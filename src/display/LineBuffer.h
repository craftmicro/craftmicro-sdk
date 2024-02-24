#pragma once

#include "Common.h"
#include "display/LineBufferData.h"
#include "display/Display.h"
#include "geom/ClipRect.h"
#include "graphics/Bitmap.h"

namespace craft {

    /**
     * @brief Two most common line buffer heights
     */
    enum LineBufferHeight {
        fullFramebuffer = 0,
        singleLine = 1
    };

    /**
     * Line Buffer
     * A line-by-line frame buffer implementation
     **/
    class LineBuffer {
    public:
        /**
         * @brief Construct a new Line Buffer object
         *
         * @param	display			A Display instance for the hardware display being used.
         * @param	bufferHeight	The height of the line buffer, in lines. Default = 1. Full frame buffer = 0.
         */
        LineBuffer(Display* display);

        /**
         * @brief Destroy the Line Buffer object
         */
        ~LineBuffer();

        /**
         * @brief Start the render process for a frame
         * Sets the buffer region
         * @param rect The region of the display to draw to
         */
        void begin(ClipRect* rect);

        /**
         * @brief End the render process for a frame
         */
        void end();

        /**
         * Resets the region without changing it. This resets the line buffer to
         * start of the region. The back buffer is not affected until the next flip.
         */
        void resetRegion();

        /**
         * @brief Advance the buffer to the next line and flush to hardware if necessary
         * The buffer is advanced to the next line. If the buffer is filled or the end of
         * the drawing region is reached, the buffers are flipped and the pixels are
         * flushed to the hardware. Setting flush to true will also flip and flush the
         * buffer, even if it is not full.
         * @param flush If true will flush the buffer to the hardware even if not full
         */
        void flip(bool flush = false);

        /**
         * Fill the current line with a color. Respects region
         **/
        inline void clear(color888 c) {
            uint16_t i = region.x;
            while (i < region.x2) _data[_frontIndex].pixels[i++] = c;
        }

        /**
         * Write a pixel to the current line. Overwrites underlying pixel (if any)
         * @param  c 	The color (pixel) in RGB 888 format
         * @param  x 	The X coordinate
         */
        inline void pixel(color888 c, int16_t x) {
            _data[_frontIndex].pixels[_yOffset + x] = c;
        }

        /**
         * read a pixel from the current line (front buffer)
         * @param  x 	The X coordinate
         * @return 		The color (pixel) in RGB 888 format
         */
        inline color888 pixel(int16_t x) {
            return _data[_frontIndex].pixels[_yOffset + x];
        }

        /**
         * Blend a pixel to the current line using float_t alpha 0.0 - 1.0
         * @param  c 	The color (pixel) in RGB 888 format
         * @param  a 	The alpha (0.0 - 1.0)
         * @param  x 	The X coordinate
         */
        inline void blend(color888 c, alpha_t a, int16_t x) {
            _data[_frontIndex].pixels[_yOffset + x] = blend888(_data[_frontIndex].pixels[_yOffset + x], c, alpha8bit(a));
        }

        /**
         * Blend a pixel to the current line using integer alpha 0 - 255
         * @param  c 	The color (pixel) in RGB 888 format
         * @param  a 	The alpha (0 - 255)
         * @param  x 	The X coordinate
         */
        inline void blend(color888 c, uint8_t a, int16_t x) {
            _data[_frontIndex].pixels[_yOffset + x] = blend888(_data[_frontIndex].pixels[_yOffset + x], c, a);
        }

        /**
         * @brief Reference to the display
         */
        Display* display;

        /**
         * @brief Maximum buffer size as dictated by display
         */
        ClipRect maxRegion;

        /**
         * @brief Rect describing the dirty region (region of the buffer being updated)
         */
        ClipRect region;

        /**
         * @brief Rect describing the scaled region (region scaled by pixelScale)
         */
        ClipRect scaledRegion;

        /**
         * @brief Get the buffer to draw (the back buffer)
         */
        LineBufferData drawBuffer() {
            return _data[_frontIndex];
        }

    protected:
        /**
         * @brief Pointer to the pixel data
         */
        LineBufferData _data[2];

        /**
         * @brief Index to the active (front) data buffer for reading and writing
         */
        uint8_t _frontIndex = 0;

        /**
         * @brief Index to the active data buffer for transferring to the hardware. I.e: `lineBuff->data[ lineBuff->backIndex ][ x ]`
         */
        uint8_t _backIndex = 1;

        /**
         * @brief Height of the line buffer in lines
         */
        uint16_t _bufferHeight = 1;

        /**
         * @brief Width of the line buffer in pixels
         */
        uint16_t _bufferWidth = 0;

        /**
         * @brief Currently active line
         */
        uint16_t _y = 0;

        /**
         * @brief Pixel offset of current line
         */
        uint16_t _yOffset = 0;
    };

} // namespace craft
