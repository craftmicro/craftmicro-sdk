#pragma once

#include "Common.h"
#include "Rect.h"

/**
 * Integer rect
 **/
namespace craft {

    /**
     * A clipping rectangle class
     */
    class ClipRect {

    public:
        /**
         * Construct an empty clip rect
         */
        ClipRect() {
            clear();
        }

        /**
         * Construct a clip rect as a copy of another
         */
        ClipRect(ClipRect* rect) {
            set(rect);
        }

        /**
         * Construct a clip rect from a point and size
         */
        ClipRect(int16_t px, int16_t py, int16_t w, int16_t h) {
            setPosAndSize(px, py, w, h);
        }

        /**
         * Construct a clip rect as an integer copy of a rect (floats)
         */
        ClipRect(Rect* rect) {
            set(rect);
        }

        /**
         * X coordinate of top-left corner.
         * Use setters to set so that x2 and width are adjusted appropriately.
         */
        int16_t x;

        /**
         * Y coordinate of top-left corner.
         * Use setters to set so that y2 and height are adjusted appropriately.
         */
        int16_t y;

        /**
         * X coordinate of bottom-right corner.
         * Use setters to set so that width is adjusted appropriately.
         */
        int16_t x2;

        /**
         * Y coordinate of bottom-right corner.
         * Use setters to set so that height is adjusted appropriately.
         */
        int16_t y2;

        /**
         * Width of rect. If 0, rect is invalid.
         * Use setters to set so that x2 is adjusted appropriately.
         */
        int16_t width;

        /**
         * Height of rect. If 0, rect is invalid.
         * Use setters to set so that y2 is adjusted appropriately.
         */
        int16_t height;

        /**
         * Clear back to an empty rect
         */
        void clear() {
            x = 0; y = 0;
            x2 = -1; y2 = -1;
            width = 0; height = 0;
        }

        /**
         * Set (copy) the size of the rect from the supplied rect
         * @param rect   	The rect to set from
         */
        void set(ClipRect* rect) {
            x = rect->x;
            y = rect->y;
            x2 = rect->x2;
            y2 = rect->y2;
            width = rect->width;
            height = rect->height;
        }

        /**
         * Set (copy) the size of the rect from the supplied rect
         * @param rect   	The rect to set from
         */
        void set(Rect* rect) {
            set((int16_t)rect->p1.x, (int16_t)rect->p1.y, (int16_t)rect->p2.x - 1, (int16_t)rect->p2.y - 1);
        }

        /**
         * Set the top-left and bottom-right corners of rect.
         * Adjusts width and height.
         * @param px   	X coordinate of top-left corner
         * @param py 	Y coordinate of top-left corner
         * @param px2   X coordinate of bottom-right corner
         * @param py2  	Y coordinate of bottom-right corner
         */
        void set(int16_t px, int16_t py, int16_t px2, int16_t py2) {
            if (px2 < px) {
                x = px2;
                x2 = px;
            }
            else {
                x = px;
                x2 = px2;
            }
            if (py2 < py) {
                y = py2;
                y2 = py;
            }
            else {
                y = py;
                y2 = py2;
            }
            width = x2 - x + 1;
            height = y2 - y + 1;
        }

        /**
         * Set width of rect
         * @param w The width
         */
        void setWidth(int16_t w) {
            if (w < 0) {
                x += w;
                width = -w;
            }
            else {
                width = w;
            }
            x2 = x + width - 1;
        }

        /**
         * Set height of rect
         * @param h The height
         */
        void setHeight(int16_t h) {
            if (h < 0) {
                y += h;
                height = -h;
            }
            else {
                height = h;
            }
            y2 = y + height - 1;
        }

        /**
         * Set the top-left corner of rect.
         * Adjusts bottom-right corner
         * @param px   	X coordinate of top-left corner
         * @param py 	Y coordinate of top-left corner
         **/
        void setPos(int16_t px, int16_t py) {
            x = px;
            y = py;
            x2 = x + width - 1;
            y2 = y + height - 1;
        }

        /**
         * Set the bottom-right corner of rect.
         * Adjusts width and height
         * @param px   	X coordinate of bottom-right corner
         * @param py 	Y coordinate of bottom-right corner
         **/
        void setPos2(int16_t px, int16_t py) {
            x2 = px;
            y2 = py;
            if (x2 > x) x2 = x - 1;
            if (y2 > y) y2 = y - 1;
            width = x2 - x + 1;
            height = y2 - y + 1;
        }

        /**
         * Set the width and height of the rect
         * Adjusts x2, y2
         * @param w   	Width of rect
         * @param h 	Height of rect
         **/
        void setSize(int16_t w, int16_t h) {
            setWidth(w);
            setHeight(h);
        }

        /**
         * Set the top-left corner and width and height of the rect
         * Adjusts x2, y2
         * @param px   	X coordinate of top-left corner
         * @param py 	Y coordinate of top-left corner
         * @param w   	Width of rect
         * @param h 	Height of rect
         **/
        void setPosAndSize(int16_t px, int16_t py, int16_t w, int16_t h) {
            if (w < 0) {
                px += w;
                w = -w;
            }
            if (h < 0) {
                py += h;
                h = -h;
            }
            x = px; y = py;
            width = w; height = h;
            x2 = x + width - 1; y2 = y + height - 1;
        }

        /**
         * Move the rect by the specified amount
         * @param x The amount to move in the X direction
         * @param y The amount to move in the Y direction
         */
        void translate(int16_t x, int16_t y) {
            setPos(this->x + x, this->y + y);
        }

        /**
         * Return true if the clip rect contains the specified point
         * @param  px  	X coord to test
         * @param  py 	Y coord to test
         * @return   True if point within rect
         */
        bool contains(int16_t px, int16_t py) {
            return ((px >= x) && (px <= x2) && (py >= y) && (py <= y2));
        }

        /**
         * Return true if the clip rect contains the specified X coord
         * @param  px  	X coord to test
         * @return   True if point within rect
         */
        bool containsX(int16_t px) {
            return ((px >= x) && (px <= x2));
        }

        /**
         * Return true if the clip rect contains the specified Y coord
         * @param  px  	Y coord to test
         * @return   True if point within rect
         */
        bool containsY(int16_t py) {
            return ((py >= y) && (py <= y2));
        }

        /**
         * Check if the clip rect is empty (has a 0 width or height)
         * @return True if the rect is empty
         */
        bool isEmpty() {
            return (width == 0) || (height == 0);
        }

        /**
         * Check if any part of another rect overlaps this one
         * @param rect The other rect
         * @return bool True if any part of the rects overlap
         */
        bool overlaps(ClipRect* rect) {
            if (isEmpty() || rect->isEmpty()) return false;
            if (rect->x2 < x) return false;
            if (rect->x > x2) return false;
            if (rect->y2 < y) return false;
            if (rect->y > y2) return false;
            return true;
        }

        /**
         * Clip this rect to another rect (intersection)
         * @param  rect  	The rect to clip to
         */
        void clip(ClipRect* rect) {
            if (x < rect->x) x = rect->x;
            if (x2 > rect->x2) x2 = rect->x2;
            if (y < rect->y) y = rect->y;
            if (y2 > rect->y2) y2 = rect->y2;
            if (x > x2) {
                x2 = x - 1;
            }
            width = x2 - x + 1;
            if (y > y2) {
                y2 = y - 1;
            }
            height = y2 - y + 1;
        }

        /**
         * Clip this rect to a rectangular area specified by position and size (intersection)
         * @param  px  	X coord to clip
         * @param  py 	Y coord to clip
         * @param  w  	Width
         * @param  h 	Height
         */
        void clipPosAndSize(int16_t px, int16_t py, int16_t w, int16_t h) {
            if (w < 0) {
                w = -w;
                px -= w;
            }
            if (h < 0) {
                h = -h;
                py -= h;
            }
            if (x < px) x = px;
            if (x2 >= (px + w)) x2 = px + w - 1;
            if (y < py) y = py;
            if (y2 >= (py + h)) y2 = py + h - 1;
            if (x > x2) {
                x2 = x - 1;
            }
            width = x2 - x + 1;
            if (y > y2) {
                y2 = y - 1;
            }
            height = y2 - y + 1;
        }

        /**
         * Expand this rect to also encompase the specified rect (union)
         * @param rect The rect to encompase
         */
        void grow(ClipRect* rect) {
            if (isEmpty()) {
                set(rect);
                return;
            }
            if (x > rect->x) x = rect->x;
            if (x2 < rect->x2) x2 = rect->x2;
            if (y > rect->y) y = rect->y;
            if (y2 < rect->y2) y2 = rect->y2;
            width = x2 - x + 1;
            height = y2 - y + 1;
        }

        /**
         * Expand this rect to also encompase a rectangular area specified by position and size (union)
         * @param  px  	X coord to clip
         * @param  py 	Y coord to clip
         * @param  w  	Width
         * @param  h 	Height
         */
        void growPosAndSize(int16_t px, int16_t py, int16_t w, int16_t h) {
            if (isEmpty()) {
                set(px, py, w, h);
                return;
            }
            if (w < 0) {
                w = -w;
                px -= w;
            }
            if (h < 0) {
                h = -h;
                py -= h;
            }
            if (x > px) x = px;
            if (x2 <= (px + w)) x2 = (px + w) - 1;
            if (y > py) y = py;
            if (y2 <= (py + h)) y2 = (py + h) - 1;
            width = x2 - x + 1;
            height = y2 - y + 1;
        }

        /**
         * @brief Create a clone of this rect
         *
         * @return ClipRect* A clone of this object
         */
        ClipRect* clone() {
            return new ClipRect(this->x, this->y, this->width, this->height);
        }

    }; // class

} // namespace craft
