#include <CraftMicro.h>

using namespace craft;

App* app;

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
}

void loop() {
    // Call update as often as possible
    app->update();
}
