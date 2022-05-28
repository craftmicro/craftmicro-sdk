#pragma once

#include "Common.h"
#include "geom/Point.h"

/**
 * Line segment
 **/
namespace craft {

    /**
     * Line segment
     */
    class Line {
    public:
        /**
         * @brief Construct a new Line object
         *
         * @param x The x coordinate of start point
         * @param y The y coordinate of start point
         * @param x2 The x coordinate of end point
         * @param y2 The y coordinate of end point
         */
        Line(float_t x = 0, float_t y = 0, float_t x2 = 0, float_t y2 = 0) {
            this->x = x;
            this->y = y;
            this->x2 = x2;
            this->y2 = y2;
        }

        /**
         * X coordinate of start point
         */
        float_t x;

        /**
         * Y coordinateof start point
         */
        float_t y;

        /**
         * X coordinate of end point
         */
        float_t x2;

        /**
         * Y coordinate of end point
         */
        float_t y2;

        /**
         * @brief Set both start and end points at once
         *
         * @param x The x coordinate of start point
         * @param y The y coordinate of start point
         * @param x2 The x coordinate of end point
         * @param y2 The y coordinate of end point
         */
        void set(float_t x = 0, float_t y = 0, float_t x2 = 0, float_t y2 = 0) {
            this->x = x;
            this->y = y;
            this->x2 = x2;
            this->y2 = y2;
        }

        /**
         * @brief Set both x and y of start point at once
         *
         * @param x The X coordinate
         * @param y The Y coordinate
         */
        void setStart(float_t x, float_t y) {
            this->x = x;
            this->y = y;
        }

        /**
         * @brief Set both x and y of end point at once
         *
         * @param x The X coordinate
         * @param y The Y coordinate
         */
        void setEnd(float_t x, float_t y) {
            this->x2 = x;
            this->y2 = y;
        }

        /**
         * @brief Get the intersection point of two lines
         *
         * @param line The line to check for intersection
         * @return Point* The intersection point, or null if they do not intersect
         */
        Point* intersection(Line* line) {
            float_t detL1 = determinant();
            float_t detL2 = Line::Determinant(line);
            float_t x1mx2 = x - x2;
            float_t x3mx4 = line->x - line->x2;
            float_t y1my2 = y - y2;
            float_t y3my4 = line->y - line->y2;

            float_t denom = Line::Determinant(x1mx2, y1my2, x3mx4, y3my4);
            if (denom == 0.0)
                return NULL;

            float_t xnom = Line::Determinant(detL1, x1mx2, detL2, x3mx4);
            float_t ynom = Line::Determinant(detL1, y1my2, detL2, y3my4);
            Point* p = new Point(xnom / denom, ynom / denom);
            if (!isfinite(p->x) || !isfinite(p->y))
            {
                delete p;
                return NULL;
            }

            return p;
        }

        /**
         * @brief Copy the values from another line to this one
         *
         * @param from The line to copy from
         */
        void copy(Line* from) {
            x = from->x;
            y = from->y;
            x2 = from->x2;
            y2 = from->y2;
        }

        /**
         * @brief Create a new Line with the same values as this one
         *
         * @return Line* The new line
         */
        Line* clone() {
            return new Line(x, y, x2, y2);
        }

    protected:
        inline double determinant() {
            return this->x * this->y2 - this->y * this->x2;
        }
        static inline double Determinant(float_t a, float_t b, float_t c, float_t d) {
            return a * d - b * c;
        }
        static inline double Determinant(Line* line) {
            return line->x * line->y2 - line->y * line->x2;
        }
    };

} // namespace craft
