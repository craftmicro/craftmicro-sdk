#pragma once

#include "display/Display.h"
#include <SPI.h>
#if CRAFTMICRO_USE_DMA
#include <DMAChannel.h>
#endif

namespace craft {

    /**
     * Define SPI parameters
     **/
    #define SPICLOCK	60e6

     /**
      * Display base class for SPI displays.
      **/
    class DisplaySPI : public Display {
    protected:

        uint8_t _rst;
        uint8_t _cs, _dc;
        uint8_t _miso, _mosi, _sclk;
        uint8_t _pcs_data, _pcs_command;

        #if defined(KINETISK)

        ALWAYS_INLINE void init() {
            if (_mosi > 0) SPI.setMOSI(_mosi);
            if (_miso > 0) SPI.setMOSI(_miso);
            if (_sclk > 0)  SPI.setSCK(_sclk);
            SPI.begin();

            if (SPI.pinIsChipSelect(_cs, _dc)) {
                _pcs_data = SPI.setCS(_cs);
                _pcs_command = _pcs_data | SPI.setCS(_dc);
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

        SPIClass* _spi = nullptr;

        ALWAYS_INLINE void init() {
            _spi = new SPIClass(HSPI);
            _spi->begin(_sclk, _miso?_miso:-1, _mosi, _cs); //SCLK, MISO, MOSI, SS
            pinMode(_cs, OUTPUT);
        }

        ALWAYS_INLINE void beginTransaction() {
            _spi->beginTransaction(SPISettings(SPICLOCK, MSBFIRST, SPI_MODE0));
        }

        ALWAYS_INLINE void endTransaction() {
            _spi->endTransaction();
        }

        /**
         * @brief Write an SPI command
         */
        ALWAYS_INLINE void writeCommand(uint8_t c) {
            digitalWrite(_spi->pinSS(), LOW);
            _spi->transfer(c);
            digitalWrite(_spi->pinSS(), HIGH);
        }

        ALWAYS_INLINE void writeCommand_last(uint8_t c) {
            writeCommand(c);
        }

        /**
         * @brief Write SPI data
         */
        ALWAYS_INLINE void writeData8(uint8_t d){
            writeCommand(d);
        }

        ALWAYS_INLINE void writeData8_last(uint8_t d) {
            writeCommand(d);
        }

        ALWAYS_INLINE void writeData16(uint16_t d) {
            writeCommand((d >> 8) & 0xff);
            writeCommand(d & 0xff);
        }

        ALWAYS_INLINE void writeData16_last(uint16_t d) {
            writeData16(d);
        }

        #endif
    };

} // namespace craft
