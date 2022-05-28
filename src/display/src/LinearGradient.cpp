#include "../LinearGradient.h"

namespace craft {

    LinearGradient* LinearGradient::Create(uint8_t numStops) {
        LinearGradient* g = MemoryPool<LinearGradient>::Create();
        g->_numStops = numStops;
        g->_stops = new GradientStop * [numStops];
        while (numStops--) g->_stops[numStops] = GradientStop::Create();
        return g;
    }

    void LinearGradient::recycle() {
        MemoryPool<LinearGradient>::recycle();
    }

    void LinearGradient::beginRender(ClipRect* updateArea) {
        // Calculate all stop values
        if (_needsCalc) {
            _needsCalc = false;

            float_t dx = _x2 - _x;
            float_t dy = _y2 - _y;

            // Reverse stops if required
            if (dx < 0) {
                swap(_x, _x2);
                swap(_y, _y2);
                dx = -dx;
                dy = -dy;

                if (!_reverse) {
                    _reverse = true;
                    reverse();
                }
            }
            else if (_reverse) {
                _reverse = false;
                reverse();
            }

            // Calculate stops
            uint8_t i = 0;
            uint8_t n = 1;
            _stops[0]->update(0);
            while (i < _numStops - 1) {
                _stops[i]->distance = _stops[n]->position - _stops[i]->position;
                _stops[i]->step = 1.0 / _stops[i]->distance;
                _stops[n]->update(0);
                _stops[i]->dr = (_stops[n]->r - _stops[i]->r);
                _stops[i]->dg = (_stops[n]->g - _stops[i]->g);
                _stops[i]->db = (_stops[n]->b - _stops[i]->b);
                _stops[i]->da = (_stops[n]->a - _stops[i]->a);
                i++; n++;
            }

            // Screen area
            _y0 = updateArea->y;

            // vertical?

            if (dx == 0.0) {
                _dx = 0;
                _dy = 1.0 / dy;
                _pos0 = -_y * _dy;
            }
            else {
                // Calculate pos at origin (pos0)
                float_t m = dy / dx;
                float_t x3 = _x + m * _y;
                float_t x4 = _x2 + m * _y2;
                float_t d = (x4 - x3);
                _pos0 = -x3 / d;

                // Calculate steps to change gradient
                _dx = 1.0 / d;
                _dy = m * _dx;
            }
        }
    }

    void LinearGradient::beginLine(int16_t ry) {
        // Calculate pos offset based on pos0 and dy
        _pos = _pos0 + (ry - _y0) * _dy;

        // Calculate the first stop on this line
        _activeStop = 0;
        while (_activeStop < _numStops) {
            if (_activeStop == _numStops - 1) break;
            if (_stops[_activeStop + 1]->position >= _pos) {
                _stops[_activeStop]->update(_pos);
                break;
            }
            _activeStop++;
        }
    }

    void LinearGradient::calcPixel(int16_t rx, int16_t ry) {
        rc = (((uint8_t)_stops[_activeStop]->r) << 16) | (((uint8_t)_stops[_activeStop]->g) << 8) | (uint8_t)_stops[_activeStop]->b;
        ra = _stops[_activeStop]->a;
        if (_activeStop < (_numStops - 1)) {
            while ((_activeStop < (_numStops - 1)) && (_pos >= _stops[_activeStop + 1]->position)) {
                _activeStop++;
            }
            _stops[_activeStop]->update(_pos);
        }
        _pos += _dx;
    }

    void LinearGradient::skipPixel(int16_t rx, int16_t ry) {
        _pos += _dx;
    }

} // namespace craft