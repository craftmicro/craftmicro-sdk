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
