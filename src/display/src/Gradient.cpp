#include "../Gradient.h"

namespace craft {

	Gradient::Gradient( uint8_t numStops ) {
		numStops = max( 2, numStops );
		_numStops = numStops;
		_stops = new GradientStop * [numStops];
		while ( numStops-- ) _stops[numStops] = GradientStop::Create();
	}

	Gradient::~Gradient() {
		reset();
	}

	void GradientStop::reset() {
		color = 0;
		alpha = 1.0;
		position = 0.0;
		distance = 0.0;
		step = 0.0;
		r = 0.0;
		g = 0.0;
		b = 0.0;
		a = 0.0;
		dr = 0.0;
		dg = 0.0;
		db = 0.0;
		da = 0.0;
	}

	void GradientStop::update( float_t pos ) {
		r = (float_t)( ( color >> 16 ) & 0xff );
		g = (float_t)( ( color >> 8 ) & 0xff );
		b = (float_t)( ( color >> 0 ) & 0xff );
		a = this->alpha;
		if ( ( pos > position ) && ( pos < ( position + distance ) ) ) {
			float_t s = ( pos - position ) * step;
			r += dr * s;
			g += dg * s;
			b += db * s;
			a += da * s;
		}
	}

	void Gradient::reset() {
		// Reset position
		position( 0, 0, 1.0, 0 );
		// Remove stops
		if ( _stops ) {
			while ( _numStops-- ) _stops[_numStops]->recycle();
			delete[] _stops;
		}
		_stops = nullptr;
	}

	void Gradient::position( float_t x, float_t y, float_t x2, float_t y2 ) {
		_needsCalc = true;
		_x = x;
		_x2 = x2;
		_y = y;
		_y2 = y2;
	}

	/**
	 * @brief Set or change a gradient stop
	 *
	 * @param color The color of the stop
	 * @param alpha The alpha at the stop
	 * @param position The position along the gradient (0.0 - 1.0)
	 */
	Gradient* Gradient::stop( uint8_t index, color888 color, float_t alpha, float_t position ) {
		_needsCalc = true;
		if ( _reverse ) index = _numStops - index - 1;
		_stops[index]->color = color;
		_stops[index]->alpha = alpha;
		_stops[index]->position = _reverse ? ( 1.0 - position ) : position;
		return this;
	}

	/**
	 * @brief Reverse the stops
	 *
	 */
	void Gradient::reverse() {
		uint8_t n = 0;
		GradientStop* t;
		while ( n < ( _numStops >> 1 ) ) {
			t = _stops[n];
			_stops[n] = _stops[_numStops - n - 1];
			_stops[_numStops - n - 1] = t;
			n++;
		}
		n = 0;
		while ( n < _numStops ) {
			_stops[n]->position = 1 - _stops[n]->position;
			n++;
		}
	}

} // namespace