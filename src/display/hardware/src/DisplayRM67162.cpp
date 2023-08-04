#include "../DisplayRM67162.h"

namespace craft {
    /**
     * Define RM67162 commands
     **/
    namespace RM67162_Command {
        enum {
            NOP = 0x00,
            SWRESET = 0x01,		    // Resets the commands and parameters to their S/W Reset default values
            RDDID = 0x04,		    // Read display identification information (return 24bits)

            SLPIN = 0x10,		    // Enter sleep mode
            SLPOUT = 0x11,		    // Turns off sleep mode
            RDPIXFMT = 0x0C,        // Read pixel format

            INVOFF = 0x20,		    // Exit display inversion mode
            INVON = 0x21,		    // Enter into display inversion mode
            DISPOFF = 0x28,		    // Display off
            DISPON = 0x29,		    // Display on

            CASET = 0x2A,		    // Column Address Set
            PASET = 0x2B,		    // Page Address Set
            RAMWR = 0x2C,		    // Memory Write
            RAMRD = 0x2E,		    // Memory Read

            TELOFF = 0x34,          // Tearing effect line off
            TELON = 0x35,           // Tearing effect line on
            SCANMD = 0x36,          // Scan mode
            IDLOFF = 0x38,          // Idle mode off
            IDLON = 0x39,           // Idle mode on
            PIXFMT = 0x3A,          // Interface Pixel Format (Data format select)
            RAMWC = 0x3C,           // Memory continuous write
            RAMRC = 0x3E,           // Memory continuous read  

            TESET = 0x44,           // Set tear scan-line  

            DSPCTL = 0x53,          // Set write display control 

            DTYSET = 0xB0,          // Duty setting
            FRMCTR = 0xB2,          // Frame rate control
            UPDTEQ = 0xB4,          // Update period gate EQ control
            DSTREQ = 0xB5,          // Destress period gate EQ control
            PANSET = 0xB8,          // Panel setting
            SRCSET = 0xB9,          // Source setting

            GTVCTR = 0xC0,		    // Gate volume control
            DSPIST = 0xC4,          // Set DSPI mode
            OSCEN = 0xC7,           // OSC Enable
            VCVCTR = 0xC8,          // VCOMH volume control

            BSTEN = 0xD1,           // Booster enable

            SPISEL = 0xE4,          // 4-SPI Input select
            MTBCTR = 0xEB,          // MTP load control
        };
    };

    /**
     * Initialise the display. Called from the constructor.
     * More info here: https://github.com/eframt/sparkfun_edge_prj_template/blob/24cc390581078aee1e6739803a373de516ec15d2/AmbiqSuiteSDK/devices/am_devices_mspi_rm67162.c#L664
     **/
    static const uint8_t init_commands[] = {
        2,      RM67162_Command::TELON, 0x00,               // Enable tearing effect
        2,      RM67162_Command::DSPIST, 0x80,              // Set DSPI mode (0x80=SPI, 0x81=DSPI)
        2,      RM67162_Command::PIXFMT, 0x75,              // Pixel format (0x72=8bit, 0x71=3bit, 0x75=16bit, 0x77=24bit)
        2,      RM67162_Command::SCANMD, 0x40,              // Scan mode (orientation? 0x40=0, 0x70=90, 0x10=180, 0x00=270)
        2,      RM67162_Command::DSPCTL, 0x20,              // Set write display control
        // Reference sets display area here. Omitting
        3,      RM67162_Command::TESET, 0x00, 0x28,         // Set tear scanline
        1,      RM67162_Command::SLPOUT,                    // Sleep out
        2,      DELAY_COMMAND, 130,                         // Delay 130ms
        0
    };

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
    DisplayRM67162::DisplayRM67162(DisplaySize sz, uint8_t cs, uint8_t dc, uint8_t rst, uint8_t mosi, uint8_t sclk, uint8_t bklt, uint8_t scale) {
        _cs = cs;
        _dc = dc;
        _rst = rst;
        _mosi = mosi;
        _sclk = sclk;
        _miso = 255;
        _bklt = bklt;
        _bkltPWM = false;
        switch (sz) {
            case DisplaySize::Size320x240:
            default:
                _hwSize.setSize(320, 240);
                _o = DisplayOrientation::Landscape;
        }
        _pf = PixelFormat::RGB565; // Can support 24bit, but need to update init_commands as well
        _px = scale == 0 ? 1 : scale;
        _size.setSize(_hwSize.width / _px, _hwSize.height / _px);

        // Initialise SPI
        init();

        // Send init commands
        beginTransaction();
        commandSequence(init_commands);
        writeCommand_last(RM67162_Command::DISPON);    // Display on
        endTransaction();
        delay(200);

        // Ready to send data
        ready = true;
    }

    void DisplayRM67162::setArea(ClipRect& rect) {
        writeCommand(RM67162_Command::CASET); // Column addr set
        writeData16(rect.x * _px);
        writeData16((rect.x2 + 1 * _px) - 1);

        writeCommand(RM67162_Command::PASET); // Row addr set
        writeData16(rect.y * _px);
        writeData16((rect.y2 + 1 * _px) - 1);

        // Tell display we are about to send data
        writeCommand(RM67162_Command::RAMWR);
    }

} // namespace craft
