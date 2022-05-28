#pragma once

#include "display/Display.h"
#include "display/Stage.h"
#include "display/Messenger.h"
#include "physics/Tween.h"
#include "input/Input.h"

/**
 * Application
 **/
namespace craft {

    /**
     * App framework. An app manages:
     * 		Input (@see Input.h)
     * 		Messages (@see Messenger.h)
     * 		Tweens (@see Tween.h)
     * and can optionally manage:
     * 		Graphics and display (@see Graphics.h)
     */
    class App : public Listener {
    public:

        /**
         * Constructor for app without any graphical elements.
         **/
        App();

        /**
         * Constructor with display adapter object
         * @param	display			A Display instance for the hardware display being used.
         * @param	bufferHeight	The height of the line buffer, in lines. Default = 1. Full framebuffer = 0.
         **/
        App(Display* display, int bufferHeight = 1);

        /**
         * Destructor
         **/
        ~App();

        /**
         * The hardware display object
         */
        Display* display;

        /**
         * The drawing buffer object
         */
        LineBuffer* buffer;

        /**
         * The stage for rendering graphics
         */
        Stage* stage;

        /**
         * Input
         **/
        Input* input;

        /**
         * Listener for messages/events
         */
        Messenger* messenger;

        /**
         * Tween object for animations
         */
        Tween* tweens;

        /**
         * Set target FPS for rendering functions. This includes
         * tweening and updating the display.
         * @param 	fps 	Default 30
         */
        void setRenderFPS(uint16_t fps);

        /**
         * Update the app
         */
        void update();

        /**
         * Initialise serial for debugging messages
         * @param boolean If true, wait until serial object is ready (maximum of 2 seconds)
         */
        void serialBegin(boolean waitUntilReady = false);

    protected:

        /**
         * Called from constructor
         */
        void _init();

        /**
         * Timing
         */
        uint32_t _renderDeltaMicrosMax = (1.0 / 30.0) * 1000000; // 30fps
        uint32_t renderDeltaMicros = 0;
        float_t renderDeltaSecs = 0;
        uint32_t thisMicros;
        uint32_t lastMicros;
        uint32_t deltaMicros;
        float_t deltaSecs;

    };

} // namespace craft
