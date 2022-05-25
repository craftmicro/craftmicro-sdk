#include "../Tween.h"

namespace craft {

	/**
	 * Create the Tween item
	 */
	TweenItem::TweenItem( float_t* property, float_t from, float_t to, float_t seconds, EasingFunction ease, TweenCallback callback, void* callbackData ) {
		this->property = property;

		this->from = from;
		this->change = to - from;
		this->current = 0;
		this->seconds = seconds;
		this->seconds_inv = 1 / seconds;
		this->ease = ease;

		this->callback = callback;
		this->callbackData = callbackData;

		*property = from;
	}

	TweenItem* TweenItem::remove(){
		TweenItem* next = LinkedList<TweenItem>::next();
		LinkedList<TweenItem>::remove();
		_next = nullptr;
		_prev = nullptr;
		return next;
	}

	/**
	 * Add an Tween
	 */
	void Tween::addTween( float_t* property, float_t from, float_t to, float_t seconds, EasingFunction ease, TweenCallback callback, void* callbackData ) {
		TweenItem* item = new TweenItem( property, from, to, seconds, ease, callback, callbackData );
		if ( _tweens ) _tweens->before( item );
		_tweens = item;
	}

	/**
	 * Remove all tweens for a property
	 */
	void Tween::removeTween( float_t* property ) {
		TweenItem* item = _tweens;
		TweenItem* removedItem;
		while ( item ) {
			// Remove item if property matches
			if ( item->property == property ) {
				removedItem = item;
				item = removedItem->remove();
				if (removedItem == _tweens) _tweens = item;
				delete removedItem;
			}
			// Move to next
			else {
				item = item->next();
			}
		}
	}

	/**
	 * Trigger an event
	 */
	void Tween::update( float_t dt ) {
		TweenItem* item = _tweens;
		TweenItem* removedItem;
		while ( item ) {
			// Progress the tween
			item->current += dt;
			if ( item->current > item->seconds ) item->current = item->seconds;
			// Calculate value
			*(item->property) = item->from + item->change * item->ease( item->current * item->seconds_inv );
			// If tween is done, remove it then trigger callback
			if ( item->current == item->seconds ) {
				removedItem = item;
				item = removedItem->remove();
				if (removedItem == _tweens) _tweens = item;
				if ( removedItem->callback ) removedItem->callback( removedItem->callbackData );
				delete removedItem;
			}
			// Move to next
			else {
				item = item->next();
			}
		}
	}

} // namespace