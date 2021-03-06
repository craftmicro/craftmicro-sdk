#include <CraftMicro.h>
#include "resources/font_PixelSix.h"

using namespace craft;

App* app;
Text* text;

void setup() {
    // Create a new application
    // Use a 320x240 ILI9341 display, and scale all pixels to 2x2 (effective size is 160x120)
    // Use a single-line line buffer for low memory consumption
    app = new App(
        new DisplayILI9341(DisplaySize::Size320x240, 10, 15, 4, 11, 13, 12, 6, 2),
        LineBufferHeight::singleLine
    );
    // Set background color
    app->stage->backgroundColor(Color8888::SaddleBrown);

    // Create a text object usiing the "PixelSix" font
    text = Text::Create(&PixelSix);
    text->text(S("All children, except one, grow up. They soon know that they will grow up, and the way Wendy knew was this."));
    text->width(app->display->width() - 50);
    text->x(40);
    text->y(10);
    text->color(Color8888::White);
    // Add the text to the stage so that it can be rendered
    app->stage->addChild(text);
}

void loop() {
    // Call update as often as possible
    app->update();
}