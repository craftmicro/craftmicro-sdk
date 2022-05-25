#pragma once
#ifndef _CRAFTMICRO_EASING_H
#define _CRAFTMICRO_EASING_H 1

namespace craft {

	/**
	 * Function pointer to allow specifying any easing function
	 **/
	typedef float_t( *EasingFunction )( float_t );

	// Linear interpolation (no easing)
	float_t easeNone( float_t p );

	// Quadratic easing; p^2
	float_t quadraticEaseIn( float_t p );
	float_t quadraticEaseOut( float_t p );
	float_t quadraticEaseInOut( float_t p );

	// Cubic easing; p^3
	float_t cubicEaseIn( float_t p );
	float_t cubicEaseOut( float_t p );
	float_t cubicEaseInOut( float_t p );

	// Quartic easing; p^4
	float_t quarticEaseIn( float_t p );
	float_t quarticEaseOut( float_t p );
	float_t quarticEaseInOut( float_t p );

	// Quintic easing; p^5
	float_t quinticEaseIn( float_t p );
	float_t quinticEaseOut( float_t p );
	float_t quinticEaseInOut( float_t p );

	// Sine wave easing; sin(p * PI/2)
	float_t sineEaseIn( float_t p );
	float_t sineEaseOut( float_t p );
	float_t sineEaseInOut( float_t p );

	// Circular easing; sqrt(1 - p^2)
	float_t circularEaseIn( float_t p );
	float_t circularEaseOut( float_t p );
	float_t circularEaseInOut( float_t p );

	// Exponential easing, base 2
	float_t exponentialEaseIn( float_t p );
	float_t exponentialEaseOut( float_t p );
	float_t exponentialEaseInOut( float_t p );

	// Exponentially-damped sine wave easing
	float_t elasticEaseIn( float_t p );
	float_t elasticEaseOut( float_t p );
	float_t elasticEaseInOut( float_t p );

	// Overshooting cubic easing; 
	float_t backEaseIn( float_t p );
	float_t backEaseOut( float_t p );
	float_t backEaseInOut( float_t p );

	// Exponentially-decaying bounce easing
	float_t bounceEaseIn( float_t p );
	float_t bounceEaseOut( float_t p );
	float_t bounceEaseInOut( float_t p );

} // ns:mac

#endif
