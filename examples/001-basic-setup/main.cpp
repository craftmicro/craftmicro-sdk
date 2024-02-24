#include <CraftMicro.h>
#include "TFT_eSPI_display.h"

using namespace craft;

App* app;

void setup() {
    // Create a new application
    app = new App(new TFTDisplay());

    // Set background color
    app->stage->backgroundColor(Color8888::SaddleBrown);
}

void loop() {
    // Call update as often as possible
    app->update();
}
