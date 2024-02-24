#include "../Display.h"

namespace craft {

    /**
     * Update the linebuffer to the display
     **/
    void Display::draw(LineBufferData& buffer, int bufferWidth) {
        switch (pixelFormat) {
            case PixelFormat::RGB888:
                draw888(buffer, bufferWidth);
                break;
            case PixelFormat::RGB565:
            default:
                draw565(buffer, bufferWidth);
                break;
        }
    }

    /**
     * Update the linebuffer to the display for 16-bit pixel formats
     **/
    void Display::draw565(LineBufferData& buffer, int bufferWidth) {
        if (pixelScale == 1) {
            int lineOffset = 0;
            int sx = _x;
            for (uint16_t y = buffer.rect.y; y <= buffer.rect.y2; y++) {
                for (uint16_t x = buffer.rect.x; x <= buffer.rect.x2; x++) {
                    drawPixel565(to565(buffer.pixels[lineOffset + x]));
                    _x++;
                }
                _x = sx;
                _y++;
                lineOffset += bufferWidth;
            }
        }
        else {
            int lineOffset = 0;
            int sx = _x;
            for (uint16_t y = buffer.rect.y; y <= buffer.rect.y2; y++) {
                for (uint16_t i = 0; i < pixelScale; i++) {
                    for (uint16_t x = buffer.rect.x; x <= buffer.rect.x2; x++) {
                        for (uint16_t j = 0; j < pixelScale; j++) {
                            drawPixel565(to565(buffer.pixels[lineOffset + x]));
                            _x++;
                        }
                    }
                    _x = sx;
                    _y++;
                }
                lineOffset += bufferWidth;
            }
        }
    }

    /**
     * Update the linebuffer to the display
     **/
    void Display::draw888(LineBufferData& buffer, int bufferWidth) {
        if (pixelScale == 1) {
            int lineOffset = 0;
            int sx = _x;
            for (uint16_t y = buffer.rect.y; y <= buffer.rect.y2; y++) {
                for (uint16_t x = buffer.rect.x; x <= buffer.rect.x2; x++) {
                    drawPixel888(buffer.pixels[lineOffset + x]);
                    _x++;
                }
                _x = sx;
                _y++;
                lineOffset += bufferWidth;
            }
        }
        else {
            int lineOffset = 0;
            int sx = _x;
            for (uint16_t y = buffer.rect.y; y <= buffer.rect.y2; y++) {
                for (uint16_t i = 0; i < pixelScale; i++) {
                    for (uint16_t x = buffer.rect.x; x <= buffer.rect.x2; x++) {
                        for (uint16_t j = 0; j < pixelScale; j++) {
                            drawPixel888(buffer.pixels[lineOffset + x]);
                            _x++;
                        }
                    }
                    _x = sx;
                    _y++;
                }
                lineOffset += bufferWidth;
            }
        }
    }

} // namespace craft