#pragma once

#include "Common.h"
#include "display/LineBufferData.h"
#include "geom/ClipRect.h"
#include "graphics/Bitmap.h"

namespace craft {

    /**
     * Display size
     */
    enum class DisplaySize {
        Size128x128,
        Size320x240,
        Size240x240,
        Size135x240,
        Size135x240_flipped,
        Size240x135,
        Size240x135_flipped,
        Size240x280,
        Size320x480,
        Size480x320,
    };

    /**
     * Display orientation
     */
    enum class DisplayOrientation {
        Default,            // Default for the display. Could be either portrait or landscape
        Landscape,          // Landscape
        Portrait,           // Portrait
        LandscapeFlipped,   // Landscape but upside-down
        PortraitFlipped,    // Portrait but upside-down
    };

    /**
     * Display base class.
     * This minimal version of the display class only includes enough code to
     * set up the display and to draw pixels to it. Do not use this class directly.
     * Use one of the derived classes specifically for your display in /display/hardware
     *
     * Any hardware implementation is required to implement:
     * 		Constructor
     * 		draw (@see Display::draw)
     * 		ready (@see Display::ready)
     **/
    class Display {
    public:

        /**
         * Destroy the Display object
         */
        virtual ~Display(void) {}

        /**
         * @brief Set up to begin drawing a single render pass (frame)
         *
         * @param rect The area to draw to
         */
        virtual void beginDrawing(ClipRect& rect);

        /**
         * @brief Draw a buffer of pixel data to the display
         *
         * @see beginDrawing should be called first
         * @see endDrawing should be called once all pixel data is complete
         *
         * Each display must override this method. The example below provides a
         * template of the steps required to implement the draw method.
         * @see DisplayILI9341 for a full implementation using 4-wire SPI
         *
         * It is always assumed that all inputs are valid, and no checking or
         * clipping needs to occur
         *
         * @param buffer The line buffer to draw (buffer is scaled by pixel scale)
         */
        virtual void draw(LineBufferData& buffer) {

            // (1) Set ready flag to indicate we are not ready for the next draw call yet.
            // Note that this is not really required for syncronous methods (like this example)
            // but is important if DMA or an alternative asyncronous method of sending the
            // pixel data is used.
            ready = false;

            // (2) Send the data
            // Pixel scaling allows 1 pixel in the data to be scaled up to 2x2, 4x4 or 8x8 pixels
            // on the display. That means that if a line of pixels in scaled by 4x4 we actually
            // need to draw that line 4 times. Likewise, we also need to draw each pixel
            // horizontally 4 times.
            // Example: data[ A, B, C ] at 4x4 pixel scale (_px)
            // Display: AAAABBBBCCCC
            //			AAAABBBBCCCC
            //			AAAABBBBCCCC
            //			AAAABBBBCCCC
            //
            // Colours are always provided in 888 format (0x00000000RRRRRRRRGGGGGGGGBBBBBBBB). Use
            // the conversion functions for the hardware's colour. For example to565

            // (3) Set ready flag to indicate we are ready for the next draw call
            ready = true;
        }

        /**
         * @brief Finalise drawing a single render pass
         */
        virtual void endDrawing();

        /**
         * Flag indicates when the draw command has finished pushing pixels to the hardware.
         */
        bool ready = false;

        /**
         * Width of the display in pixels (scaled by pixelscale). Read-only.
         **/
        int16_t width() { return _size.width; }

        /**
         * Height of the display in pixels (scaled by pixelscale). Read-only.
         **/
        int16_t height() { return _size.height; }

        /**
         * Width of the display in pixels (unscaled). Read-only.
         **/
        int16_t hardwareWidth() { return _hwSize.width; }

        /**
         * Height of the display in pixels (unscaled). Read-only.
         **/
        int16_t hardwareHeight() { return _hwSize.height; }

        /**
         * The pixel format of the display
         */
        PixelFormat pixelFormat() { return _pf; }

        /**
         * The orientation of the display
         */
        DisplayOrientation orientation() { return _o; }

        /**
         * Turn the backlight on or off. If the backlight pin is set, the backlight
         * is turned on automatically during init/construction. If you want it off, call
         * backlight(0) after construction.
         * @param	brightness	0.0 - 1.0
         **/
        void backlight(float_t brightness) {
            if (_bklt == 255) return;
            brightness = alphaClamp(brightness);
            if (brightness == 0) digitalWrite(_bklt, LOW);
            else if (_bkltPWM) analogWrite(_bklt, (uint8_t)(255.0 * brightness));
            else digitalWrite(_bklt, HIGH);
        }

    protected:

        /**
         * Pixel format
         */
        PixelFormat _pf = PixelFormat::Unknown;

        /**
         * Pixel scale
         */
        uint8_t _px = 1;

        /**
         * @brief Display orientation
         */
        DisplayOrientation _o = DisplayOrientation::Default;

        /**
         * Actual hardware width and height of the display
         */
        ClipRect _hwSize;

        /**
         * Width and height after applying pixel scale
         */
        ClipRect _size;

        /**
         * Backlight
         **/
        uint8_t _bklt = 255;
        bool _bkltPWM = false;

        /**
         * @brief Set the area of the display to draw to
         *
         * @param rect The area to draw to
         */
        virtual void setArea(ClipRect& rect);

        /**
         * @brief Set the Orientation of the display
         *
         * At this time this must be called only once during display construction. It is not possible
         * to change the display orientation at runtime. Well, that's not exactly true - it should be
         * possible to switch between landscape/landscapeFlipped, or between portrait/portraitFlipped
         * but not from one to the other. This is because the line buffer would also need to be changed
         * to reflect the different size of the line.
         *
         * @param o The orientation
         */
        virtual void setOrientation(DisplayOrientation o) {}
    };

} // namespace craft
