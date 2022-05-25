#pragma once
#ifndef _CRAFTMICRO_IDRAWABLEH_
#define _CRAFTMICRO_IDRAWABLEH_ 1

#include "Common.h"
#include "geom/ClipRect.h"
#include "graphics/Color.h"

namespace craft {

	/**
	 * An interface for all drawable objects
	 */
	class IDrawable {
	public:
		/**
		 * @brief Begin the render sweep for the current frame
		 * The render sweep for each frame is:
		 * 		beginRender
		 * 			beginLine y
		 * 				calcPixel|calcMaskPixel|skipPixel x ... x2
		 *			...
		 * 			beginLine y2
		 * 				calcPixel|calcMaskPixel|skipPixel x ... x2
		 * 		endRender
		 * @param updateArea The area of the display being updated
		 */
		virtual void beginRender( ClipRect* updateArea ) {}

		/**
		 * @Brief Initialise the next line to be read for rendering
		 *
		 * Identified the y coordinate in local space at which the next line of pixels
		 * will be read (@see readPixel). In the same sweep, ry will always be 1 greater
		 * than ry on the last call to prepareLine
		 *
		 * @param ry The current Y position (line) in local coordinates
		 */
		virtual void beginLine( int16_t ry ) {}

		/**
		 * @brief Calculate the pixel to be rendered at the current position
		 *
		 * The coordinates, rx and ry, are in local coordinates. rx will always be n + 1
		 * higher than rx the previous call to calcPixel, calcMaskPixel or skipPixel for
		 * a given line (prepareLine is called at the start of a line). ry will be
		 * identical.
		 *
		 * The renderer expects the  results of calcPixel to be in _rc (the color, 24bit RGB)
		 * and _ra (alpha 0.0 - 1.0).
		 *
		 * @param rx The current X position in local coordinates
		 * @param ry The current Y position in local coordinates
		 */
		virtual void calcPixel( int16_t rx, int16_t ry ) {
			_rc = 0;
			_ra = 0.0;
		}

		/**
		 * @brief Skip the pixel at the current position
		 * If the object is not being drawn (for example, it is masked by a higher object) then
		 * skipPixel will be called instead of calcPixel. Some implementations may require some
		 * processing, even if the pixel is not being rendered.
		 *
		 * @param rx The current X position in local coordinates
		 * @param ry The current Y position in local coordinates
		 */
		virtual void skipPixel( int16_t rx, int16_t ry ) {}

		/**
		 * @brief End the render sweep for the current frame
		 * @see beginRender
		 */
		virtual void endRender() {}

		/**
		 * @brief Return the color calculated by the last calcPixel call
		 * @return color888 The color
		 */
		inline color888 getCalcColor() {
			return _rc;
		}

		/**
		 * @brief Return the alpha calculated by the last calcPixel call
		 * @return float_t The alpha
		 */
		inline float_t getCalcAlpha() {
			return _ra;
		}

	protected:
		/**
		 * @brief The color from the previous call to calcPixel
		 */
		color888 _rc;

		/**
		 * @brief The alpha from the previous call to calcPixel
		 */
		float_t _ra;

	}; // class

} // namespace

#endif