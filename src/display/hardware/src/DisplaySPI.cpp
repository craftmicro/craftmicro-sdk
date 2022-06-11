#include "../DisplaySPI.h"

namespace craft {

    /**
     * Update the linebuffer to the display
     **/
    void DisplaySPI::draw(LineBufferData& buffer) {
        // Set not ready
        ready = false;

        // Begin the transmission to hardware
        beginTransaction();

        // Set the area of the display to write to
        setArea(buffer);

        // Write pixels. Some SPI implementations require the final pixel
        // to be written differently, so we need to keep track of the count
        if (_px == PixelScale::x1) {
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
        }
        // Done with complete transaction
        endTransaction();

        // Set ready to send data
        ready = true;
    }

} // namespace craft