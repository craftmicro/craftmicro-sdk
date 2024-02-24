#include <CraftMicro.h>
#include "TFT_eSPI_display.h"

// You will need to clone the craftmicro-fonts repo to access these fonts.
// If you are using the Arduino IDE, just clone it to your Arduino libraries
// folder.
// If you have cloned it to a different location, make sure to add the path
// to the library to your include paths. If you are using PlatformIO, it will
// look something like this:
//     build_flags = -I"C:/libraries/craftmicro-fonts/"
//
// These are just a selection of the available fonts.
// Be sure to check out the others!
#include "fonts/alkhemikal.h"
#include "fonts/bangalore.h"
#include "fonts/chunkydunk.h"
#include "fonts/emoticomic.h"
#include "fonts/grapesoda.h"
#include "fonts/greenscreen.h"
#include "fonts/hydratinglip.h"
#include "fonts/pixel_berry.h"
#include "fonts/pixel_love.h"
#include "fonts/pixelpoiiz.h"
#include "fonts/superscript.h"
#include "fonts/westington.h"

using namespace craft;

struct FontEntry {
    const char* name;
    const packedbdf_t* font;
};

App* app;
Text* heading;
Text* body;
int fontIndex = 0;
int fontCount = 12;
uint32_t time = 0;
FontEntry fonts[12] = {
    {
        S("alkhemikal"),
        &alkhemikal
    },
    {
        S("bangalore"),
        &bangalore
    },
    {
        S("chunkydunk"),
        &chunkydunk
    },
    {
        S("emoticomic"),
        &emoticomic
    },
    {
        S("grapesoda"),
        &grapesoda
    },
    {
        S("greenscreen"),
        &greenscreen
    },
    {
        S("hydratinglip"),
        &hydratinglip
    },
    {
        S("pixel_berry"),
        &pixel_berry
    },
    {
        S("pixel_love"),
        &pixel_love
    },
    {
        S("pixelpoiiz"),
        &pixelpoiiz
    },
    {
        S("superscript"),
        &superscript
    },
    {
        S("westington"),
        &westington
    }
};

void setup() {
    // Create a new application. Scale all pixels to 2x2
    app = new App(new TFTDisplay(0, 1, 2));

    // Set background color
    app->stage->backgroundColor(Color8888::SaddleBrown);

    heading = Text::Create(fonts[0].font);
    heading->width(app->stage->width() - 20);
    heading->x(10);
    heading->y(10);
    heading->color(Color8888::Yellow);
    app->stage->addChild(heading);

    // Create the body text object
    body = Text::Create(fonts[0].font);
    body->text(S("All children, except one, grow up. They soon know that they will grow up, and the way Wendy knew was this.\nABCDEFGHIJKLM NOPQRSTUVWXYZ abcdefghijklm nopqrstuvwxyz (0123456789)[a+b=c]"));
    body->width(app->stage->width() - 20);
    body->x(10);
    body->y(10);
    body->lineSpacing(1.25);
    body->color(Color8888::White);
    app->stage->addChild(body);

    time = millis();
}

void loop() {
    // Every 5 seconds, change the font
    if (millis() > time) {
        time = millis() + 5000;

        app->stage->dirty(); // Force redraw

        heading->font(fonts[fontIndex].font);
        heading->text(fonts[fontIndex].name);

        body->font(fonts[fontIndex].font);
        body->y(heading->y() + heading->height());

        if (++fontIndex >= fontCount) fontIndex = 0;
    }

    // Call update as often as possible
    app->update();
}
