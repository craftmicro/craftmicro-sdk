#include "../Display.h"

namespace craft {

    // Draw funcs

    void drawPixel565(int x, int _y, uint32_t c, int pixelScale, bool hasFramebuffer, void* buffer, int width) {
        uint16_t color = to565(c);
        uint16_t* bf = (uint16_t*)buffer;
        x *= pixelScale;
        int y = hasFramebuffer ? _y : 0;
        int index = y * width + x;
        for (int py = 0; py < pixelScale; py++) {
            for (int px = 0; px < pixelScale; px++) {
                bf[index + px] = color;
            }
            index += width;
        }
    }

    void drawPixel888(int x, int _y, uint32_t color, int pixelScale, bool hasFramebuffer, void* buffer, int width) {
        uint8_t* bf = (uint8_t*)buffer;
        uint8_t r = red(color);
        uint8_t g = green(color);
        uint8_t b = blue(color);
        x *= pixelScale;
        int y = hasFramebuffer ? _y : 0;
        int index = (y * width + x) * 3;
        for (int py = 0; py < pixelScale; py++) {
            for (int px = 0; px < pixelScale; px++) {
                bf[index + px + 0] = r;
                bf[index + px + 1] = g;
                bf[index + px + 2] = b;
            }
            index += width * 3;
        }
    }

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
        if (pixelFormat == PixelFormat::RGB565) {
            _drawFunc = drawPixel565;
            if (!_hasFramebuffer) {
                framebuffer = new uint16_t[width * pixelScale];
            }
        }
        else if (pixelFormat == PixelFormat::RGB888) {
            _drawFunc = drawPixel888;
            if (!_hasFramebuffer) {
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

    void Display::_draw(int x, color8888 color) {
        _drawFunc(x, _y, color, pixelScale, _hasFramebuffer, framebuffer, width);
    }

} // namespace craft