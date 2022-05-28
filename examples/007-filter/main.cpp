#include <CraftMicro.h>
#include "../../resources/asterix.h"

using namespace craft;

App* app;
Sprite* asterixSprite1;
Sprite* asterixSprite2;
Sprite* asterixSprite3;
Sprite* asterixSprite4;
Sprite* asterixSprite5;

HSVFilter* hsvFilter;
TintFilter* tintFilter;

float_t h = 0;
float_t a = 0;
float_t da = 0.01;

// Runs on every render cycle. Animate a 
// couple of the filters,
boolean onRenderFrame( uint32_t event, void* data ) {
    h++;
    hsvFilter->h = h;
    asterixSprite1->dirty(); // Forces the sprite to redraw

    a += da;
    if ( a > 1 ) {
        a = 1;
        da = -da;
    }
    else if ( a < 0 ) {
        a = 0;
        da = -da;
    }
    tintFilter->amount( a );
    asterixSprite2->dirty(); // Forces the sprite to redraw

    return true;
}

void setup() {
    // Create a new application
    // Use a 320x240 ILI9341 display, and scale all pixels to 2x2 (effective size is 160x120)
    // Use a single-line line buffer for low memory consumption
    app = new App(
        new DisplayILI9341( DisplaySize::Size320x240, 10, 15, 4, 11, 13, 12, 6, PixelScale::x2 ),
        LineBufferHeight::singleLine
    );
    // Set background color
    app->stage->backgroundColor( Color8888::SaddleBrown );

    // Create sprite 1 and add it to the stage
    asterixSprite1 = Sprite::Create( (TilemapData*)&asterix, 0 );
    app->stage->addChild( asterixSprite1 );
    asterixSprite1->origin( OriginType::centerBottom, true );
    asterixSprite1->x( 25 );
    asterixSprite1->y( 100 );
    // Adjust the Hue, Saturation and Value
    // See onRenderFrame - the hue value is cycled
    hsvFilter = new HSVFilter( 0, 0, 0 );
    asterixSprite1->filters = hsvFilter;

    // Create sprite 2 and add it to the stage
    asterixSprite2 = Sprite::Create( (TilemapData*)&asterix, 0 );
    app->stage->addChild( asterixSprite2 );
    asterixSprite2->origin( OriginType::centerBottom, true );
    asterixSprite2->x( 50 );
    asterixSprite2->y( 100 );
    // Tint the sprite by a color
    // See onRenderFrame - the amount of tint is cycled
    tintFilter = new TintFilter( Color8888::DarkOrange, 0 );
    asterixSprite2->filters = tintFilter;

    // Create sprite 3 and add it to the stage
    asterixSprite3 = Sprite::Create( (TilemapData*)&asterix, 0 );
    app->stage->addChild( asterixSprite3 );
    asterixSprite3->origin( OriginType::centerBottom, true );
    asterixSprite3->x( 75 );
    asterixSprite3->y( 100 );
    // Mask a specific color (make it transparent)
    // Will only mask the exact color. In this example it is masking the
    // skin color of the asterix sprite. You'll see that it leaves behind
    // some of the darken skin pixels that don't exactly match the color.
    asterixSprite3->filters = new ColorMaskFilter( 0xffb496 );

    // Create sprite 4 and add it to the stage
    asterixSprite4 = Sprite::Create( (TilemapData*)&asterix, 0 );
    app->stage->addChild( asterixSprite4 );
    asterixSprite4->origin( OriginType::centerBottom, true );
    asterixSprite4->x( 100 );
    asterixSprite4->y( 100 );
    // Mask a specific color and close colors (make it transparent)
    // Will mask the color and any close colors within a threshhold
    // (note the darker skin pixels are now also masked)
    asterixSprite4->filters = new FuzzyColorMaskFilter( 0xffb496, 0.25 );

    // Create sprite 5 and add it to the stage
    asterixSprite5 = Sprite::Create( (TilemapData*)&asterix, 0 );
    app->stage->addChild( asterixSprite5 );
    asterixSprite5->origin( OriginType::centerBottom, true );
    asterixSprite5->x( 125 );
    asterixSprite5->y( 100 );
    // Filters can be stacked (objects can have more than one filter)
    asterixSprite5->filters = new FuzzyColorMaskFilter( 0xffb496, 0.25 );
    // This is a lighten/darken filter. -1.0 is full black and 1.0 is
    // full white. 0 is no change.
    asterixSprite5->filters->add( new ShadeFilter( 0.5 ) );

    // Listen for the update_render event. This runs the 'onRenderFrame' function on
    // every render cycle. We use this to animate some of the filters.
    app->messenger->addListener( Event::update_render, new CallbackListener( onRenderFrame ) );
}

void loop() {
    app->update();
}