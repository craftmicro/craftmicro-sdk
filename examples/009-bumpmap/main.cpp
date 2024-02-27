#include <CraftMicro.h>
#include "TFT_eSPI_display.h"
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
    // Create a new application. Scale all pixels to 2x2
    app = new App(new TFTDisplay(0, 2));

    // Set background color
    app->stage->backgroundColor(Color8888::SaddleBrown);

    // Create a box and add it to the centre of the stage
    box = Box::Create(app->stage->width() / 2 - 16, app->stage->height() / 2 - 16, 32, 32);
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