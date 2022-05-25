#pragma once
#ifndef _CRAFTMICRO_COLORMASKFILTER_H
#define _CRAFTMICRO_COLORMASKFILTER_H 1

#include "Filter.h"

namespace craft {

	/**
	 * Color-mask filter
	 * Makes a specifc color transparent
	 */
	class ColorMaskFilter : public Filter, public MemoryPool<Filter> {
	public:
		/**
		 * @brief Construct a new Color Mask Filter object
		 *
		 * @param color The color to mask
		 */
		ColorMaskFilter( color888 color ) {
			this->color = color & 0xffffff;
		}

		/**
		 * @brief Apply the filter to the specified pixel
		 *
		 * @param rx The current X position in local coordinates
		 * @param ry The current Y position in local coordinates
		 * @param a (in/out) The alpha value of the pixel being filtered
		 * @param c (in/out) The color value of the pixel being filtered
		 */
		void filterPixel( int16_t rx, int16_t ry, float_t& a, color888& c ) override {
			if ( ( c & 0xffffff ) == this->color ) a = 0;
		}

		/**
		 * @brief The color being masked
		 */
		color888 color = 0;

		/**
		 * @brief Reset filter back to defaults
		 */
		void reset() override {
			color = 0;
		}

	};



} // namespace

#endif
