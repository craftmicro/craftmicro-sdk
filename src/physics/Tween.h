#pragma once
#ifndef _CRAFTMICRO_TWEENH_
#define _CRAFTMICRO_TWEENH_ 1

#include "Common.h"
#include "utils/LinkedList.h"
#include "physics/Easing.h"

namespace craft {

	/**
	 * Listener callback. If the callback returns true, the listener remains
	 * in place and continues to listen for future events. If it returns false
	 * the listener will be removed from the list.
	 * @param  void*		Pointer to user data associated with the listener
	 */
	typedef void ( *TweenCallback )( void* );

	/**
	 * Tween item. Holds details of a single tween in a linked list.
	 */
	class TweenItem : public LinkedList<TweenItem> {
	public:
		TweenItem( float_t* property, float_t from, float_t to, float_t seconds, EasingFunction ease, TweenCallback callback, void* callbackData );

		/**
		 * @brief Removes the tween item and returns the next one in the list
		 * @return TweenItem* The next tween item
		 */
		TweenItem* remove();

		float_t* property;

		float_t from;
		float_t change;
		float_t current;
		float_t seconds;
		float_t seconds_inv;
		EasingFunction ease;
		TweenCallback callback;
		void* callbackData;
	};

	/**
	 * Tweening functionallity
	 */
	class Tween {
	public:
		/**
		 * Add a tween
		 */
		void addTween( float_t* property, float_t from, float_t to, float_t seconds, EasingFunction ease, TweenCallback callback, void* callbackData );

		/**
		 * Remove a tween
		 */
		void removeTween( float_t* property );

		/**
		 * Update all tweens
		 */
		void update( float_t dt );

	private:
		TweenItem* _tweens = nullptr;

	};

} // namespace

#endif