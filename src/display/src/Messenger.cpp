#include "../Messenger.h"

namespace craft {

	/**
	 * Create the listener item
	 */
	ListenerItem::ListenerItem( uint32_t event, Listener* listener, void* messageData ) {
		this->event = event;
		this->listener = listener;
		this->messageData = messageData;
	}

	/**
	 * Create the timer item
	 */
	TimerItem::TimerItem( uint32_t event, float_t triggerTime, Listener* listener, void* messageData ) : ListenerItem( event, listener, messageData ) {
		this->triggerTime = triggerTime;
		this->currentTime = 0;
	}

	/**
	 * Add an event listener
	 */
	void Messenger::addListener( uint32_t event, Listener* listener, void* callbackData ) {
		ListenerItem* item = new ListenerItem( event, listener, callbackData );
		if ( _listeners ) _listeners->before( item );
		_listeners = item;
	}

	/**
	 * Remove an event listener
	 */
	void Messenger::removeListener( uint32_t event, Listener* listener ) {
		ListenerItem* item = _listeners;
		ListenerItem* tempItem;
		while ( item ) {
			// Remove item if event matches
			if ( ( item->event == event ) && ( item->listener == listener ) ) {
				tempItem = item;
				item = (ListenerItem*)item->remove();
				delete tempItem;
			}
			// Move to next
			else {
				tempItem = item;
				item = (ListenerItem*)item->next();
				delete tempItem;
			}
		}
	}

	/**
	 * Remove all listeners for a specific event
	 */
	void Messenger::removeListenersForEvent( uint32_t event ) {
		ListenerItem* item = _listeners;
		ListenerItem* tempItem;
		while ( item ) {
			// Remove item if event matches
			if ( item->event == event ) {
				tempItem = item;
				item = (ListenerItem*)item->remove();
				delete tempItem;
			}
			// Move to next
			else {
				tempItem = item;
				item = (ListenerItem*)item->next();
				delete tempItem;
			}
		}
	}

	/**
	 * Add a timer
	 */
	void Messenger::addTimer( uint32_t event, float_t triggerTime, Listener* listener, void* callbackData ) {
		TimerItem* item = new TimerItem( event, triggerTime, listener, callbackData );
		if ( _timers ) _timers->before( item );
		_timers = item;
	}

	/**
	 * Remove a timer
	 */
	void Messenger::removeTimer( uint32_t event, Listener* listener ) {
		TimerItem* item = _timers;
		TimerItem* tempItem;
		while ( item ) {
			// Remove item if event matches
			if ( ( item->event == event ) && ( item->listener == listener ) ) {
				tempItem = item;
				item = (TimerItem*)item->remove();
				delete tempItem;
			}
			// Move to next
			else {
				tempItem = item;
				item = (TimerItem*)item->next();
				delete tempItem;
			}
		}
	}

	/**
	 * Remove all timers for a specific event
	 */
	void Messenger::removeTimersForEvent( uint32_t event ) {
		TimerItem* item = _timers;
		TimerItem* tempItem;
		while ( item ) {
			// Remove item if event matches
			if ( item->event == event ) {
				tempItem = item;
				item = (TimerItem*)item->remove();
				delete tempItem;
			}
			// Move to next
			else {
				tempItem = item;
				item = (TimerItem*)item->next();
				delete tempItem;
			}
		}
	}

	/**
	 * Trigger an event
	 */
	void Messenger::sendMessage( uint32_t event ) {
		ListenerItem* item = _listeners;
		ListenerItem* tempItem;
		boolean res;
		while ( item ) {
			// Fire the event
			if ( item->event == event ) {
				// Make listener listen
				res = item->listener->listen( event, item->messageData );
				// Remove this listener
				if ( !res ) {
					tempItem = item;
					item = (ListenerItem*)item->remove();
					delete tempItem;
				}
				// Or move to the next one
				else {
					item = (ListenerItem*)item->next();
				}
			}
			// Move to next
			else {
				item = (ListenerItem*)item->next();
			}
		}
	}

	/**
	 * Update timers
	 */
	void Messenger::update( float_t dt ) {
		TimerItem* item = _timers;
		TimerItem* tempItem;
		boolean res;
		while ( item ) {
			// Update the timer
			item->currentTime += dt;
			// Fire the event
			if ( item->currentTime >= item->triggerTime ) {
				// Make listener listen
				res = item->listener->listen( item->event, item->messageData );
				// Remove this listener
				if ( !res ) {
					tempItem = item;
					item = (TimerItem*)item->remove();
					delete tempItem;
				}
				// Or update time and move to the next one
				else {
					item->currentTime -= item->triggerTime;
					item = (TimerItem*)item->next();
				}
			}
			// Move to next
			else {
				item = (TimerItem*)item->next();
			}
		}
	}

} // namespace