#pragma once

#include "display/DisplayObject.h"
#include "geom/Point.h"

namespace craft {

    /**
     * A shape (polygon)
     */
    class Shape : public DisplayObject, public MemoryPool<Shape> {

    public:

        /**
         * Create a new object or take one from the pool
         * @return The new or recycled object
         */
        static Shape* Create();
        static Shape* Create(Point** points, uint16_t len);

        /**
         * Reset the object back to default settings
         */
        void reset() override;

        /**
         * @brief Provide the points that define the shape
         * If the first and last points are different, the are automatically joined
         *
         * @param points An array of points
         * @param len The number of points
         */
        void set(Point** points, uint16_t len);

        /**
         * Update the display object.
         * @param	dt 			Time since last update in seconds
         */
        void update(float_t dt);

        /**
         * Color
         */
        color888 color;

        /**
         * @brief Set the global position of the display object
         *
         * @param x The global X position
         * @param y The global Y position
         */
        void globalPos(float_t x, float_t y);

        /**
         * prepare to render the next line
         * @param ry The y position in local coordinates
         */
        void beginLine(int16_t ry);

        /**
         * Read a pixel from the sprite and advance position
         * @param rx The x position in local coordinates
         * @param ry The y position in local coordinates
         */
        void calcPixel(int16_t rx, int16_t ry);

    protected:
        /**
         * @brief The points that make up the shape
         */
        Point** _points = 0;

        /**
         * @brief The number of points
         */
        uint16_t _pointsLen = 0;

    };

} // namespace craft
