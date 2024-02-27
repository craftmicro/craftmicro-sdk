#include <CraftMicro.h>
#include "TFT_eSPI_display.h"
#include "resources/font_PixelSix008.h"

using namespace craft;

App* app;
Box* box;
Text* text;

// The pin that the button is connected to
pin BUTTON_PIN = 35;
// Change this to PinType::digitalNC if the button is "normally closed" (i.e. normally HIGH, LOW when pressed)
PinType BUTTON_TYPE = PinType::digital;

// Define custom events we want to capture. These events can be any number > 255 (0-255 are reserved)
typedef enum {
    button_down = 1000,
    button_up = 1001,
    button_click = 1002,
    button_dblclick = 1003,
    button_hold = 1004,
    button_clickhold = 1005,
} CustomEvent;

bool buttonEvent(uint32_t event, void* data) {
    // Perform different action based on the event that we received
    switch (event) {
        case button_down:
            box->color = Color8888::Crimson;
            box->dirty(); // Force the box to rdraw after a change
            break;
        case button_up:
            box->color = Color8888::PaleGreen;
            box->dirty(); // Force the box to rdraw after a change
            break;
        case button_click:
            text->text(S("Click"));
            break;
        case button_dblclick:
            text->text(S("Double-click"));
            break;
        case button_hold:
            text->text(S("Hold"));
            break;
        case button_clickhold:
            text->text(S("Click then hold"));
            break;
    }
    return true;
}

void setup() {
    // Create a new application. Scale all pixels to 2x2
    app = new App(new TFTDisplay(0, 2));

    app->serialBegin();
    // Set background color
    app->stage->backgroundColor(Color8888::SaddleBrown);

    // Create a box to show the state of the button 
    box = Box::Create(10, 10, 20, 20);
    box->color = Color8888::PaleGreen;
    app->stage->addChild(box);

    // Create a text area to show click types
    text = Text::Create(&PixelSix008);
    text->text(S("Press the button"));
    text->width(app->stage->width() - 20);
    text->x(10);
    text->y(40);
    text->color(Color8888::White);
    app->stage->addChild(text);

    // Define which actions we want events fired for
    app->input->map(BUTTON_PIN, BUTTON_TYPE, ClickType::down, CustomEvent::button_down);
    app->input->map(BUTTON_PIN, BUTTON_TYPE, ClickType::up, CustomEvent::button_up);
    app->input->map(BUTTON_PIN, BUTTON_TYPE, ClickType::click, CustomEvent::button_click);           // A quick click of the button
    app->input->map(BUTTON_PIN, BUTTON_TYPE, ClickType::dbl_click, CustomEvent::button_dblclick);    // A quick double-click of the button
    app->input->map(BUTTON_PIN, BUTTON_TYPE, ClickType::hold, CustomEvent::button_hold);             // Hold the button down
    app->input->map(BUTTON_PIN, BUTTON_TYPE, ClickType::click_hold, CustomEvent::button_clickhold);  // A quick click followed by holding the button down

    // Listen for the events we are interested in
    app->messenger->addListener(CustomEvent::button_down, new CallbackListener(buttonEvent));
    app->messenger->addListener(CustomEvent::button_up, new CallbackListener(buttonEvent));
    app->messenger->addListener(CustomEvent::button_click, new CallbackListener(buttonEvent));
    app->messenger->addListener(CustomEvent::button_dblclick, new CallbackListener(buttonEvent));
    app->messenger->addListener(CustomEvent::button_hold, new CallbackListener(buttonEvent));
    app->messenger->addListener(CustomEvent::button_clickhold, new CallbackListener(buttonEvent));
}

void loop() {
    // Call update as often as possible
    app->update();
}
