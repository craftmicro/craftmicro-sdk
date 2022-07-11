#pragma once

#include <Arduino.h>

namespace craft {

	/**
	 * Use double-precision floating point. Default is 'float' (single precision)
	 */
	#define CRAFTMICRO_USE_DOUBLE 0

	/**
	 * Craft Micro makes extensive use of object pooling to recycle objects instead of
	 * creating new ones. This results in better performance, and less heap
	 * fragmentation, but does require more RAM. On low RAM systems, or for
	 * situations where you are using 1000s of simultanious objects you may need
	 * to switch this off to use less RAM.
	 */
	#define CRAFTMICRO_OBJECT_REUSE 1

	/**
	 * XXX: Implement this flag
	 * Use DMA for memory operations where possible
	 */
	#define CRAFTMICRO_USE_DMA 0

	/**
	 * @brief Maximum title length for GUI widgets (default 32)
	 */
	#define CRAFTMICRO_GUI_MAX_TITLE_LEN 32

	/**
	 * @brief Maximum acronyn length for GUI widgets (default 3)
	 */
	#define CRAFTMICRO_GUI_MAX_ACRONYM_LEN 3

	/**
	 * ######## ONLY MAKE CHANGES ABOVE THIS LINE ##########
	 */

	/**
	 * Define the floating point type to be used by the library
	 * Possible: float (default), double
	 */
	#if CRAFTMICRO_USE_DOUBLE
	typedef double float_t;
	#else
	typedef float float_t;
	#endif

	/**
	 * @brief Value to supply for unused pin
	 * The type is uint8_t
	 */
	#define UNUSED_PIN 255

	/**
	 * @brief Supply the pin number, or -1 if the pin is unused
	 * Used to convert between craft micro "UNUSED_PIN" and the common value of -1 in other libraries
	 */
	#define PIN_OR_UNUSED(p) p==UNUSED_PIN?-1:p

	/**
	 * @brief Swap two values
	 **/
	template<typename T>
	inline void swap(T& a, T& b) {
		T t = a;
		a = b;
		b = t;
	}

	/**
	 * @brief Modified flash string helper
	 */
	#define S(string_literal) ((const char*)F(string_literal))

	 /**
	  * @brief Inlining macro
	  */
	#if defined(_MSC_VER)
	#define ALWAYS_INLINE __forceinline inline
	#elif defined(__GNUC__)
	#define ALWAYS_INLINE inline
	#endif

} // ns::craft
