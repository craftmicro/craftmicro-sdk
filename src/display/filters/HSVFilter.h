#pragma once
#ifndef _CRAFTMICRO_HSVFILTER_H
#define _CRAFTMICRO_HSVFILTER_H 1

#include "Filter.h"

namespace craft {

	/**
	 * Hue Saturation Value filter
	 */
	class HSVFilter : public Filter, public MemoryPool<Filter> {

	public:
		/**
		 * @brief Construct a new Hue Saturation Value Filter object
		 *
		 * @param h The hue shift (is in the range 0 to 360 after the shift)
		 * @param s The saturation shift (is in the range 0.0 to 1.0 after the shift)
		 * @param v The value shift (is in the range 0.0 to 1.0 after the shift)
		 */
		HSVFilter( float_t h = 0, float_t s = 0, float_t v = 0 ) {
			this->h = h;
			this->s = s;
			this->v = v;
		}

		/**
		 * @brief Apply the filter to the specified pixel
		 *
		 * @param rx The current X position in local coordinates
		 * @param ry The current Y position in local coordinates
		 * @param a (in/out) The alpha value of the pixel being filtered
		 * @param c (in/out) The color value of the pixel being filtered
		 */
		void filterPixel( int16_t rx, int16_t ry, float_t& a, color888& c ) {
			float_t h, s, v;
			toHSV( c, h, s, v );
			h += this->h;
			s += this->s;
			v += this->v;
			c = to8888( h, s, v );
		}

		/**
		 * @brief Reset filter back to defaults
		 */
		void reset() override {
			h = 0;
			s = 0;
			v = 0;
		}

		float_t h = 0;
		float_t s = 0;
		float_t v = 0;

	};

} // namespace

#endif
