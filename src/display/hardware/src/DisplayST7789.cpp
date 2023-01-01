#include "../DisplayST7789.h"
#include <SPI.h>

namespace craft {

    /**
     * Define ST7789 commands
     **/
    namespace ST7789_Command {
        enum {
            NOP = 0x00,
            SWRESET = 0x01, // Resets the commands and parameters to their S/W Reset default values
            RDDID = 0x04,	// Read display identification information (return 24bits)
            RDDST = 0x09,	// Read display status

            SLPIN = 0x10,  // Enter sleep mode
            SLPOUT = 0x11, // Turns off sleep mode
            PTLON = 0x12,  // Turns on partial mode
            NORON = 0x13,  // Returns the display to normal mode (aprtial mode off)

            INVOFF = 0x20,
            INVON = 0x21,
            DISPOFF = 0x28, // Turns display off
            DISPON = 0x29,	// Turns display on
            CASET = 0x2A,	// Column Address Set
            RASET = 0x2B,	// Row Address Set
            RAMWR = 0x2C,	// RAM Write (data write)
            RAMRD = 0x2E,	// RAm Read (data read)

            PTLAR = 0x30,
            TEOFF = 0x34, // Tear Effect off
            TEON = 0x35,  // tear Effect on
            MADCTL = 0x36,
            COLMOD = 0x3A
        };
    }

    namespace ST7789_MADCTL {
        enum {
            MY = 0x80,
            MX = 0x40,
            MV = 0x20,
            ML = 0x10,
            RGB = 0x00,
        };
    }

    static const uint8_t init_commands[] = {
        1, ST7789_Command::SLPOUT,
        2, ST7789_Command::COLMOD, 0x55,
        2, DELAY_COMMAND, 10,
        2, ST7789_Command::MADCTL, 0x00,
        5, ST7789_Command::CASET, 0, 0, 0, 240,
        5, ST7789_Command::RASET, 0, 0, 320 >> 8, 320 & 0xff,
        1, ST7789_Command::INVON,
        2, DELAY_COMMAND, 10,
        1, ST7789_Command::NORON,
        2, DELAY_COMMAND, 10,
        1, ST7789_Command::DISPON,
        2, DELAY_COMMAND, 255,
        0
    };

    /**
     * Constructor. Note - constructor calls init
     * @param	cs		Pin used for Chip Select
     * @param	dc		Pin used for Data Control
     * @param	rst		Pin used for Reset (optional. 255=unused)
     * @param	mosi	Pin used for MOSI communication (data out from master)
     * @param	sclk	Pin used for clock
     * @param	width	TFT pixel width
     * @param	Height	TFT pixel height
     **/
    DisplayST7789::DisplayST7789(DisplaySize sz, uint8_t cs, uint8_t dc, uint8_t rst, uint8_t mosi, uint8_t sclk, uint8_t bklt, uint8_t scale) {
        _cs = cs;
        _dc = dc;
        _rst = rst;
        _mosi = mosi;
        _sclk = sclk;
        _miso = 255;
        _bklt = bklt;
        _bkltPWM = false;
        switch (sz) {
            case DisplaySize::Size240x135:
                _o = DisplayOrientation::Landscape;
                _hwSize.setSize(240, 135);
                _xoffset = (int)((320 - _hwSize.width) / 2);
                _yoffset = (int)((240 - _hwSize.height) / 2);
                break;
            case DisplaySize::Size240x135_flipped:
                _o = DisplayOrientation::LandscapeFlipped;
                _hwSize.setSize(240, 135);
                _xoffset = (int)((320 - _hwSize.width) / 2);
                _yoffset = (int)((240 - _hwSize.height) / 2);
                break;
            case DisplaySize::Size135x240_flipped:
                _o = DisplayOrientation::PortraitFlipped;
                _hwSize.setSize(135, 240);
                _yoffset = (int)((320 - _hwSize.height) / 2);
                _xoffset = (int)((240 - _hwSize.width) / 2);
                break;
            case DisplaySize::Size135x240:
            default:
                _o = DisplayOrientation::Portrait;
                _hwSize.setSize(135, 240);
                _yoffset = (int)((320 - _hwSize.height) / 2);
                _xoffset = (int)((240 - _hwSize.width) / 2);
                break;
        }
        _pf = PixelFormat::RGB565;
        _px = scale == 0 ? 1 : scale;
        _size.setSize(_hwSize.width / _px, _hwSize.height / _px);

        // Initialise SPI
        init();
        beginTransaction();
        commandSequence(init_commands);
        setOrientation(_o);
        endTransaction();

        // Ready to send data
        ready = true;
    }

    void DisplayST7789::setArea(LineBufferData& buffer) {
        writeCommand(ST7789_Command::CASET); // Column addr set
        writeData16((buffer.rect.x * _px) + _xoffset);
        writeData16(((buffer.rect.x2 + 1) * _px) - 1 + _xoffset);

        writeCommand(ST7789_Command::RASET); // Row addr set
        writeData16((buffer.rect.y * _px) + _yoffset);
        writeData16(((buffer.rect.y2 + 1) * _px) - 1 + _yoffset);

        // Tell display we are about to send data
        writeCommand(ST7789_Command::RAMWR);
    }

    void DisplayST7789::setOrientation(DisplayOrientation o) {
        writeCommand(ST7789_Command::MADCTL);
        switch (o) {
            case DisplayOrientation::Landscape:
                writeData8_last(ST7789_MADCTL::MY | ST7789_MADCTL::MV | ST7789_MADCTL::RGB);
                break;
            case DisplayOrientation::LandscapeFlipped:
                writeData8_last(ST7789_MADCTL::MX | ST7789_MADCTL::MV | ST7789_MADCTL::RGB);
                break;
            case DisplayOrientation::PortraitFlipped:
                writeData8_last(ST7789_MADCTL::MX | ST7789_MADCTL::MY | ST7789_MADCTL::RGB);
                break;
            case DisplayOrientation::Portrait:
            case DisplayOrientation::Default:
            default:
                writeData8_last(ST7789_MADCTL::RGB);
                break;
        }
    }

} // namespace
