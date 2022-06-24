#pragma once

#include "display/Display.h"
#include <SPI.h>
#if CRAFTMICRO_USE_DMA
#include <DMAChannel.h>
#endif

namespace craft {

    #define UNUSED_PIN 255
    #define PIN_OR_UNUSED(p) p==UNUSED_PIN?-1:p
    #define DELAY_COMMAND 255

    /**
     * @brief Determine clock speed
     */

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
        uint32_t _spiClock;
        bool _useSpiTransaction = true;
        SPIClass* _spi = nullptr;

        /**
         * @brief Initialise SPI and the display
         */
        ALWAYS_INLINE void init() {

            // Determine clock speed
            #if defined(KINETISK)
            _spiClock = 60e6;
            #else
            _spiClock = 40e6;
            #endif

            // Determnine SPI class
            // TODO: Based on pins?
            #if defined(ESP32)
            _spi = new SPIClass(VSPI);
            _useSpiTransaction = true;
            #elif defined(KINETISK)
            _spi = new SPIClass(SPI);
            _useSpiTransaction = false;
            #else
            _spi = new SPIClass(SPI);
            #endif

            // Set up MISO, MOSI and SCLK
            #if defined(KINETISK)
            if (_mosi != UNUSED_PIN) _spi->setMOSI(_mosi);
            if (_miso != UNUSED_PIN) _spi->setMISO(_miso);
            if (_sclk != UNUSED_PIN) _spi->setSCK(_sclk);
            _spi->begin();
            #else
            _spi->begin(PIN_OR_UNUSED(_sclk), PIN_OR_UNUSED(_miso), PIN_OR_UNUSED(_mosi), PIN_OR_UNUSED(_cs));
            #endif

            // Set up CS and DC
            #if defined(KINETISK)
            if (_spi->pinIsChipSelect(_cs, _dc)) {
                _pcs_data = SPI.setCS(_cs);
                _pcs_command = _pcs_data | SPI.setCS(_dc);
            }
            else {
                _useSpiTransaction = true; // Fallback
            }
            #endif
            if (_useSpiTransaction) {
                if (_cs != UNUSED_PIN) {
                    pinMode(_cs, OUTPUT);
                    digitalWrite(_cs, HIGH);
                }
                if (_dc != UNUSED_PIN) {
                    pinMode(_dc, OUTPUT);
                    digitalWrite(_dc, HIGH); // Data mode
                }
            }

            // If the reset feature is used, reset the display (Reset is active low)
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

        /**
         * @brief Perform a sequence of SPI commands
         * @param commands Array of commands
         * @return ALWAYS_INLINE
         */
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

        /**
         * @brief Start an SPI transaction
         */
        ALWAYS_INLINE void beginTransaction() {
            SPI.beginTransaction(SPISettings(_spiClock, MSBFIRST, SPI_MODE0));
            if (_cs != UNUSED_PIN && _useSpiTransaction) digitalWrite(_cs, LOW);
        }

        /**
         * @brief End the SPI transaction
         */
        ALWAYS_INLINE void endTransaction() {
            if (_cs != UNUSED_PIN && _useSpiTransaction) digitalWrite(_cs, HIGH);
            SPI.endTransaction();
        }

        /**
         * @brief Write an SPI command
         */
        ALWAYS_INLINE void writeCommand(uint8_t c) {
            #if defined(KINETISK)
            if (!_useSpiTransaction) {
                KINETISK_SPI0.PUSHR = c | _pcs_command << 16 | SPI_PUSHR_CTAS(0) | SPI_PUSHR_CONT;
                waitFifoNotFull();
                return;
            }
            #endif
            if (_dc != UNUSED_PIN) digitalWrite(_dc, LOW);
            _spi->transfer(c);
            if (_dc != UNUSED_PIN) digitalWrite(_dc, HIGH);
        }
        ALWAYS_INLINE void writeCommand_last(uint8_t c) {
            #if defined(KINETISK)
            if (!_useSpiTransaction) {
                uint32_t mcr = SPI0_MCR;
                KINETISK_SPI0.PUSHR = c | _pcs_command << 16 | SPI_PUSHR_CTAS(0) | SPI_PUSHR_EOQ;
                waitTransmitComplete(mcr);
                return;
            }
            #endif
            writeCommand(c);
        }

        /**
         * @brief Write SPI data
         */
        ALWAYS_INLINE void writeData8(uint8_t d) {
            #if defined(KINETISK)
            if (!_useSpiTransaction) {
                KINETISK_SPI0.PUSHR = d | _pcs_data << 16 | SPI_PUSHR_CTAS(0) | SPI_PUSHR_CONT;
                waitFifoNotFull();
                return;
            }
            #endif
            _spi->transfer(d);
        }
        ALWAYS_INLINE void writeData8_last(uint8_t d) {
            #if defined(KINETISK)
            if (!_useSpiTransaction) {
                uint32_t mcr = SPI0_MCR;
                KINETISK_SPI0.PUSHR = d | _pcs_data << 16 | SPI_PUSHR_CTAS(0) | SPI_PUSHR_EOQ;
                waitTransmitComplete(mcr);
                return;
            }
            #endif
            writeData8(d);
        }
        ALWAYS_INLINE void writeData16(uint16_t d) {
            #if defined(KINETISK)
            if (!_useSpiTransaction) {
                KINETISK_SPI0.PUSHR = d | _pcs_data << 16 | SPI_PUSHR_CTAS(1) | SPI_PUSHR_CONT;
                waitFifoNotFull();
                return;
            }
            #endif
            _spi->transfer16(d);
        }
        ALWAYS_INLINE void writeData16_last(uint16_t d) {
            #if defined(KINETISK)
            if (!_useSpiTransaction) {
                uint32_t mcr = SPI0_MCR;
                KINETISK_SPI0.PUSHR = d | _pcs_data << 16 | SPI_PUSHR_CTAS(1) | SPI_PUSHR_EOQ;
                waitTransmitComplete(mcr);
                return;
            }
            #endif
            writeData16(d);
        }

        // KINETISK methods for fast hardware SPI
        #if defined(KINETISK)

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

        #endif // KINETISK
    };

} // namespace craft
