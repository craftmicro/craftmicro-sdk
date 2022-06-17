#include <CraftMicro.h>

using namespace craft;

App* app;
Box* box;

LinearGradient* gradient;
float_t angle = 0;
float_t center_x = 0;
float_t center_y = 0;

// Runs on every render cycle. Spins the gradient around
// in a circle and changes it's size.
boolean onRenderFrame(uint32_t event, void* data) {
    angle += 0.05;
    if (angle > (M_PI * 2)) angle -= M_PI * 2;
    float_t r = center_x + center_x * 0.5 * cosf(angle * 5);
    float_t c = cosf(angle) * r;
    float_t s = sinf(angle) * r;
    gradient->position(
        center_x - c, center_y + s,
        center_x + c, center_y - s
    );
    box->dirty();

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

    // Create a box
    box = Box::Create();
    app->stage->addChild(box);
    box->id = 22;
    box->x(10);
    box->y(10);
    box->width(app->display->width() - 20);
    box->height(app->display->height() - 20);

    // Create a gradient and add 6 stops for a rainbox effect. The 
    // gradient is applied to the box.
    center_x = (app->display->width() - 20) / 2;
    center_y = (app->display->height() - 20) / 2;
    gradient = LinearGradient::Create(6);
    gradient->stop(0, Color8888::Red, 1.0, 0.0)
        ->stop(1, Color8888::Orange, 1.0, 0.2)
        ->stop(2, Color8888::Yellow, 1.0, 0.4)
        ->stop(3, Color8888::Green, 1.0, 0.6)
        ->stop(4, Color8888::Indigo, 1.0, 0.8)
        ->stop(5, Color8888::Violet, 1.0, 1.0);
    gradient->position(center_x, 10, center_x, app->display->height() - 10);
    box->gradient = gradient;

    // Listen for the update_render event. This runs the 'onRenderFrame' function on
    // every render cycle. We use this to animatet the gradient.
    app->messenger->addListener(Event::update_render, new CallbackListener(onRenderFrame));
}

void loop() {
    app->update();
}
