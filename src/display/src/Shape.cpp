#include "../Shape.h"

namespace craft {

    Shape* Shape::Create(Point** points, uint16_t len) {
        Shape* shape = MemoryPool<Shape>::Create();
        shape->set(points, len);
        return shape;
    }

    void Shape::reset() {
        _points = 0;
        _pointsLen = 0;

        DisplayObject::reset();
    }

    void Shape::set(Point** points, uint16_t len) {

        dirty();
    }

    void Shape::update(float_t dt) {
        // Update self

        // Update children
        DisplayObject::update(dt);
    }

    void Shape::globalPos(float_t x, float_t y) {
        _localBounds->clear();
        uint16_t l = _pointsLen;
        Point* p;
        while (l--) {
            p = _points[l];
            _localBounds->x = craft::min(_localBounds->x, p->x);
            _localBounds->x2 = craft::max(_localBounds->x2, p->x);
            _localBounds->y = craft::min(_localBounds->y, p->y);
            _localBounds->y2 = craft::max(_localBounds->y2, p->y);
        }
        DisplayObject::globalPos(x, y);
    }

    void Shape::beginLine(int16_t ry) {

    }

    void Shape::calcPixel(int16_t rx, int16_t ry) {
        _ra = 1;
        _rc = color;
    }

} // namespace craft