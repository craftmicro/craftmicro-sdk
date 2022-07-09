#include <CraftMicro.h>
#include "resources/normalmap.h"

using namespace craft;

App* app;
Box* box;
BumpFilter* filter;
Light* light;

// Runs on every render cycle
bool onRenderFrame(uint32_t event, void* data) {
    // Change the direction of the light source (circular)
    light->direction += 0.01;
    light->update();

    box->dirty(); // Force the box to redraw

    return true;
}

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

    // Create a box and add it to the centre of the stage
    box = Box::Create(app->display->width() / 2 - 16, app->display->height() / 2 - 16, 32, 32);
    app->stage->addChild(box);
    box->color = Color8888::Orange;

    // Add a bump filter with a light source
    light = Light::Create(LightType::Directional);
    light->strength = 0.5;
    filter = BumpFilter::Create(&normalmap, 0, light);
    box->filters = filter;

    // Listen for the update_render event. This runs the 'onRenderFrame' function on
    // every render cycle. We use this to animate the light source to show the effect
  // of the bump filter
    app->messenger->addListener(Event::update_render, new CallbackListener(onRenderFrame));
}

void loop() {
    app->update();
}