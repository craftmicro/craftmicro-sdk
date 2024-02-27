#pragma once

#include "Common.h"
#include "geom/ClipRect.h"
#include "graphics/Bitmap.h"

namespace craft {

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
         * @brief Draw a pixel to the framebuffer
         *
         * @param x The x coordinate
         * @param color The color to draw
         * @param a The alpha value
         */
        void _draw(int x, uint32_t color, float_t a);

        /**
         * @brief Draw a pixel to the framebuffer
         *
         * @param x The x coordinate
         * @param color The color to draw
         */
        void _draw565(int x, uint16_t color);

        /**
         * @brief Blend a pixel to the framebuffer
         *
         * @param x The x coordinate
         * @param color The color to draw
         * @param a The alpha value
         */
        void _blend565(int x, uint16_t color, float_t a);

        /**
         * @brief Draw a pixel to the framebuffer
         *
         * @param x The x coordinate
         * @param color The color to draw
         */
        void _draw888(int x, uint32_t color);

        /**
         * @brief Blend a pixel to the framebuffer
         *
         * @param x The x coordinate
         * @param color The color to draw
         * @param a The alpha value
         */
        void _blend888(int x, uint32_t color, float_t a);

    };

} // namespace craft
