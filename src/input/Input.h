#pragma once

#include "display/Messenger.h"

namespace craft {

    enum class InputType {

        /**
         * ONE BUTTON mode
         * 		B1: p1
         * 			Click: Next/Down
         * 		  	Dbl-click: Select/Action
         * 		   	Long press: Back
         */
        button1 = 1,

        /**
         * THREE BUTTON mode
         * 		B1: p1
         * 			Click: Next/Down
         * 		B2: p2
         * 			Click: Previous/Up
         * 		B3: p3
         * 			Click: Select/Action
         * 			Long press: Back
         */
         button3 = 3,

         /**
          * D-PAD + ONE BUTTON mode
          * 		D1: p1
          * 			Click: Previous/Up
          * 			Long press: Repeat
          * 		D2: p2
          * 			Click: Next/Down
          * 			Long press: Repeat
          * 	  	D3: p3
          * 	  		Click: Left
          * 	  		Long press: Repeat
          * 	  	D4: p4
          * 	  		Click: Right
          * 	  		Long press: Repeat
          * 		B1: p5
          * 			Click: Select/Action
          * 			Long press: Back
          */
          dpad1 = 5,

          /**
           * D-PAD + TWO BUTTON mode
           * 		D1: p1
           * 			Click: Previous/Up
           * 			Long press: Repeat
           * 		D2: p2
           * 			Click: Next/Down
           * 			Long press: Repeat
           * 	  	D3: p3
           * 	  		Click: Left
           * 	  		Long press: Repeat
           * 	  	D4: p4
           * 	  		Click: Right
           * 	  		Long press: Repeat
           * 		B1: p5
           * 			Click: Select/Action
           * 		B2: p6
           * 			Click: Back
           */
           dpad2 = 6,

           /**
            * ANALOGUE JOY + ONE BUTTON mode (i.e. Joystick + 1 button)
            * This could be an analogue joystick and a seperate button, or a
            * stick that can also be depressed as a button.
            * 		J1: p1
            * 			Click: Previous/Up
            * 			Long press: Repeat
            * 		J2: p2
            * 			Click: Next/Down
            * 			Long press: Repeat
            * 	  	J3: p3
            * 	  		Click: Left
            * 	  		Long press: Repeat
            * 	  	J4: p4
            * 	  		Click: Right
            * 	  		Long press: Repeat
            * 		B1: p5
            * 			Click: Select/Action
            * 			Long press: Back
            */
            joy1 = 7,

            /**
             * ANALOGUE JOY + TWO BUTTON mode (i.e. Joystick + 2 button)
             * 		J1: p1
             * 			Click: Previous/Up
             * 			Long press: Repeat
             * 		J2: p2
             * 			Click: Next/Down
             * 			Long press: Repeat
             * 	  	J3: p3
             * 	  		Click: Left
             * 	  		Long press: Repeat
             * 	  	J4: p4
             * 	  		Click: Right
             * 	  		Long press: Repeat
             * 		B1: p5
             * 			Click: Select/Action
             * 		B2: p6
             * 			Click: Back
             */
             joy2 = 8

    };

    enum class ClickType {
        none = 0,

        // Normal digital button actions
        click = 1, // Short click and release
        dbl_click = 2, // Two quick clicks in succession
        press = 3, // XXX A longer press and release (not common. See hold)
        hold = 4, // Hold down
        click_press = 5, // XXX A quick click then a longer press and release (not common. See click_hold)
        click_hold = 6, // A quick click, then hold down

        // Other digital button actions
        down = 10, // Any time a button goes from off to on
        up = 11, // Any time a button goes on to off

        // Normal analogue actions
        move = 20, // For analogue inputs, this is any movement over the threshhold
        move_positive = 21, // For analogue inputs, this is any positive movement over over the threshhold
        move_negative = 22, // For analogue inputs, this is any negative movement over over the threshhold

        // Other analogue actions
        release = 30  // For analogue inputs, this is a return to neutral

    };

    enum class PinType {
        digital = 0,
        analog = 1, // Analogue, 0=off, >0 is on
        analog_mid = 2  // Analogue, middle=off, away from middle is on (+ve and -ve)
    };

    typedef uint8_t pin;

    enum class PinState {
        psRest, 					// Resting state
        psDown1DB,					// Button down, debounce period
        psDown1,					// Down
        psUp1DB,					// Button up, debounce period
        psUp1,						// Up after debounce
        psPress1DB,					// Button up after press, debounce period
        psDown2DB,					// Button down second time, debounce period
        psDown2,					// Down second time
        psUp2DB,					// Button up, debounce period
        psPress2DB,					// Button up after second press, debounce period
        psHold,						// Hold button down (first or second click)
        psLastDB,					// Button up, debounce period. Rest after
    };

    /**
     * An input mapping
     */
    typedef struct InputMapS {
        ClickType clickType;
        uint32_t event;
        uint16_t threshhold;
        struct InputMapS* next;
    } InputMap;

    /**
     * A listening pin
     */
    typedef struct InputPinS {
        uint8_t pin;
        PinType pinType;
        PinState state;
        float_t time;
        InputMap* mappings;
        struct InputPinS* next;
    } InputPin;

    /**
     * Handle input
     */
    class Input {

    public:

        static constexpr float_t TIME_DEBOUNCE = 0.03f;
        static constexpr float_t TIME_PRESS = 0.6f;
        static constexpr float_t TIME_HOLD = 0.6f;
        static constexpr float_t TIME_DBLCLICK = 0.2f;

        /**
         * Constructor
         *
         */
        Input(Messenger* messenger);

        /**
         * Sets the input mode to one of the preset modes. Additional mappings can be added
         * as well, or instead of, setting the mode. See the definition for InputType for the
         * pins that should be specified when calling this method.
         * @param mode 		The input mode
         */
        void setMode(InputType mode, pin p1 = 0, pin p2 = 0, pin p3 = 0, pin p4 = 0, pin p5 = 0, pin p6 = 0);

        /**
         * Sets analogue joystick pins. These are mapped automatically to the events for
         * input_up, input_down, input_left and input_right with a thresshold of 50%.
         * @param up    Pin to use for up
         * @param down  Pin to use for down
         * @param left  Pin to use for left
         * @param right Pin to use for right
         */
        void setJoyPins(pin up, pin down, pin left, pin right);

        /**
         * Sets D-Pad pins. These are mapped automatically to the events for
         * input_up, input_down, input_left and input_right.
         * @param up    Pin to use for up
         * @param down  Pin to use for down
         * @param left  Pin to use for left
         * @param right Pin to use for right
         */
        void setDPadPins(pin up, pin down, pin left, pin right);

        /**
         * Map a specific pin to an input event. Multiple events can be mapped to the same pin, as long
         * as a different clickType is used for each. Examples:
         * 		map( 12, digital, click, input_select ); // Map a click on pin 12 to the 'select' event
         * 		map( 7, analog_mid, move, input_vaxis, 0.2 ); // Map analogue movement on pin 7 to the 'vertical axis' event after moving 20% from neutral
         * 		map( 16, digital, click, input_next );			// Map a click on pin 16 to 'next', AND
         * 		map( 16, digital, dbl_click, input_previous );	// Map a dbl-click on the same pin to 'previous'
         * @param  pin       	The pin to map
         * @param  pinType   	Digital or analogue pin type
         * @param  clickType 	The type of click
         * @param  event     	The event to fire
         * @param  threshhold   If the pin is analogue, the associated threshhold
         * @return           The input for chaining
         */
        Input* map(pin pin, PinType pinType, ClickType clickType, uint32_t event, uint16_t threshhold = 0);

        /**
         * Remove a pin mapping from a pin.
         * @param  	pin 		The pin to unmap
         * @param 	ClickType 	The click type to unmap. If 0 will unmap all clickTypes for pin
         * @return     The input for chaining
         */
        Input* unmap(pin pin, ClickType clickType = craft::ClickType::none);

        /**
         * Remove all pin mappings
         * @return     The input for chaining
         */
        Input* unmapAll();

        /**
         * Set the active state of the Input object. If false will not fire input events, but will
         * still process pins when update() is called.
         * @param 	state 	true if active, false if not active
         */
        void setActive(boolean state);

        /**
         * Update inputs
         */
        void update(float_t dt);

    protected:

        /**
         * Active flag
         */
        boolean _active = true;

        /**
         * This listener for firing input events
         */
        Messenger* _messenger = 0;

        /**
         * The current input mode
         */
        InputType _mode;

        /**
         * Listening pins
         */
        InputPin* _pins = 0;

    };

} // namespace craft
