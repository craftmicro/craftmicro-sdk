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
         * If there is no framebuffer, implement drawBegin, drawEnd, and either drawPixel565 or drawPixel888
         */
        void* framebuffer = nullptr;

        /**
         * @brief Internal: Called automatically once to initialize the display when mounted
         *
         * Do not call this method directly. It is used internally.
         */
        void mount();

        /**
         * @brief Called at the start of a frame when drawing to the display
         *
         * @param area The area of the display that will be updated
         */
        virtual void drawBegin(ClipRect* area) {}

        /**
         * @brief Draw a pixel to the display. Should be implemented if framebuffer is not provided and color mode is RGB565.
         *
         * @param x The x coordinate
         * @param y The y coordinate
         * @param color The color to draw
         */
        virtual void drawPixel565(int x, int y, uint16_t color) {}

        /**
         * @brief Draw a pixel to the display. Should be implemented if framebuffer is not provided and color mode is RGB888.
         *
         * @param x The x coordinate
         * @param y The y coordinate
         * @param color The color to draw
         */
        virtual void drawPixel888(int x, int y, uint32_t color) {}

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
        ClipRect rect;

        /**
         * @brief Draw a pixel to the framebuffer
         *
         * @param x The x coordinate
         * @param y The y coordinate
         * @param color The color to draw
         * @param a The alpha value
         */
        void draw(int x, int y, uint32_t color, float_t a);

        /**
         * @brief Draw a pixel to the framebuffer
         *
         * @param x The x coordinate
         * @param y The y coordinate
         * @param color The color to draw
         */
        void draw565(int x, int y, uint16_t color);

        /**
         * @brief Blend a pixel to the framebuffer
         *
         * @param x The x coordinate
         * @param y The y coordinate
         * @param color The color to draw
         * @param a The alpha value
         */
        void blend565(int x, int y, uint16_t color, float_t a);

        /**
         * @brief Draw a pixel to the framebuffer
         *
         * @param x The x coordinate
         * @param y The y coordinate
         * @param color The color to draw
         */
        void draw888(int x, int y, uint32_t color);

        /**
         * @brief Blend a pixel to the framebuffer
         *
         * @param x The x coordinate
         * @param y The y coordinate
         * @param color The color to draw
         * @param a The alpha value
         */
        void blend888(int x, int y, uint32_t color, float_t a);

    };

} // namespace craft
