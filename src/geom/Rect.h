#pragma once

#include "Common.h"
#include "Matrix.h"
#include "Point.h"
#include "utils/Math.h"

namespace craft {

    /**
     * A float rectangle class
     */
    class Rect {

    public:
        /**
         * Constructor
         */
        Rect() {
            clear();
        }

        /**
         * Constructor
         */
        Rect(float_t x, float_t y, float_t w, float_t h) {
            setPosAndSize(x, y, w, h);
        }

        /**
         * Constructor
         */
        Rect(Point p1, Point p2) {
            set(p1.x, p1.y, p2.x, p2.y);
        }

        /**
         * Top-left corner of the rect
         */
        Point p1;

        /**
         * Bottom-right corner of the rect
         * For all comparisons (such as @see contains), p2 itself is not included.
         */
        Point p2;

        /**
         * Clear back to an empty rect
         */
        void clear() {
            p1.set(0, 0);
            p2.set(0, 0);
        }

        /**
         * Set (copy) the size of the rect from the supplied rect
         * @param rect   	The rect to set from
         */
        void set(Rect rect) {
            p1.set(rect.p1.x, rect.p1.y);
            p2.set(rect.p2.x, rect.p2.y);
        }

        /**
         * Set the top-left and bottom-right corners of rect.
         * Adjusts width and height.
         * @param p1   	The top-left corner
         * @param p2	The bottom-right corner
         */
        void set(Point p1, Point p2) {
            set(p1.x, p1.y, p2.x, p2.y);
        }

        /**
         * Set the top-left and bottom-right corners of rect.
         * Adjusts width and height.
         * @param x   	X coordinate of top-left corner
         * @param y 	Y coordinate of top-left corner
         * @param x2	X coordinate of bottom-right corner
         * @param y2  	Y coordinate of bottom-right corner
         */
        void set(float_t x, float_t y, float_t x2, float_t y2) {
            if (x2 < x) {
                p1.x = x2;
                p2.x = x;
            }
            else {
                p1.x = x;
                p2.x = x2;
            }
            if (y2 < y) {
                p1.y = y2;
                p2.y = y;
            }
            else {
                p1.y = y;
                p2.y = y2;
            }
        }

        /**
         * Set width of rect
         * @param w The width
         */
        void width(float_t w) {
            if (w < 0) {
                p1.x += w;
                w = -w;
            }
            p2.x = p1.x + w;
        }

        /**
         * @brief Return the width of the rect
         * @return float_t The width
         */
        float_t width() {
            return p2.x - p1.x;
        }

        /**
         * Set height of rect
         * @param h The height
         */
        void height(float_t h) {
            if (h < 0) {
                p1.y += h;
                h = -h;
            }
            p2.y = p1.y + h;
        }

        /**
         * @brief Return the height of the rect
         * @return float_t The height
         */
        float_t height() {
            return p2.y - p1.y;
        }

        /**
         * Set the top-left corner of rect.
         * Keeps the same width and height Adjusts bottom-right corner
         * @param x   	X coordinate of top-left corner
         * @param y 	Y coordinate of top-left corner
         **/
        void setPos(float_t x, float_t y) {
            float_t w = width();
            float_t h = height();
            p1.set(x, y);
            p2.set(x + w, y + h);
        }

        /**
         * Set the bottom-right corner of rect.
         * Keeps the same width and height Adjusts top-left corner
         * @param x2   	X coordinate of bottom-right corner
         * @param y2 	Y coordinate of bottom-right corner
         **/
        void setPos2(float_t x2, float_t y2) {
            float_t w = width();
            float_t h = height();
            p2.set(x2, y2);
            p1.set(x2 - w, y2 - h);
        }

        /**
         * Set the width and height of the rect
         * Adjusts p2
         * @param w   	Width of rect
         * @param h 	Height of rect
         **/
        void setSize(float_t w, float_t h) {
            p2.set(p1.x + w, p1.y + h);
        }

        /**
         * Set the top-left corner and width and height of the rect
         * Adjusts p2
         * @param x   	X coordinate of top-left corner
         * @param y 	Y coordinate of top-left corner
         * @param w   	Width of rect
         * @param h 	Height of rect
         **/
        void setPosAndSize(float_t x, float_t y, float_t w, float_t h) {
            if (w < 0) {
                x += w;
                w = -w;
            }
            if (h < 0) {
                y += h;
                h = -h;
            }
            p1.set(x, y);
            p2.set(x + w, y + h);
        }

        /**
         * Transform the rect with the provided matrix
         * @param t The matrix to transform by
         */
        void transform(Matrix* t) {
            Point tl = Point(p1.x, p1.y);
            Point tr = Point(p2.x, p1.y);
            Point bl = Point(p1.x, p2.y);
            Point br = Point(p2.x, p2.y);
            t->transform(&tl);
            t->transform(&tr);
            t->transform(&bl);
            t->transform(&br);
            // TODO: 12 compares. Can we improve this?
            p1.x = min(tl.x, min(tr.x, min(bl.x, br.x)));
            p1.y = min(tl.y, min(tr.y, min(bl.y, br.y)));
            p2.x = max(tl.x, max(tr.x, max(bl.x, br.x)));
            p2.y = max(tl.y, max(tr.y, max(bl.y, br.y)));
        }

        /**
         * Transform the rect with the provided matrix around a point
         * @param t The matrix to transform by
         * @param originX The X-coordinate as the origin
         * @param originY The Y-coordinate as the origin
         */
        void transform(Matrix* t, float_t originX, float_t originY) {
            Point tl = Point(p1.x, p1.y);
            Point tr = Point(p2.x, p1.y);
            Point bl = Point(p1.x, p2.y);
            Point br = Point(p2.x, p2.y);
            t->transform(&tl, originX, originY);
            t->transform(&tr, originX, originY);
            t->transform(&bl, originX, originY);
            t->transform(&br, originX, originY);
            // TODO: 12 compares. Can we improve this?
            p1.x = min(tl.x, min(tr.x, min(bl.x, br.x)));
            p1.y = min(tl.y, min(tr.y, min(bl.y, br.y)));
            p2.x = max(tl.x, max(tr.x, max(bl.x, br.x)));
            p2.y = max(tl.y, max(tr.y, max(bl.y, br.y)));
        }

        /**
         * Return true if the rect contains the specified point
         * @param  x  	X coord to test
         * @param  y 	Y coord to test
         * @return   True if point within rect
         */
        bool contains(float_t x, float_t y) {
            return ((x >= p1.x) && (x < p2.x) && (y >= p1.y) && (y < p2.y));
        }

        /**
         * Return true if the rect contains the specified X coord
         * @param  x  	X coord to test
         * @return   True if point within rect
         */
        bool containsX(float_t x) {
            return ((x >= p1.x) && (x < p2.x));
        }

        /**
         * Return true if the rect contains the specified Y coord
         * @param  y  	Y coord to test
         * @return   True if point within rect
         */
        bool containsY(float_t y) {
            return ((y >= p1.y) && (y < p2.y));
        }

        /**
         * Check if the rect is empty (has a 0 width or height)
         * @return True if the rect is empty
         */
        bool isEmpty() {
            return (p1.x == p2.x) || (p1.y == p2.y);
        }

        /**
         * Check if any part of another rect overlaps this one
         * @param rect The other rect
         * @return bool True if any part of the rects overlap
         */
        bool overlaps(Rect rect) {
            if (isEmpty() || rect.isEmpty()) return false;
            if (rect.p2.x < p1.x) return false;
            if (rect.p1.x >= p2.x) return false;
            if (rect.p2.y < p1.y) return false;
            if (rect.p1.y >= p2.y) return false;
            return true;
        }

        /**
         * Clip this rect to another rect (intersection)
         * @param  rect  	The rect to clip to
         */
        void clip(Rect rect) {
            if (p1.x < rect.p1.x) p1.x = rect.p1.x;
            if (p2.x > rect.p2.x) p2.x = rect.p2.x;
            if (p1.y < rect.p1.y) p1.y = rect.p1.y;
            if (p2.y > rect.p2.y) p2.y = rect.p2.y;
            if (p1.x > p2.x) p2.x = p1.x;
            if (p1.y > p2.y) p2.y = p1.y;
        }

        /**
         * Clip this rect to a rectangular area specified by position and size (intersection)
         * @param  x  	X coord to clip
         * @param  y 	Y coord to clip
         * @param  w  	Width
         * @param  h 	Height
         */
        void clipPosAndSize(float_t x, float_t y, float_t w, float_t h) {
            if (w < 0) {
                w = -w;
                x -= w;
            }
            if (h < 0) {
                h = -h;
                y -= h;
            }
            if (p1.x < x) p1.x = x;
            if (p2.x > (x + w)) p2.x = x + w;
            if (p1.y < y) p1.y = y;
            if (p2.y > (y + h)) p2.y = y + h;
            if (p1.x > p2.x) p2.x = p1.x;
            if (p1.y > p2.y) p2.y = p1.y;
        }

        /**
         * Expand this rect to also encompase the specified rect (union)
         * @param rect The rect to encompase
         */
        void grow(Rect rect) {
            if (isEmpty()) {
                set(rect);
                return;
            }
            if (p1.x > rect.p1.x) p1.x = rect.p1.x;
            if (p2.x < rect.p2.x) p2.x = rect.p2.x;
            if (p1.y > rect.p1.y) p1.y = rect.p1.y;
            if (p2.y < rect.p2.y) p2.y = rect.p2.y;
        }

        /**
         * Expand this rect to also encompase a rectangular area specified by position and size (union)
         * @param  x  	X coord to clip
         * @param  y 	Y coord to clip
         * @param  w  	Width
         * @param  h 	Height
         */
        void growPosAndSize(float_t x, float_t y, float_t w, float_t h) {
            if (isEmpty()) {
                set(x, y, w, h);
                return;
            }
            if (w < 0) {
                w = -w;
                x -= w;
            }
            if (h < 0) {
                h = -h;
                y -= h;
            }
            if (p1.x > x) p1.x = x;
            if (p2.x < (x + w)) p2.x = x + w;
            if (p1.y > y) p1.y = y;
            if (p2.y < (y + h)) p2.y = y + h;
        }

        /**
         * @brief Create a clone of this rect
         *
         * @return Rect* A clone of this object
         */
        Rect* clone() {
            return new Rect(this->p1, this->p2);
        }

    }; // class

} // namespace craft
