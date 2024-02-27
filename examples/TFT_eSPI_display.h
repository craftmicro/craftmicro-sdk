#pragma once

#include <TFT_eSPI.h>

/**
 * @brief Create an interface to the display using TFT_eSPI
 *
 * Make sure you follow the instructions for TFT_eSPI to set up your display
 */
class TFTDisplay : public Display {
public:
    TFT_eSPI tft = TFT_eSPI();

    /**
     * @brief Construct a new TFTDisplay object
     *
     * @param rotation      Display rotation
     * @param pixelScale    The amount to scale pixels by (1 = no scaling, 2 = double size, etc.)
     */
    TFTDisplay(int rotation = 0, int pixelScale = 1) {
        tft.init();
        tft.setRotation(rotation);
        tft.fillScreen(TFT_BLACK);

        this->pixelScale = pixelScale;
        pixelFormat = PixelFormat::RGB565;
        width = tft.width();
        height = tft.height();
    }
    void drawBegin(ClipRect* rect) override {
        tft.startWrite();
        tft.setAddrWindow(rect->x, rect->y, rect->width, rect->height);
    }
    inline void draw565(color565 color) override {
        tft.pushBlock(color, 1);
    }
    void drawEnd() override {
        tft.endWrite();
    }
};

