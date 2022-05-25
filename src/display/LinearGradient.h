#pragma once
#ifndef _CRAFTMICRO_LINEARGRADIENTH_
#define _CRAFTMICRO_LINEARGRADIENTH_ 1

#include "Gradient.h"

namespace craft {

	/**
	 * A linear gradient
	 */
	class LinearGradient : public Gradient, public MemoryPool<LinearGradient> {
	public:
		/**
		 * Create a new object or take one from the pool
		 * @return The new or recycled object
		 */
		static LinearGradient* Create( uint8_t numStops );

		/**
		 * @brief Construct a new Linear Gradient object
		 *
		 * @param numStops The number of stops. Must be at least 2
		 */
		LinearGradient( uint8_t numStops = 2 ) : Gradient( numStops ) {}

		/**
		 * @brief Recycle back to the memory pool
		 */
		void recycle() override;

		/**
		 * @brief Begin the render sweep for the current frame
		 * @param updateArea The area of the display being updated
		 */
		void beginRender( ClipRect* updateArea ) override;

		/**
		 * prepare to render the next line
		 * @param ry The y position in local coordinates
		 */
		void beginLine( int16_t ry ) override;

		/**
		 * @brief Calulcate the next pixel in the line
		 * @param rx The x position in local coordinates
		 * @param ry The y position in local coordinates
		 */
		void calcPixel( int16_t rx, int16_t ry ) override;

		/**
		 * @brief Advance a pixel without calculating it
		 *
		 * @param rx The x position in local coordinates
		 * @param ry The y position in local coordinates
		 */
		void skipPixel( int16_t rx, int16_t ry ) override;

	};

} // namespace

#endif