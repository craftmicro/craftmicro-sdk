#include <CraftMicro.h>
#include "TFT_eSPI_display.h"
#include "resources/asterix.h"
#include "resources/obelix.h"
#include "resources/dogmatix.h"

using namespace craft;

App* app;
Sprite* asterixSprite;
Sprite* obelixSprite;
Sprite* dogmatixSprite;

void setup() {
    // Create a new application. Scale all pixels to 2x2
    app = new App(new TFTDisplay(0, 1, 2));

    // Set background color
    app->stage->backgroundColor(Color8888::SaddleBrown);

    // Create an Asterix sprite and put it on the stage
    asterixSprite = Sprite::Create(&asterix, 0);
    app->stage->addChild(asterixSprite);
    asterixSprite->origin(OriginType::centerBottom, true);
    asterixSprite->x(app->stage->width() / 2 - 18);
    asterixSprite->y(app->stage->height() - 5);

    // Create an Obelix sprite and put it on the stage
    obelixSprite = Sprite::Create(&obelix, 0);
    app->stage->addChild(obelixSprite);
    obelixSprite->origin(OriginType::centerBottom, true);
    obelixSprite->x(app->stage->width() / 2 + 18);
    obelixSprite->y(app->stage->height() - 5);

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
