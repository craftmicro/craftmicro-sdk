#pragma once
/**
 * This minimal version only includes enough code to set up the display and to
 * send the framebuffer to it via SPI and (optionally) DMA.
 *
 * ACKNOWLEDGEMENTS
 * This ILI9341 SPI-based display code has drawn on the contributions of many smart people.
 * Many thanks to:
 *		Paul Stoffregen / ILI9341_t3 - https://github.com/PaulStoffregen/ILI9341_t3
 *		Frank Bösing / ILI9341_t3DMA - https://github.com/FrankBoesing/ILI9341_t3DMA
 *		KurtE / ILI9341_t3n - https://github.com/KurtE/ILI9341_t3n
 *
 * XXX: DMA SUPPORT - NOT YET IMPLEMENTED
 * To compile with or without DMA, see the CRAFTMICRO_USE_DMA define in Common.h
 **/

#include "display/hardware/DisplaySPI.h"

namespace craft {

    /**
     * Display base class for SPI-based ILI9341 display
     **/
    class DisplayILI9341 : public DisplaySPI {
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
        DisplayILI9341(
            DisplaySize sz,	// size320x240
            uint8_t cs,		// 10
            uint8_t dc,		// 15
            uint8_t rst = 4,
            uint8_t mosi = 11,
            uint8_t sclk = 13,
            uint8_t miso = 12,
            uint8_t bklt = 6,
            uint8_t scale = 1
        );

    protected:
        void setArea(ClipRect& rect) override;

    };

} // namespace craft
