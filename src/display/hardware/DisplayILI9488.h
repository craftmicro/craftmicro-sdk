#pragma once
/**
 * This minimal version only includes enough code to set up the display and to
 * send the framebuffer to it via SPI.
 **/

#include "display/hardware/DisplaySPI.h"

namespace craft {

    /**
     * Display base class for SPI-based ILI488 display
     **/
    class DisplayILI9488 : public DisplaySPI {
    public:

        /**
         * Constructor for 4-wire SPI.
         * @param	cs		Pin used for Chip Select
         * @param	dc		Pin used for Data Control
         * @param	rst		Pin used for Reset (optional. 255=unused)
         * @param	mosi	Pin used for MOSI communication (data out from master)
         * @param	sclk	Pin used for clock
         * @param	miso	Pin used for MISO communication (data out from slave)
         * @param	bklt	Pin used for backlight (optional. 255=unused)
         * @param	px 		Scale factor from framebuffer to display. Normally 1:1 (pixelScale_1x1)
         **/
        DisplayILI9488(
            DisplaySize sz,
            uint8_t cs,
            uint8_t dc,
            uint8_t rst,
            uint8_t mosi,
            uint8_t sclk,
            uint8_t miso,
            uint8_t bklt = UNUSED_PIN,
            uint8_t scale = 1
        );

    protected:
        void setArea(ClipRect& rect) override;
        void setOrientation(DisplayOrientation o) override;
    };

} // namespace craft
