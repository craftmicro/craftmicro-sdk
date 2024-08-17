#pragma once

#include "Common.h"
#include "geom/ClipRect.h"
#include "graphics/Bitmap.h"

namespace craft {

    typedef void (*drawFunc)(int x, int y, uint32_t color, int pixelScale, bool hasFramebuffer, void* buffer, int width);

    /**
     * Display base class
     *
     * To use this class, you must subclass it and provide all properties:
     * - pixelFormat
     * - width
     * - height
     * - pixelScale
     * - framebuffer
     **/
    class Display {
    public:
        /**
         * @brief Destroy the Display object
         *
         * If a framebuffer is supplied, the user manages it's lifecycle.
         */
        ~Display();

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
         * @brief Pointer to the framebuffer
         *
         * The framebuffer must be the size of the entire display, and the type must match the pixelFormat property.
         * If pixelFormat is RGB565, the framebuffer must be an array of uint16_t[width * height]
         * If pixelFormat is RGB888, the framebuffer must be an array of uint8_t[width * height * 3]
         *
         * If there is no framebuffer, implement drawBegin, drawEnd, and either drawPixel565 or drawPixel888.
         * If a framebuffer is provided these functions do not need to be implemented.
         */
        void* framebuffer = nullptr;

        /**
         * @brief Called at the start of a frame when drawing to the display
         *
         * @param area The area of the display that will be updated
         */
        virtual void drawBegin(ClipRect* area) {}

        /**
         * @brief Draw a pixel to the display. Should be implemented if framebuffer is not provided and color mode is RGB565.
         *
         * @param color The color to draw
         */
        virtual void draw565(uint16_t color) {}

        /**
         * @brief Draw a pixel to the display. Should be implemented if framebuffer is not provided and color mode is RGB888.
         *
         * @param color The color to draw
         */
        virtual void draw888(uint32_t color) {}

        /**
         * @brief Called at the end of a frame when drawing to the display
         */
        virtual void drawEnd() {}

    protected:
        friend class App;
        friend class Stage;

        /**
         * @brief The drawable size in scaled pixels
         */
        ClipRect _rect;

        /**
         * @brief Called automatically once to initialize the display when mounted
         */
        void _mount();

        /**
         * @brief Has a user-provided framebuffer
         */
        bool _hasFramebuffer = false;

        /**
         * @brief Start x position of the line buffer
         */
        int _x;

        /**
         * @brief Current line
         */
        int _y;

        /**
         * @brief Width of the current drawing rect
         */
        int _w;

        /**
         * @brief Called when rendering a frame is about to start
         *
         * @param area The area of the display to update
         */
        void _drawBegin(ClipRect* area);

        /**
         * @brief Called when rendering a line is about to start
         */
        void _lineBegin(int y);

        /**
         * @brief Called when rendering a line has ended to flush the line to the display
         */
        void _lineFlush();

        /**
         * @brief The draw function to use based on the pixelFormat
         */
        drawFunc _drawFunc;

        /**
         * @brief Draw a pixel to the display
         */
        void _draw(int x, color8888 color);
    };

} // namespace craft
