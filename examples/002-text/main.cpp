#include <CraftMicro.h>
#include "TFT_eSPI_display.h"
#include "resources/font_PixelSix.h"

using namespace craft;

App* app;
Text* text;

void setup() {
    // Create a new application. Scale all pixels to 2x2
    app = new App(new TFTDisplay(0, 2));

    // Set background color
    app->stage->backgroundColor(Color8888::SaddleBrown);

    // Create a text object usiing the "PixelSix" font
    text = Text::Create(&PixelSix);
    text->text(S("All children, except one, grow up. They soon know that they will grow up, and the way Wendy knew was this."));
    text->width(app->stage->width() - 50);
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