#include <CraftMicro.h>
#include "resources/asterix.h"
#include "resources/obelix.h"
#include "resources/dogmatix.h"

using namespace craft;

App* app;
Sprite* asterixSprite;
Sprite* obelixSprite;
Sprite* dogmatixSprite;

void setup() {
    // Create a new application
    // Use a 320x240 ILI9341 display, and scale all pixels to 2x2 (effective size is 160x120)
    // Use a single-line line buffer for low memory consumption
    app = new App(
        new DisplayILI9341(DisplaySize::Size320x240, 10, 15, 4, 11, 13, 12, 6, PixelScale::x2),
        LineBufferHeight::singleLine
    );
    // Set background color
    app->stage->backgroundColor(Color8888::SaddleBrown);

    // Create an Asterix sprite and put it on the stage
    asterixSprite = Sprite::Create(&asterix);
    app->stage->addChild(asterixSprite);
    asterixSprite->origin(OriginType::centerBottom, true);
    asterixSprite->x(50);
    asterixSprite->y(100);

    // Create an Obelix sprite and put it on the stage
    obelixSprite = Sprite::Create(&obelix);
    app->stage->addChild(obelixSprite);
    obelixSprite->origin(OriginType::centerBottom, true);
    obelixSprite->x(100);
    obelixSprite->y(100);

    // Add a Dogmatix sprite and add it as a child of Obelix.
    // This means that it will move with Obelix and is treated as
    // part of obelix.
    dogmatixSprite = Sprite::Create(&dogmatix);
    obelixSprite->addChild(dogmatixSprite);
    dogmatixSprite->origin(OriginType::centerBottom, true);
    dogmatixSprite->x(-16);
    dogmatixSprite->y(0);
}

void loop() {
    // Call update as often as possible
    app->update();
}
