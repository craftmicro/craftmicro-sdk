#pragma once

/**
 * 2D Point
 **/
namespace craft {

    /**
     * Point float_t class
     */
    class Point {
    public:

        /**
         * @brief Construct a new Point object
         *
         * @param x The x coordinate
         * @param y The y coordinate
         */
        Point(float_t x = 0, float_t y = 0) {
            this->x = x;
            this->y = y;
        }

        /**
         * X coordinate
         */
        float_t x;

        /**
         * Y coordinate
         */
        float_t y;

        /**
         * @brief Set both x and y at once
         *
         * @param x The X coordinate
         * @param y The Y coordinate
         */
        void set(float_t x, float_t y) {
            this->x = x;
            this->y = y;
        }

        /**
         * @brief Copy the values from another point to this one
         *
         * @param from The point to copy from
         */
        void copy(Point* from) {
            x = from->x;
            y = from->y;
        }

        /**
         * @brief Create a new Point with the same values as this one
         *
         * @return Point* The new point
         */
        Point* clone() {
            Point* p = new Point();
            p->copy(this);
            return p;
        }

    };



} // namespace craft

