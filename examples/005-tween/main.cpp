#include <CraftMicro.h>

using namespace craft;

App* app;
Box* box;

float_t x = 0.0;
float_t y = 0.0;
float_t next_x = 150.0;
float_t next_y = 110.0;

// Start a tween in the horizontal plane
void hTweenDone( void* data ) {
    // Tween the 'x' variable between it's current value and next_x over 4.3 seconds.
    // Use 'quadratic ease-in and ease-out' easing function.
    // Once the tween is complete, call hTweenDone again
    app->tweens->addTween( &x, x, next_x, 4.3, quadraticEaseInOut, hTweenDone, NULL );
    next_x = ( next_x == 0.0 ) ? 150.0 : 0.0;
}

// Start a tween in the vertical plane
void vTweenDone( void* data ) {
    if ( next_y == 0.0 ) {
        // Tween the 'y' variable between it's current value and next_y over 1.0 seconds.
        // Use 'quadratic ease-in' easing function so it eases in slowly.
        // Once the tween is complete, call vTweenDone again
        app->tweens->addTween( &y, y, next_y, 1.0, quadraticEaseOut, vTweenDone, NULL );
        next_y = 110.0;
    }
    else {
        // Tween the 'y' variable between it's current value and next_y over 1.0 seconds.
        // Use 'quadratic ease-out' easing function so it starts fast but eases out at the end.
        // Once the tween is complete, call vTweenDone again
        app->tweens->addTween( &y, y, next_y, 1.0, quadraticEaseIn, vTweenDone, NULL );
        next_y = 0.0;
    }
}

// Update the position of the box to the latest values being tweened.
// This also forces the box to be redrawn (changing the position causes
// the box to be 'dirty' and redraw).
bool updateBox( uint32_t event, void* data ) {
    box->x( x );
    box->y( y );
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

    // Create a small box
    box = Box::Create( 10, 10, 10, 10 );
    box->color = Color8888::PaleGoldenrod;
    app->stage->addChild( box );

    // Start easing in both h and v directions
    hTweenDone( NULL );
    vTweenDone( NULL );

    // Listen for the update_render event so that we can update the box on
    // everyy render cycle. The function 'updateBox' is called.
    app->messenger->addListener( Event::update_render, new CallbackListener( updateBox ) );
}

void loop() {
    app->update();
}