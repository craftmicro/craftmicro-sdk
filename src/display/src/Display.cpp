#include "../Display.h"

namespace craft {

    Display::~Display() {
        if (!_hasFramebuffer) {
            if (pixelFormat == PixelFormat::RGB565) {
                delete[](uint16_t*)framebuffer;
            }
            else if (pixelFormat == PixelFormat::RGB888) {
                delete[](uint8_t*)framebuffer;
            }
        }
    }

    /**
     * Initialise after user-values have been defined
     */
    void Display::_mount() {
        _rect.setSize((int)(width / pixelScale), (int)(height / pixelScale));
        _hasFramebuffer = framebuffer != nullptr;
        if (!_hasFramebuffer) {
            if (pixelFormat == PixelFormat::RGB565) {
                framebuffer = new uint16_t[width * pixelScale];
            }
            else if (pixelFormat == PixelFormat::RGB888) {
                framebuffer = new uint8_t[width * pixelScale * 3];
            }
        }
    }

    void Display::_drawBegin(ClipRect* area) {
        _w = area->width;
        _x = area->x;
        drawBegin(area);
    }

    void Display::_lineBegin(int y) {
        _y = y * pixelScale;
    }

    void Display::_lineFlush() {
        if (!_hasFramebuffer) {
            if (pixelFormat == PixelFormat::RGB565) {
                int index = _x;
                uint16_t* buffer = (uint16_t*)framebuffer;
                for (int y = 0; y < pixelScale; y++) {
                    for (int x = 0; x < _w; x++) {
                        this->draw565(buffer[index + x]);
                    }
                    index += width;
                }
            }
            else if (pixelFormat == PixelFormat::RGB888) {
                int index = _x * 3;
                uint8_t* buffer = (uint8_t*)framebuffer;
                for (int y = 0; y < pixelScale; y++) {
                    for (int x = 0; x < _w; x++) {
                        this->draw888(to8888(buffer[index + x * 3], buffer[index + x * 3 + 1], buffer[index + x * 3 + 2]));
                    }
                    index += width * 3;
                }
            }
        }
    }

    /**
     * Draw a pixel to the display
     **/
    void Display::_draw(int x, uint32_t color, float_t a) {
        switch (pixelFormat) {
            case PixelFormat::RGB888:
                if (a == 1.0f) {
                    _draw888(x, color);
                }
                else if (a > 0.0f) {
                    _blend888(x, color, a);
                }
                break;
            case PixelFormat::RGB565:
            default:
                if (a == 1.0f) {
                    _draw565(x, to565(color));
                }
                else if (a > 0.0f) {
                    _blend565(x, to565(color), a);
                }
                break;
        }
    }

    void Display::_draw565(int x, uint16_t color) {
        uint16_t* buffer = (uint16_t*)framebuffer;
        x *= pixelScale;
        int y = _hasFramebuffer ? _y : 0;
        int index = y * width + x;
        for (int py = 0; py < pixelScale; py++) {
            for (int px = 0; px < pixelScale; px++) {
                buffer[index + px] = color;
            }
            index += width;
        }
    }

    void Display::_blend565(int x, uint16_t color, float_t a) {
        uint16_t* buffer = (uint16_t*)framebuffer;
        x *= pixelScale;
        int y = _hasFramebuffer ? _y : 0;
        int index = y * width + x;
        color = blend565a8(color, buffer[index], a * 255);
        for (int py = 0; py < pixelScale; py++) {
            for (int px = 0; px < pixelScale; px++) {
                buffer[index + px] = color;
            }
            index += width;
        }
    }

    void Display::_draw888(int x, uint32_t color) {
        uint8_t* buffer = (uint8_t*)framebuffer;
        uint8_t r = red(color);
        uint8_t g = green(color);
        uint8_t b = blue(color);
        x *= pixelScale;
        int y = _hasFramebuffer ? _y : 0;
        int index = (y * width + x) * 3;
        for (int py = 0; py < pixelScale; py++) {
            for (int px = 0; px < pixelScale; px++) {
                buffer[index + px + 0] = r;
                buffer[index + px + 1] = g;
                buffer[index + px + 2] = b;
            }
            index += width * 3;
        }
    }

    void Display::_blend888(int x, uint32_t color, float_t a) {
        uint8_t* buffer = (uint8_t*)framebuffer;
        x *= pixelScale;
        int y = _hasFramebuffer ? _y : 0;
        int index = (y * width + x) * 3;
        uint32_t bg = (buffer[index + 0] << 16) | (buffer[index + 1] << 8) | buffer[index + 2];
        color = blend8888(color, bg, a * 255);
        uint8_t r = red(color);
        uint8_t g = green(color);
        uint8_t b = blue(color);
        for (int py = 0; py < pixelScale; py++) {
            for (int px = 0; px < pixelScale; px++) {
                buffer[index + px + 0] = r;
                buffer[index + px + 1] = g;
                buffer[index + px + 2] = b;
            }
            index += width * 3;
        }
    }

} // namespace craft