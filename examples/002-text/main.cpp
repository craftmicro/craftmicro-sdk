#include <CraftMicro.h>
#include "../resources/font_PixelSix008.h"

using namespace craft;

App* app;
Text* text;

void setup() {
    // Create a new application
    // Use a 320x240 ILI9341 display, and scale all pixels to 2x2 (effective size is 160x120)
    // Use a single-line line buffer for low memory consumption
    app = new App(
        new DisplayILI9341( DisplaySize::Size320x240, 10, 15, 4, 11, 13, 12, 6, PixelScale::Scale2x2 ),
        LineBufferHeight::singleLine
    );
    // Set background color
    app->stage->backgroundColor( ARGB8888::SaddleBrown );

    // Create a text object usiing the "Pixel6" font
    text = Text::Create( (packedbdf_t*)&PixelSix008 );
    text->text( (char*)F( "All children, except one, grow up. They soon know that they will grow up, and the way Wendy knew was this." ) );
    text->width( 80 );
    text->x( 40 );
    text->y( 10 );
    text->color( ARGB8888::White );
    // Add the text to the stage so that it can be rendered
    app->stage->addChild( text );
}

void loop() {
    // Call update as often as possible
    app->update();
}