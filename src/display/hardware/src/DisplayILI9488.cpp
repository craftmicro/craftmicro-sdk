#include "../DisplayILI9488.h"

namespace craft {
    /**
     * Define ILI9488 commands
     **/
    namespace ILI9488_Command {
        enum {
            NOP = 0x00,
            SWRESET = 0x01,		// Resets the commands and parameters to their S/W Reset default values
            RDDID = 0x04,		// Read display identification information (return 24bits)
            RDDST = 0x09,		// Read display status 

            SLPIN = 0x10,		// Enter sleep mode
            SLPOUT = 0x11,		// Turns off sleep mode
            PTLON = 0x12,		// Turns on partial mode
            NORON = 0x13,		// Returns the display to normal mode (aprtial mode off)

            RDMODE = 0x0A,
            RDMADCTL = 0x0B,
            RDPIXFMT = 0x0C,
            RDIMGFMT = 0x0D,
            RDSELFDIAG = 0x0F,

            INVOFF = 0x20,		// Recover from display inversion mode
            INVON = 0x21,		// Enter into display inversion mode
            GAMMASET = 0x26,		// Select the desired Gamma curve (only 01 is defined)
            DISPOFF = 0x28,		// Display off
            DISPON = 0x29,		// Display on

            CASET = 0x2A,		// Column Address Set
            PASET = 0x2B,		// Page Address Set
            RAMWR = 0x2C,		// Memory Write
            RGBSET = 0x2D,		// Color Set
            RAMRD = 0x2E,		// Memory Read

            PTLAR = 0x30,
            MADCTL = 0x36,
            VSCRSADD = 0x37,
            PIXFMT = 0x3A,

            INTFCCTR = 0xB0,

            FRMCTR1 = 0xB1,
            FRMCTR2 = 0xB2,
            FRMCTR3 = 0xB3,
            INVCTR = 0xB4,
            DFUNCTR = 0xB6,
            EMTRYSET = 0xB7,

            PWCTR1 = 0xC0,		// Power control
            PWCTR2 = 0xC1,
            PWCTR3 = 0xC2,
            PWCTR4 = 0xC3,
            PWCTR5 = 0xC4,
            VMCTR1 = 0xC5,		// Set the VCOM voltage
            VMCTR2 = 0xC7,

            RDID1 = 0xDA,
            RDID2 = 0xDB,
            RDID3 = 0xDC,
            RDID4 = 0xDD,

            GMCTRP1 = 0xE0,		// Positive Gamma correction
            GMCTRN1 = 0xE1,     // Negative Gamma correction

            IFCTL = 0xF6,       // Interface Control
            ADJCTR3 = 0xF7
        };
    };

    /**
     * Initialise the display. Called from the constructor.
     **/
    static const uint8_t init_commands[] = {
        16, 	ILI9488_Command::GMCTRP1, 0x00, 0x03, 0x09, 0x08, 0x16, 0x0A, 0x3F, 0x78, 0x4C, 0x09, 0x0A, 0x08, 0x16, 0x1A, 0x0F, // Positive Gamma Control
        16,     ILI9488_Command::GMCTRN1, 0x00, 0x16, 0x19, 0x03, 0x0F, 0x05, 0x32, 0x45, 0x46, 0x04, 0x0E, 0x0D, 0x35, 0x37, 0x0F, // Negative Gamma Control
        3,      ILI9488_Command::PWCTR1, 0x17, 0x15,// Power Control 1
        2,      ILI9488_Command::PWCTR2, 0x41,      // Power Control 2
        4,      ILI9488_Command::VMCTR1, 0x00, 0x12, 0x80,          // VCOM Control
        2,      ILI9488_Command::MADCTL, 0x48,      // Memory Access Control, MX, BGR
        2,      ILI9488_Command::PIXFMT, 0x66,      // Pixel Interface Format, 18 bit colour for SPI
        2,      ILI9488_Command::INTFCCTR, 0x00,    // Interface Mode Control
        2,      ILI9488_Command::FRMCTR1, 0xA0,     // Frame Rate Control
        2,      ILI9488_Command::INVCTR, 0x02,      // Display Inversion Control
        4,      ILI9488_Command::DFUNCTR, 0x02, 0x02, 0x3B,         // Display Function Control
        2,      ILI9488_Command::EMTRYSET, 0xC6,    // Entry Mode Set
        5,      ILI9488_Command::ADJCTR3, 0xA9, 0x51, 0x2C, 0x82,   // Adjust Control 3
        1,      ILI9488_Command::SLPOUT,            // Exit Sleep
        2,      DELAY_COMMAND, 120,                 // Delay 120ms
        0
    };

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
    DisplayILI9488::DisplayILI9488(DisplaySize sz, uint8_t cs, uint8_t dc, uint8_t rst, uint8_t mosi, uint8_t sclk, uint8_t miso, uint8_t bklt, uint8_t scale) {
        _cs = cs;
        _dc = dc;
        _rst = rst;
        _mosi = mosi;
        _sclk = sclk;
        _miso = miso;
        _bklt = bklt;
        _bkltPWM = false;
        DisplayOrientation so = DisplayOrientation::Default;
        switch (sz) {
            case DisplaySize::Size480x320:
                _hwSize.setSize(480, 320);
                so = DisplayOrientation::Landscape;
                break;
            case DisplaySize::Size320x480:
            default:
                _hwSize.setSize(320, 480);
                _o = DisplayOrientation::Portrait;
                so = _o;
        }
        _pf = PixelFormat::RGB888;
        _px = scale == 0 ? 1 : scale;
        _size.setSize(_hwSize.width / _px, _hwSize.height / _px);

        // Initialise SPI
        init();

        // Send init commands
        beginTransaction();
        commandSequence(init_commands);
        writeCommand_last(ILI9488_Command::DISPON);    // Display on
        endTransaction();

        // Rotate display
        setOrientation(so);

        // Ready to send data
        ready = true;
    }

    void DisplayILI9488::setOrientation(DisplayOrientation o) {
        if (_o == o) return;
        _o = o;
        beginTransaction();
        writeCommand(ILI9488_Command::MADCTL);
        switch (_o) {
            case DisplayOrientation::Landscape:
                writeData8_last(0x20 | 0x08);
                break;
            case DisplayOrientation::Default:
            case DisplayOrientation::Portrait:
                writeData8_last(0x40 | 0x08);
                break;
            case DisplayOrientation::LandscapeFlipped:
                writeData8_last(0x40 | 0x80 | 0x20 | 0x08);
                break;
            case DisplayOrientation::PortraitFlipped:
                writeData8_last(0x80 | 0x08);
                break;
        }
        endTransaction();
    }

    void DisplayILI9488::setArea(ClipRect& rect) {
        writeCommand(ILI9488_Command::CASET); // Column addr set
        writeData16(rect.x * _px);
        writeData16((rect.x2 + 1) * _px - 1);

        writeCommand(ILI9488_Command::PASET); // Row addr set
        writeData16(rect.y * _px);
        writeData16((rect.y2 + 1 * _px) - 1);

        // Tell display we are about to send data
        writeCommand(ILI9488_Command::RAMWR);
    }

} // namespace craft
