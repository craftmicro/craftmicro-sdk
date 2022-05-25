#pragma once
#ifndef _CRAFTMICRO_MESSENGERH_
#define _CRAFTMICRO_MESSENGERH_ 1

#include "Common.h"
#include "utils/LinkedList.h"

namespace craft {

	/**
	 * Common events. 0-255 are reserved. Define any user events from 256 onward.
	 */
	typedef enum {
		input_next = 1,	// Core input events
		input_previous = 2,
		input_back = 3,
		input_action = 4,

		input_up = 5,	// Secondary input events for movement
		input_down = 6,
		input_left = 7,
		input_right = 8,

		input_action1 = 4,	// Secondary input events for buttons/actions
		input_action2 = 9,
		input_action3 = 10,
		input_action4 = 11,

		input_select = 12,	// Specialised input events
		input_start = 13,
		input_key = 14,
		input_close = 15,
		input_quit = 16,

		action_save = 30,	// Common actions
		action_load = 31,
		action_reset = 32,
		action_home = 33,
		action_end = 34,
		action_pgup = 35,
		action_pgdn = 36,

		action_play = 50,	// Media actions (also see action_home, action_end)
		action_stop = 51,
		action_pause = 51,
		action_rewind = 52,
		action_fastforward = 53,

		update_all = 60,	// Update events
		update_render = 61,

		gui_menuitem_selected = 70		// Gui events
	} Event;

	/**
	 * Listener. An object that is listening for a message.
	 * Inherit from this class to be able to listen for events.
	 */
	class Listener {
	public:
		/**
		 * Called when a message is sent to the listener. If the listen method
		 * returns false, the listener is removed. If it returns true, the the
		 * listener remains in place.
		 * @param  event       The event of the message
		 * @param  messageData Any user message data that was registered with the messenger
		 * @return             Keep the listener?
		 */
		virtual boolean listen( uint32_t event, void* messageData ) { return true; }
	};

	/**
	 * Listener that fires a callback.
	 * Example usage:
	 *
	 * // Define the callback function
	 * boolean handleTheEvent( uint32_t event, void* data ) {
	 * 		// Do something
	 * 		Serial.printf("Event received. The event is %l.\n", event );
	 *
	 * 		// Continue to listen to events
	 * 		return true;
	 * }
	 *
	 * // Create the listener
	 * CallbackListener* listener = new CallbackListener( handleTheEvent );
	 *
	 * // Add the listener to listen for the "action_play" event
	 * messenger->addListener( Event::action_play, listener );
	 *
	 */
	class CallbackListener : public Listener {
	public:
		/**
		 * @brief Construct a new Callback Listener object
		 *
		 * @param callback The callback function to trigger when the event is received
		 */
		CallbackListener( boolean( *callback )( uint32_t event, void* data ) ) {
			this->callback = callback;
		}

		/**
		 * The callback listener that is triggered when the event is received
		 */
		boolean( *callback )( uint32_t event, void* data );

		/**
		 * @brief This method is called when the event is fired. It will trigger the callback.
		 *
		 * @param event The event that was received
		 * @param messageData Any message data passed through with the event
		 * @return boolean True to continue to listen for events, false to remove this listener
		 */
		boolean listen( uint32_t event, void* messageData ) {
			if ( this->callback ) return this->callback( event, messageData );
			return true;
		}
	};

	/**
	 * Listener item. Holds details of a single listener in a linked list.
	 */
	class ListenerItem : public LinkedList<ListenerItem> {
	public:
		ListenerItem( uint32_t event, Listener* listener, void* messageData );

		uint32_t event;
		Listener* listener;
		void* messageData;
	};

	/**
	 * Timer item. A special listener that is triggered on a timer
	 */
	class TimerItem : public ListenerItem {
	public:
		TimerItem( uint32_t event, float_t triggerTime, Listener* listener, void* messageData );

		float_t triggerTime;
		float_t currentTime;
	};

	/**
	 * Listener functionality (events and callbacks). The listen method is called on the Listener
	 * when an event it is interested in is fired.
	 */
	class Messenger {

	public:
		/**
		 * Add an event listener
		 */
		void addListener( uint32_t event, Listener* listener, void* messageData = 0 );

		/**
		 * Remove an event listener
		 */
		void removeListener( uint32_t event, Listener* listener );

		/**
		 * Remove all listeners for a specific event
		 */
		void removeListenersForEvent( uint32_t event );

		/**
		 * Add a timer
		 */
		void addTimer( uint32_t event, float_t triggerTime, Listener* listener, void* messageData = 0 );

		/**
		 * Remove a timer
		 */
		void removeTimer( uint32_t event, Listener* listener );

		/**
		 * Remove all timers for a specific event
		 */
		void removeTimersForEvent( uint32_t event );

		/**
		 * Trigger an message. This calls the Listener::listen method on the listener. If the method
		 * returns true, the listener remains in place. If the method returns false, the listener
		 * is removed.
		 * Events 0-255 are reserved. Events >255 are user events
		 */
		void sendMessage( uint32_t event );

		/**
		 * Update the messenger to check for timers
		 * @param dt Time since last call in seconds
		 */
		void update( float_t dt );

	private:

		/**
		 * List of listeners
		 */
		ListenerItem* _listeners = 0;

		/**
		 * List of timers
		 */
		TimerItem* _timers = 0;

	};

} // namespace

#endif