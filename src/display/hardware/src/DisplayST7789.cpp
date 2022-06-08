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
			COLMOD = 0x3A,

			DELAY = 0xFF, // Delay (not an ST7789 command, but interpreted as a delay)
		};
	}

	static const uint8_t init_commands[] = {
		1, ST7789_Command::SWRESET,								 // Software reset (no args)
		2, ST7789_Command::DELAY, 150,							 // Delay 150ms
		1, ST7789_Command::SLPOUT,								 // Out of sleep mode (no args)
		2, ST7789_Command::DELAY, 10,							 // Delay 10ms
		2, ST7789_Command::COLMOD, 0x55,						 // Set color mode to 16b color
		2, ST7789_Command::DELAY, 10,							 // Delay 10ms
		2, ST7789_Command::MADCTL, 0x08,						 // Mem access ctrl (directions). Row/col addr, bottom-top refresh
		5, ST7789_Command::CASET, 0x00, 0, 0, 240,				 // Column addr set
		5, ST7789_Command::RASET, 0x00, 0, 320 >> 8, 320 & 0xff, // Row addr set
		1, ST7789_Command::INVON,								 // Invert display on (hack)
		2, ST7789_Command::DELAY, 10,							 // Delay 10ms
		1, ST7789_Command::NORON,								 // Normal display on
		2, ST7789_Command::DELAY, 10,							 // Delay 10ms
		1, ST7789_Command::DISPON,								 // Turn display on
		2, ST7789_Command::DELAY, 10,							 // Delay 10ms
		2, ST7789_Command::MADCTL, 0xC0,						 // Normal rotation
		0														 // End
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
			case DisplaySize::Size135x240:
			default:
				// Important! If hardware rotation is ever implemented, these offsets
				// are actually different for the different rotations.
				_hwSize.setSize(135, 240);
				_yoffset = (int)((320 - _hwSize.height) / 2);
				_xoffset = (int)((240 - _hwSize.width + 1) / 2);
		}
		_pf = PixelFormat::RGB565;
		_px = scale;
		_size.setSize(_hwSize.width >> _px, _hwSize.height >> _px);

		// Initialise SPI
		init();

		// Send init commands
		beginTransaction();
		const uint8_t* addr = init_commands;
		uint8_t c;
		while (1) {
			uint8_t count = *addr++;
			if (count-- == 0)
				break;
			c = *addr++;
			if (c == ST7789_Command::DELAY) {
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
		writeCommand_last(ST7789_Command::SLPOUT); // Exit Sleep
		endTransaction();

		// Turn on the display after a delay
		delay(120);
		beginTransaction();
		writeCommand_last(ST7789_Command::DISPON); // Display on
		endTransaction();

		// Turn on the backlight
		if (_bklt != 255) {
			pinMode(_bklt, OUTPUT);
			backlight(1.0);
		}
	}


	/**
	 * Update the linebuffer to the display
	 * @param	continuous	If true, will continuously refresh until stopRefresh is called
	 **/
	void DisplayST7789::draw(LineBufferData& buffer) {
		// Set not ready
		ready = false;

		// Begin the transmission to hardware
		beginTransaction();

		// Set the area of the display to write to
		writeCommand(ST7789_Command::CASET); // Column addr set
		writeData16(buffer.rect.x << _px);
		writeData16(((buffer.rect.x2 + 1) << _px) - 1);

		writeCommand(ST7789_Command::RASET); // Row addr set
		writeData16(buffer.rect.y << _px);
		writeData16(((buffer.rect.y2 + 1) << _px) - 1);

		// Tell display we are about to send data
		writeCommand(ST7789_Command::RAMWR);

		// Write pixels. For some reason this SPI implementation requires the final
		// pixel to be written differently, so we need to keep track of the count
		int scale = 1 << _px;
		int count = buffer.rect.width * scale * buffer.rect.height * scale;
		int lineOffset = 0;
		for (uint16_t y = buffer.rect.y; y <= buffer.rect.y2; y++) {
			for (uint16_t i = 0; i < scale; i++) {
				for (uint16_t x = buffer.rect.x; x <= buffer.rect.x2; x++) {
					for (uint16_t j = 0; j < scale; j++) {
						if (--count) writeData16(to565(buffer.pixels[lineOffset + x]));
						else writeData16_last(to565(buffer.pixels[lineOffset + x]));
					}
				}
			}
			lineOffset += _size.width;
		}
		// Done with complete transaction
		endTransaction();

		// Set ready to send data
		ready = true;
	}


} // namespace
