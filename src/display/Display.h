#pragma once

#include "Common.h"
#include "display/LineBufferData.h"
#include "geom/ClipRect.h"
#include "graphics/Bitmap.h"

namespace craft {

    /**
     * Display base class
     *
     * To use this class, you must subclass it and implement
     *  - beginDrawing()
     *  - drawPixel565() or drawPixel888()
     *  - endDrawing()
     **/
    class Display {
    public:
        /**
         * @brief Currently only RGB565 (16bit) and RGB888 (24bit) are supported.
         */
        PixelFormat pixelFormat = PixelFormat::Unknown;

        /**
         * @brief The width of the display in pixels
         */
        int width = 0;

        /**
         * @brief The height of the display in pixels
         */
        int height = 0;

        /**
         * @brief The amount to scale pixels
         */
        int pixelScale = 1;

        /**
         * @brief Size of the line buffer in lines (0 for full frame buffer)
         */
        int lineBufferHeight = 1;

        /**
         * @brief Called to begin drawing a new frame
         *
         * This will be followed by a series of drawPixel() calls, and finally endDrawing().
         *
         * @param rect The area of the display that will be drawn
         */
        virtual void beginDrawing(ClipRect& rect) {
            _x = rect.x;
            _y = rect.y;
        };

        /**
         * @brief Called to draw a single 16bit RGB565 pixel to the display
         *
         * @param color The color of the pixel to draw
         */
        virtual inline void drawPixel565(color565 color) {};

        /**
         * @brief Called to draw a single 24bit RGB888 pixel to the display
         *
         * @param color The color of the pixel to draw
         */
        virtual inline void drawPixel888(color888 color) {};

        /**
         * @brief Called to end drawing the current frame
         */
        virtual void endDrawing() {}

    protected:
        friend class LineBuffer;

        /**
         * Update the linebuffer to the display
         **/
        void draw(LineBufferData& buffer, int bufferWidth);

        /**
         * Update the linebuffer to the display for 16-bit pixel formats
         **/
        void draw565(LineBufferData& buffer, int bufferWidth);

        /**
         * Update the linebuffer to the display
         **/
        void draw888(LineBufferData& buffer, int bufferWidth);

        /**
         * @brief Current screen drawing position
         */
        int _x = 0;
        int _y = 0;
    };

} // namespace craft
