#include <CraftMicro.h>
#include "TFT_eSPI_display.h"
#include "resources/asterix.h"
#include "resources/obelix.h"
#include "resources/dogmatix.h"

using namespace craft;

App* app;
Box* box;
Box* box2;
Sprite* asterixSprite;
Sprite* obelixSprite;
Sprite* dogmatixSprite;

void setup() {
    // Create a new application. Scale all pixels to 2x2
    app = new App(new TFTDisplay(0, 2));

    // Set background color
    app->stage->backgroundColor(Color8888::White);

    uint16_t w = floor(app->stage->width() / 2) - 10;
    uint16_t h = floor(app->stage->height()) - 20;

    // On the left we will add an orange box and mask it
    // with the Asterix sprite. Only the part of the box
    // under the mask (under Asterix) should be drawn.
    box = Box::Create();
    box->set(10, 10, w, h);
    app->stage->addChild(box);
    box->color = Color8888::Orange;
    box->id = 1;

    asterixSprite = Sprite::Create(&asterix, 0);
    box->addChild(asterixSprite);
    asterixSprite->origin(OriginType::centerBottom, true);
    asterixSprite->x(30);
    asterixSprite->y(70);
    asterixSprite->mask = MaskType::mask;
    asterixSprite->id = 11;

    // On the right we will add a red box and INVERSE mask it
    // with the Obelix sprite. The part under the mask will not
    // be drawn, but all other parts will.
    box2 = Box::Create();
    box2->set(w + 10, 10, w, h);
    app->stage->addChild(box2);
    box2->color = Color8888::IndianRed;
    box2->id = 2;

    obelixSprite = Sprite::Create(&obelix, 0);
    box2->addChild(obelixSprite);
    obelixSprite->origin(OriginType::centerBottom, true);
    obelixSprite->x(40);
    obelixSprite->y(70);
    obelixSprite->mask = MaskType::inverse;
    obelixSprite->id = 21;

    // now we will just draw add the dogmatix sprite with no
    // masking, just for fun :)
    dogmatixSprite = Sprite::Create(&dogmatix, 0);
    box2->addChild(dogmatixSprite);
    dogmatixSprite->origin(OriginType::centerBottom, true);
    dogmatixSprite->x(1);
    dogmatixSprite->y(70);
}

void loop() {
    app->update();
}
