#pragma once

#include "Common.h"
#include "display/LineBufferData.h"
#include "geom/ClipRect.h"
#include "graphics/Bitmap.h"

namespace craft {

    /**
     * Pixel scaling.
     */
    namespace PixelScale {
        enum {
            x1 = 0,
            x2 = 1,
            x4 = 2,
            x8 = 3,
        };
    };

    /**
     * Display size
     */
    enum class DisplaySize {
        Size128x128,
        Size320x240,
        Size240x240,
        Size135x240,
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
         * @brief Draw a buffer of pixel data to the display
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

            // (2) Initilise process for sending data to the hardware
            /*
            startTransaction();
            */

            // (3) Hardware will first usually require the user to specify the screen area to draw to
            /*
            setDestinationArea(
                buffer.rect.x << _px,						// top-left x
                buffer.rect.y << _py,						// top-left y
                ((buffer.rect.x2 + 1) << _px) - 1,			// bottom-right x
                ((buffer.rect.y2 + 1) << _px) - 1			// bottom-right y
            );
            */

            // (4) Now send the data
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
            /*
            int scale = 1 << _px;
            int lineOffset = buffer.rect.y * _size.width;
            for ( uint16_t y = buffer.rect.y; y <= buffer.rect.y2; y++ ) {
                for ( uint16_t yi = 0; yi < scale; yi++ ) {
                    for ( uint16_t x = buffer.rect.x; x <= buffer.rect.x2; x++ ) {
                        for ( uint16_t xi = 0; xi < scale; xi++ ) {
                            sendPixel( to565( buffer.pixels[lineOffset + x] ) );
                        }
                    }
                }
                lineOffset += _size.width;
            }
            */

            // (5) Finalise the process to stop sending data to the hardware
            /*
            endTransaction();
            */

            // (6) Set ready flag to indicate we are ready for the next draw call
            ready = true;
        }

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
        uint8_t _px = PixelScale::x1;

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
        boolean _bkltPWM = false;

        /**
         * @brief Set the area of the display to draw to
         *
         * @param buffer The line buffer
         */
        virtual void setArea(LineBufferData& buffer);
    };

} // namespace craft
