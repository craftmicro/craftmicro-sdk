#pragma once

#include "display/hardware/DisplaySPI.h"

namespace craft {

    /**
     * Display base class for SPI-based Raydium RM67162 displays.
     **/
    class DisplayRM67162: public DisplaySPI {
    public:
        /**
         * Constructor for 4-wire SPI.
         * @param	cs		Pin used for Chip Select
         * @param	dc		Pin used for Data Control
         * @param	rst		Pin used for Reset (optional. 255=unused)
         * @param	mosi	Pin used for MOSI communication (data out from master)
         * @param	sclk	Pin used for clock
         * @param	bklt	Pin used for backlight (optional. 255=unused)
         * @param	px 		Scale factor from framebuffer to display. Normally 1:1 (pixelScale_1x1)
         **/
        DisplayRM67162(
            DisplaySize sz, // size400x400
            uint8_t cs,		// 5
            uint8_t dc,		// 16
            uint8_t rst = 23,
            uint8_t mosi = 19,
            uint8_t sclk = 18,
            uint8_t bklt = 4,
            uint8_t scale = 1
        );

    protected:
        int _xoffset = 0; // Not sure if we need these yet
        int _yoffset = 0;

        void setArea(LineBufferData& buffer) override;
    };

} // namespace craft
