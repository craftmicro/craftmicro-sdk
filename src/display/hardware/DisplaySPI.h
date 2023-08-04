#pragma once

#include "display/Display.h"
#include <SPI.h>
#if CRAFTMICRO_USE_DMA
#include <DMAChannel.h>
#endif

namespace craft {

    #define UNUSED_PIN 255
    #define PIN_OR_UNUSED(p) p==UNUSED_PIN?-1:p
    #define DELAY_COMMAND 0xff

    /**
     * @brief Determine clock speed
     */

     /**
      * Display base class for SPI displays.
      **/
    class DisplaySPI : public Display {
    public:

        /**
         * Prepare to start sending pixels
         */
        void beginDrawing(ClipRect& rect) override {
            // Begin the transmission to hardware
            beginTransaction();

            // Set the area of the display to write to
            setArea(rect);
        }

        /**
         * Update the linebuffer to the display
         **/
        void draw(LineBufferData& buffer) override {
            switch (_pf) {
                case PixelFormat::RGB888:
                    draw888(buffer);
                    break;
                case PixelFormat::RGB565:
                default:
                    draw565(buffer);
                    break;
            }
        }

        /**
         * Finalise sending pixels
         */
        void endDrawing() override {
            // Done with complete transaction
            endTransaction();
        }

        /**
         * Update the linebuffer to the display for 16-bit pixel formats
         **/
        void draw565(LineBufferData& buffer) {
            // Set not ready
            ready = false;

            // Write pixels. Some SPI implementations require the final pixel
            // to be written differently, so we need to keep track of the count
            if (_px == 1) {
                int lineOffset = 0;
                int count = buffer.rect.width * buffer.rect.height;
                for (uint16_t y = buffer.rect.y; y <= buffer.rect.y2; y++) {
                    for (uint16_t x = buffer.rect.x; x <= buffer.rect.x2; x++) {
                        if (--count) writeData16(to565(buffer.pixels[lineOffset + x]));
                        else writeData16_last(to565(buffer.pixels[lineOffset + x]));
                    }
                    lineOffset += _size.width;
                }
            }
            else {
                int count = buffer.rect.width * _px * buffer.rect.height * _px;
                int lineOffset = 0;
                for (uint16_t y = buffer.rect.y; y <= buffer.rect.y2; y++) {
                    for (uint16_t i = 0; i < _px; i++) {
                        for (uint16_t x = buffer.rect.x; x <= buffer.rect.x2; x++) {
                            for (uint16_t j = 0; j < _px; j++) {
                                if (--count) writeData16(to565(buffer.pixels[lineOffset + x]));
                                else writeData16_last(to565(buffer.pixels[lineOffset + x]));
                            }
                        }
                    }
                    lineOffset += _size.width;
                }
            }

            // Set ready to send data
            ready = true;
        }

        /**
         * Update the linebuffer to the display
         **/
        void draw888(LineBufferData& buffer) {
            // Set not ready
            ready = false;

            // Write pixels. Some SPI implementations require the final pixel
            // to be written differently, so we need to keep track of the count
            if (_px == 1) {
                color888 c;
                int lineOffset = 0;
                int count = buffer.rect.width * buffer.rect.height;
                for (uint16_t y = buffer.rect.y; y <= buffer.rect.y2; y++) {
                    for (uint16_t x = buffer.rect.x; x <= buffer.rect.x2; x++) {
                        c = buffer.pixels[lineOffset + x];
                        writeData8((c >> 16) & 0xff);
                        writeData8((c >> 8) & 0xff);
                        if (--count) writeData8(c & 0xff);
                        else writeData8_last(c & 0xff);
                    }
                    lineOffset += _size.width;
                }
            }
            else {
                color888 c;
                int count = buffer.rect.width * _px * buffer.rect.height * _px;
                int lineOffset = 0;
                for (uint16_t y = buffer.rect.y; y <= buffer.rect.y2; y++) {
                    for (uint16_t i = 0; i < _px; i++) {
                        for (uint16_t x = buffer.rect.x; x <= buffer.rect.x2; x++) {
                            c = buffer.pixels[lineOffset + x];
                            for (uint16_t j = 0; j < _px; j++) {
                                writeData8((c >> 16) & 0xff);
                                writeData8((c >> 8) & 0xff);
                                if (--count) writeData8(c & 0xff);
                                else writeData8_last(c & 0xff);
                            }
                        }
                    }
                    lineOffset += _size.width;
                }
            }

            // Set ready to send data
            ready = true;
        }

    protected:

        uint8_t _rst;
        uint8_t _cs, _dc;
        uint8_t _miso, _mosi, _sclk;
        uint8_t _pcs_data, _pcs_command;
        uint32_t _spiClock;
        bool _manualCSandDC = true;
        SPIClass* _spi = nullptr;

        /**
         * @brief Initialise SPI and the display
         */
        ALWAYS_INLINE void init() {

            // Determine clock speed
            #if defined(KINETISK)
            _spiClock = 60e6;
            #else
            _spiClock = 16000000;
            #endif

            // Determnine SPI class
            #if CRAFTMICRO_DISPLAY_SPI == 1
            _spi = new SPIClass(SPI1);
            #elif CRAFTMICRO_DISPLAY_SPI == 2
            _spi = new SPIClass(SPI2);
            #elif CRAFTMICRO_DISPLAY_SPI == 3
            _spi = new SPIClass(SPI3);
            #elif CRAFTMICRO_DISPLAY_SPI == 4
            _spi = new SPIClass(SPI4);
            #elif defined(ESP32)
            switch (_mosi) {
                #if defined(HSPI)
                case 13:
                    _spi = new SPIClass(HSPI);
                    break;
                    #endif
                    #if defined(VSPI)
                case 23:
                    _spi = new SPIClass(VSPI);
                    break;
                    #endif
                default:
                    _spi = new SPIClass(SPI);
                    break;
            }
            _manualCSandDC = true;
            #elif defined(KINETISK)
            switch (_mosi) {
                case 0:
                case 21:
                    _spi = new SPIClass(SPI1);
                    break;
                case 44:
                case 52:
                    _spi = new SPIClass(SPI2);
                    break;
                case 11:
                case 7:
                case 28:
                default:
                    _spi = new SPIClass(SPI); // SPI0
                    break;
            }
            _manualCSandDC = false;
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
                _manualCSandDC = true; // Fallback
            }
            #endif
            if (_manualCSandDC) {
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
            if (_manualCSandDC && _cs != UNUSED_PIN) digitalWrite(_cs, LOW);
        }

        /**
         * @brief End the SPI transaction
         */
        ALWAYS_INLINE void endTransaction() {
            if (_manualCSandDC && _cs != UNUSED_PIN) digitalWrite(_cs, HIGH);
            SPI.endTransaction();
        }

        /**
         * @brief Write an SPI command
         */
        ALWAYS_INLINE void writeCommand(uint8_t c) {
            #if defined(KINETISK)
            if (!_manualCSandDC) {
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
            if (!_manualCSandDC) {
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
            if (!_manualCSandDC) {
                KINETISK_SPI0.PUSHR = d | _pcs_data << 16 | SPI_PUSHR_CTAS(0) | SPI_PUSHR_CONT;
                waitFifoNotFull();
                return;
            }
            #endif
            _spi->transfer(d);
        }
        ALWAYS_INLINE void writeData8_last(uint8_t d) {
            #if defined(KINETISK)
            if (!_manualCSandDC) {
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
            if (!_manualCSandDC) {
                KINETISK_SPI0.PUSHR = d | _pcs_data << 16 | SPI_PUSHR_CTAS(1) | SPI_PUSHR_CONT;
                waitFifoNotFull();
                return;
            }
            #endif
            _spi->transfer(d >> 8);
            _spi->transfer(d);
        }
        ALWAYS_INLINE void writeData16_last(uint16_t d) {
            #if defined(KINETISK)
            if (!_manualCSandDC) {
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
