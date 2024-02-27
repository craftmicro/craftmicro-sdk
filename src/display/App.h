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
         * Constructor with display
         * @param	display			A display. Can be nullptr for non-graphical apps.
         **/
        App(Display* display = nullptr);

        /**
         * Destructor
         **/
        ~App();

        /**
         * The drawing buffer object
         */
        Display* display;

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
         * @param bool If true, wait until serial object is ready (maximum of 2 seconds)
         */
        void serialBegin(bool waitUntilReady = false);

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
