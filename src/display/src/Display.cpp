#include "../Display.h"

namespace craft {

    /**
     * Initialise after user-values have been defined
     */
    void Display::mount() {
        rect.setSize((int)(width / pixelScale), (int)(height / pixelScale));
    }

    /**
     * Draw a pixel to the display
     **/
    void Display::draw(int x, int y, uint32_t color, float_t a) {
        switch (pixelFormat) {
            case PixelFormat::RGB888:
                if (a == 1.0f) {
                    draw888(x, y, color);
                }
                else if (a > 0.0f) {
                    blend888(x, y, color, a);
                }
                break;
            case PixelFormat::RGB565:
            default:
                if (a == 1.0f) {
                    draw565(x, y, to565(color));
                }
                else if (a > 0.0f) {
                    blend565(x, y, to565(color), a);
                }
                break;
        }
    }

    void Display::draw565(int x, int y, uint16_t color) {
        uint16_t* buffer = (uint16_t*)framebuffer;
        x *= pixelScale;
        y *= pixelScale;
        int index = y * width + x;
        for (int py = 0; py < pixelScale; py++) {
            for (int px = 0; px < pixelScale; px++) {
                buffer[index + px] = color;
            }
            index += width;
        }
    }

    void Display::blend565(int x, int y, uint16_t color, float_t a) {
        uint16_t* buffer = (uint16_t*)framebuffer;
        x *= pixelScale;
        y *= pixelScale;
        int index = y * width + x;
        color = blend565a8(color, buffer[index], a * 255);
        for (int py = 0; py < pixelScale; py++) {
            for (int px = 0; px < pixelScale; px++) {
                buffer[index + px] = color;
            }
            index += width;
        }
    }

    void Display::draw888(int x, int y, uint32_t color) {
        uint8_t* buffer = (uint8_t*)framebuffer;
        uint8_t r = red(color);
        uint8_t g = green(color);
        uint8_t b = blue(color);
        x *= pixelScale;
        y *= pixelScale;
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

    void Display::blend888(int x, int y, uint32_t color, float_t a) {
        uint8_t* buffer = (uint8_t*)framebuffer;
        x *= pixelScale;
        y *= pixelScale;
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