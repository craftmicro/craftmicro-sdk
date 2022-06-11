#pragma once

#include "display/Display.h"
#include <SPI.h>
#if CRAFTMICRO_USE_DMA
#include <DMAChannel.h>
#endif

namespace craft {

    #define UNUSED_PIN 255
    #define DELAY_COMMAND 255

    /**
     * Display base class for SPI displays.
     **/
    class DisplaySPI : public Display {
    public:

        /**
         * @brief Draw data to an area of the display
         *
         * @param buffer The line buffer to draw (buffer is scaled by pixel scale)
        */
        void draw(LineBufferData& buffer) override;

    protected:

        uint8_t _rst;
        uint8_t _cs, _dc;
        uint8_t _miso, _mosi, _sclk;
        uint8_t _pcs_data, _pcs_command;

        // Kinetis K Series microcontrollers (ARM Cortex M4)
        #if defined(KINETISK)

        #define SPICLOCK	60e6

        ALWAYS_INLINE void init() {
            if (_mosi != UNUSED_PIN) SPI.setMOSI(_mosi);
            if (_miso != UNUSED_PIN) SPI.setMOSI(_miso);
            if (_sclk != UNUSED_PIN)  SPI.setSCK(_sclk);
            SPI.begin();

            if (SPI.pinIsChipSelect(_cs, _dc)) {
                _pcs_data = SPI.setCS(_cs);
                _pcs_command = _pcs_data | SPI.setCS(_dc);
            }

            // If the reset feature is used, reset the display.
            // Reset is active low.
            if (_rst != UNUSED_PIN) {
                pinMode(_rst, OUTPUT);
                digitalWrite(_rst, HIGH);
                delay(5);
                digitalWrite(_rst, LOW);
                delay(20);
                digitalWrite(_rst, HIGH);
                delay(150);
            }

            // Turn on the backlight
            if (_bklt != UNUSED_PIN) {
                pinMode(_bklt, OUTPUT);
                backlight(1.0);
            }
        }

        ALWAYS_INLINE void beginTransaction() {
            SPI.beginTransaction(SPISettings(SPICLOCK, MSBFIRST, SPI_MODE0));
        }

        ALWAYS_INLINE void endTransaction() {
            SPI.endTransaction();
        }

        /**
         * @brief Wait until there is space on the SPI fifo
         */
        ALWAYS_INLINE void waitFifoNotFull(void) {
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
        ALWAYS_INLINE void waitFifoEmpty(void) {
            uint32_t sr;
            uint32_t tmp __attribute__((unused));
            do {
                sr = KINETISK_SPI0.SR;
                if (sr & 0xF0) tmp = KINETISK_SPI0.POPR;  // drain RX FIFO
            } while ((sr & 0xF0F0) > 0);             // wait both RX & TX empty
        }

        ALWAYS_INLINE void waitTransmitComplete(void) {
            uint32_t tmp __attribute__((unused));
            while (!(KINETISK_SPI0.SR & SPI_SR_TCF)); // wait until final output done
            tmp = KINETISK_SPI0.POPR;                  // drain the final RX FIFO word
        }
        ALWAYS_INLINE void waitTransmitComplete(uint32_t mcr) {
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
        ALWAYS_INLINE void writeCommand(uint8_t c) {
            KINETISK_SPI0.PUSHR = c | (_pcs_command << 16) | SPI_PUSHR_CTAS(0) | SPI_PUSHR_CONT;
            waitFifoNotFull();
        }
        ALWAYS_INLINE void writeCommand_last(uint8_t c) {
            uint32_t mcr = SPI0_MCR;
            KINETISK_SPI0.PUSHR = c | (_pcs_command << 16) | SPI_PUSHR_CTAS(0) | SPI_PUSHR_EOQ;
            waitTransmitComplete(mcr);
        }

        /**
         * @brief Write SPI data
         */
        ALWAYS_INLINE void writeData8(uint8_t c) {
            KINETISK_SPI0.PUSHR = c | (_pcs_data << 16) | SPI_PUSHR_CTAS(0) | SPI_PUSHR_CONT;
            waitFifoNotFull();
        }
        ALWAYS_INLINE void writeData8_last(uint8_t c) {
            uint32_t mcr = SPI0_MCR;
            KINETISK_SPI0.PUSHR = c | (_pcs_data << 16) | SPI_PUSHR_CTAS(0) | SPI_PUSHR_EOQ;
            waitTransmitComplete(mcr);
        }
        ALWAYS_INLINE void writeData16(uint16_t d) {
            KINETISK_SPI0.PUSHR = d | (_pcs_data << 16) | SPI_PUSHR_CTAS(1) | SPI_PUSHR_CONT;
            waitFifoNotFull();
        }
        ALWAYS_INLINE void writeData16_last(uint16_t d) {
            uint32_t mcr = SPI0_MCR;
            KINETISK_SPI0.PUSHR = d | (_pcs_data << 16) | SPI_PUSHR_CTAS(1) | SPI_PUSHR_EOQ;
            waitTransmitComplete(mcr);
        }

        // End KINETISK
        #else

        #define SPICLOCK	40e6

        SPIClass* _spi = nullptr;
        SPISettings _spiSettings = SPISettings(SPICLOCK, MSBFIRST, SPI_MODE0);

        ALWAYS_INLINE void init() {
            // If the reset feature is used, reset the display.
            // Reset is active low.
            if (_rst != UNUSED_PIN) {
                pinMode(_rst, OUTPUT);
                digitalWrite(_rst, HIGH);
                delay(100);
                digitalWrite(_rst, LOW);
                delay(100);
                digitalWrite(_rst, HIGH);
                delay(200);
            }

            // Init SPI
            _spi = new SPIClass(VSPI);
            if (_cs != UNUSED_PIN) {
                pinMode(_cs, OUTPUT);
                digitalWrite(_cs, HIGH);
            }
            if (_dc != UNUSED_PIN) {
                pinMode(_dc, OUTPUT);
                digitalWrite(_dc, HIGH); // Data mode
            }
            _spi->begin(_sclk, _miso == UNUSED_PIN ? -1 : _miso, _mosi, _cs); //SCLK, MISO, MOSI, SS

            // Turn on the backlight
            if (_bklt != UNUSED_PIN) {
                pinMode(_bklt, OUTPUT);
                backlight(1.0);
            }
        }

        ALWAYS_INLINE void beginTransaction() {
            _spi->beginTransaction(_spiSettings);
            if (_cs != UNUSED_PIN) digitalWrite(_cs, LOW);
        }

        ALWAYS_INLINE void endTransaction() {
            if (_cs != UNUSED_PIN) digitalWrite(_cs, HIGH);
            _spi->endTransaction();
        }

        /**
         * @brief Write an SPI command
         */
        ALWAYS_INLINE void writeCommand(uint8_t c) {
            if (_dc != UNUSED_PIN) digitalWrite(_dc, LOW);
            _spi->write(c);
            if (_dc != UNUSED_PIN) digitalWrite(_dc, HIGH);
        }

        ALWAYS_INLINE void writeCommand_last(uint8_t c) {
            writeCommand(c);
        }

        /**
         * @brief Write SPI data
         */
        ALWAYS_INLINE void writeData8(uint8_t d) {
            _spi->write(d);
        }

        ALWAYS_INLINE void writeData8_last(uint8_t d) {
            writeCommand(d);
        }

        ALWAYS_INLINE void writeData16(uint16_t d) {
            _spi->write16(d);
        }

        ALWAYS_INLINE void writeData16_last(uint16_t d) {
            writeData16(d);
        }

        #endif

        ALWAYS_INLINE void commandSequence(const uint8_t* commands) {
            const uint8_t* addr = commands;
            uint8_t c;
            while (1) {
                uint8_t count = *addr++;
                if (count-- == 0) break;
                c = *addr++;
                if (c == DELAY_COMMAND) {
                    c = *addr++;
                    delay(c);
                }
                else {
                    writeCommand(c);
                    while (count-- > 0) {
                        writeData8(*addr++);
                    }
                }
            }
        }
    };

} // namespace craft
