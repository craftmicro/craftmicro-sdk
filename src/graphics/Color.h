#pragma once
#ifndef _CRAFTMICRO_COLORH_
#define _CRAFTMICRO_COLORH_ 1

#include "Common.h"

/**
 * Color types and functions
 **/
namespace craft {

	/**
	 * Defines alpha as a float (0.0 to 1.0)
	 **/
	typedef float_t alpha_t;

	/**
	 * Defines a color as packed ARGB components
	 * aaaaaaaaRRRRRRRRGGGGGGGGBBBBBBBB
	 **/
	typedef uint32_t color8888;

	/**
	 * Defines a color as packed RGB components without alpha (24bit within 32bit word)
	 * ........RRRRRRRRGGGGGGGGBBBBBBBB
	 **/
	typedef uint32_t color888;

	/**
	 * Defines a color as a RGB565 16bit unsigned int
	 * RRRRRGGGGGGBBBBB
	 **/
	typedef uint16_t color565;

	/**
	 * Defines a color as ARGB8565 24bit total, with 8-bit alpha and packed 16-bit RGB565
	 * ........aaaaaaaaRRRRRGGGGGGBBBBB
	 **/
	typedef uint32_t color8565;

	/**
	 * Defines a color as ARGB5565 21bit total, with 5-bit alpha and packed 16-bit RGB565
	 * This is used for some special fast blending routines
	 * ...........aaaaaRRRRRGGGGGGBBBBB
	 **/
	typedef uint32_t color5565;

	/**
	 * Defines a color as a RGBA4444 16bit unsigned int
	 * aaaaRRRRGGGGBBBB
	 **/
	typedef uint16_t color4444;

	/**
	 * Defines a color as ARGB6666 24bit total, with 6-bit alpha and 6-bits per color
	 * ........aaaaaaRRRRRRGGGGGGBBBBBB
	 **/
	typedef uint32_t color6666;

	/**
	 * Defines a color as 8-bit grayscale
	 **/
	typedef uint8_t colorGray;

	/**
 * Clamp alpha to range 0.0 - 1.0
 * @param  alpha 		The value to clamp
 * @return       The clamped value in the range 0.0 - 1.0
 */
	inline alpha_t alphaClamp( alpha_t a ) {
		return ( a < 0.0 ) ? 0.0 : ( a > 1.0 ) ? 1.0 : a;
	}

	/**
	 * Convert alpha from range 0.0-1.0 to 0-255 (8 bit)
	 * @param  a  	The alpha 0.0 - 1.0
	 * @return   The 8-bit alpha value
	 */
	inline uint8_t alpha8bit( alpha_t a ) {
		return (uint8_t)( alphaClamp( a ) * 255 );
	}

	/**
	 * Converts ARGB8888 24-bit format to individual RGB and A components
	 * @param	color	The RGB888 color to convert
	 * @param	r		(out) Red component
	 * @param	g		(out) Green component
	 * @param	b		(out) Blue component
	 **/
	inline void toRGBA( color8888 color, uint8_t& r, uint8_t& g, uint8_t& b, uint8_t& a ) {
		a = color >> 24;
		r = ( color >> 16 ) & 0xFF;
		g = ( color >> 8 ) & 0xFF;
		b = color & 0xFF;
	}

	/**
	 * Converts RGB888 24-bit format to individual RGB color components
	 * @param	color	The RGB888 color to convert
	 * @param	r		(out) Red component
	 * @param	g		(out) Green component
	 * @param	b		(out) Blue component
	 **/
	inline void toRGB( color888 color, uint8_t& r, uint8_t& g, uint8_t& b ) {
		r = ( color >> 16 ) & 0xFF;
		g = ( color >> 8 ) & 0xFF;
		b = color & 0xFF;
	}

	/**
	 * Converts RGB565 format to individual RGB color components
	 * @param	color	The RGB565 color to convert
	 * @param	r		(out) Red component
	 * @param	g		(out) Green component
	 * @param	b		(out) Blue component
	 **/
	inline void toRGB( color565 color, uint8_t& r, uint8_t& g, uint8_t& b ) {
		r = ( ( color >> 8 ) & 0b11111000 ) | ( ( color >> 13 ) & 0b111 );
		g = ( ( color >> 3 ) & 0b11111100 ) | ( ( color >> 9 ) & 0b11 );
		b = ( ( color << 3 ) & 0b11111000 ) | ( ( color >> 2 ) & 0b111 );
	}

	/**
	 * Converts mono 1-bit format to individual RGB color components
	 * @param	color	The mono color to convert (0,1)
	 * @param	r		(out) Red component
	 * @param	g		(out) Green component
	 * @param	b		(out) Blue component
	 */
	inline void monoToRGB( uint8_t color, uint8_t& r, uint8_t& g, uint8_t& b ) {
		if ( color & 0b1 ) {
			r = 255; g = 255; b = 255;
		}
		else {
			r = 0; g = 0; b = 0;
		}
	}

	/**
	 * Fast alpha-blending of RGB color components
	 * @param bgr    Background color R component
	 * @param bgg    Background color G component
	 * @param bgb    Background color B component
	 * @param fgr    Foreground color R component
	 * @param fgg    Foreground color G component
	 * @param fgb    Foreground color B component
	 * @param alpha The alpha (0.0-1.0)
	 * @param r     (out) Blended R component
	 * @param g     (out) Blended G component
	 * @param b     (out) Blended B component
	 */
	inline void blendRGB(
		uint8_t bgr, uint8_t bgg, uint8_t bgb,
		uint8_t fgr, uint8_t fgg, uint8_t fgb,
		alpha_t alpha,
		uint8_t& r, uint8_t& g, uint8_t& b
	) {
		uint8_t a = alpha8bit( alpha );
		uint32_t rb = ( bgr << 16 ) | bgb;
		uint32_t g0 = bgg << 8;
		rb += ( ( ( fgr << 16 ) | fgb ) - rb ) * a >> 8;
		g0 += ( ( fgg << 8 ) - g0 ) * a >> 8;
		r = ( ( rb >> 16 ) & 0xff );
		g = ( ( g0 >> 8 ) & 0xff );
		b = ( rb & 0xff );
	}

} // namespace

#endif