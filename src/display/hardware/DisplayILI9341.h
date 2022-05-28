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

#include "display/Display.h"

namespace craft {

    /**
     * Define SPI parameters
     **/
    #define SPICLOCK	60e6

     /**
      * Display base class for ILI9341 displays.
      * A contructor overload should be implemented for each communication type. At the moment
      * only 4-wire SPI is implemented.
      **/
    class DisplayILI9341 : public Display {
    public:

        /**
         * Constructor for 4-wire SPI.
         * Note - constructor calls init, so you don't need to.
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
            uint8_t scale = PixelScale::x1
        );

        /**
         * @brief Draw data to an area of the display
         *
         * @param buffer The line buffer to draw (buffer is scaled by pixel scale)
        */
        void draw(LineBufferData& buffer);

    protected:

        /**
         * SPI
         **/
        uint8_t _rst;
        uint8_t _cs, _dc;
        uint8_t _pcs_data, _pcs_command;
        uint8_t _miso, _mosi, _sclk;

        /**
         * @brief Wait until there is space on the SPI fifo
         */
        __attribute__((always_inline)) inline void waitFifoNotFull(void) {
            uint32_t sr;
            uint32_t tmp __attribute__((unused));
            do {
                sr = KINETISK_SPI0.SR;
                if (sr & 0xF0) tmp = KINETISK_SPI0.POPR;  // drain RX FIFO
            } while ((sr & (15 << 12)) > (3 << 12));
        }

        /**
         * @brief Wait until the SPI fifo is empty
         */
        __attribute__((always_inline)) inline void waitFifoEmpty(void) {
            uint32_t sr;
            uint32_t tmp __attribute__((unused));
            do {
                sr = KINETISK_SPI0.SR;
                if (sr & 0xF0) tmp = KINETISK_SPI0.POPR;  // drain RX FIFO
            } while ((sr & 0xF0F0) > 0);             // wait both RX & TX empty
        }

        __attribute__((always_inline)) inline void waitTransmitComplete(void) {
            uint32_t tmp __attribute__((unused));
            while (!(KINETISK_SPI0.SR & SPI_SR_TCF)); // wait until final output done
            tmp = KINETISK_SPI0.POPR;                  // drain the final RX FIFO word
        }
        __attribute__((always_inline)) inline void waitTransmitComplete(uint32_t mcr) {
            uint32_t tmp __attribute__((unused));
            while (1) {
                uint32_t sr = KINETISK_SPI0.SR;
                if (sr & SPI_SR_EOQF) break;  // wait for last transmit
                if (sr & 0xF0) tmp = KINETISK_SPI0.POPR;
            }
            KINETISK_SPI0.SR = SPI_SR_EOQF;
            SPI0_MCR = mcr;
            while (KINETISK_SPI0.SR & 0xF0) {
                tmp = KINETISK_SPI0.POPR;
            }
        }

        /**
         * @brief Write an SPI command
         */
        __attribute__((always_inline)) inline void writeCommand(uint8_t c) {
            KINETISK_SPI0.PUSHR = c | (_pcs_command << 16) | SPI_PUSHR_CTAS(0) | SPI_PUSHR_CONT;
            waitFifoNotFull();
        }
        __attribute__((always_inline)) inline void writeCommand_last(uint8_t c) {
            uint32_t mcr = SPI0_MCR;
            KINETISK_SPI0.PUSHR = c | (_pcs_command << 16) | SPI_PUSHR_CTAS(0) | SPI_PUSHR_EOQ;
            waitTransmitComplete(mcr);
        }

        /**
         * @brief Write SPI data
         */
        __attribute__((always_inline)) inline void writeData8(uint8_t c) {
            KINETISK_SPI0.PUSHR = c | (_pcs_data << 16) | SPI_PUSHR_CTAS(0) | SPI_PUSHR_CONT;
            waitFifoNotFull();
        }
        __attribute__((always_inline)) inline void writeData8_last(uint8_t c) {
            uint32_t mcr = SPI0_MCR;
            KINETISK_SPI0.PUSHR = c | (_pcs_data << 16) | SPI_PUSHR_CTAS(0) | SPI_PUSHR_EOQ;
            waitTransmitComplete(mcr);
        }
        __attribute__((always_inline)) inline void writeData16(uint16_t d) {
            KINETISK_SPI0.PUSHR = d | (_pcs_data << 16) | SPI_PUSHR_CTAS(1) | SPI_PUSHR_CONT;
            waitFifoNotFull();
        }
        __attribute__((always_inline)) inline void writeData16_last(uint16_t d) {
            uint32_t mcr = SPI0_MCR;
            KINETISK_SPI0.PUSHR = d | (_pcs_data << 16) | SPI_PUSHR_CTAS(1) | SPI_PUSHR_EOQ;
            waitTransmitComplete(mcr);
        }
    };

} // namespace craft
