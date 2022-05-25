#ifndef _CRAFTMICRO_COLOR565H_
#define _CRAFTMICRO_COLOR565H_ 1

#include "Common.h"
#include "graphics/Color.h"

/**
 * 16-bit color 565 functions
 **/
namespace craft {

	/**
	 * RGB565 colors
	 */
	enum Color888 {
		RGB565_Transparent = 0xf81f,
		RGB565_Pink = 0xfe19,
		RGB565_LightPink = 0xfdb8,
		RGB565_HotPink = 0xfb56,
		RGB565_DeepPink = 0xf8b2,
		RGB565_PaleVioletRed = 0xdb92,
		RGB565_MediumVioletRed = 0xc0b0,
		RGB565_LightSalmon = 0xfd0f,
		RGB565_Salmon = 0xfc0e,
		RGB565_DarkSalmon = 0xecaf,
		RGB565_LightCoral = 0xf410,
		RGB565_IndianRed = 0xcaeb,
		RGB565_Crimson = 0xd8a7,
		RGB565_Firebrick = 0xb104,
		RGB565_DarkRed = 0x8800,
		RGB565_Red = 0xf800,
		RGB565_OrangeRed = 0xfa20,
		RGB565_Tomato = 0xfb08,
		RGB565_Coral = 0xfbea,
		RGB565_DarkOrange = 0xfc60,
		RGB565_Orange = 0xfd20,
		RGB565_Yellow = 0xffe0,
		RGB565_LightYellow = 0xfffc,
		RGB565_LemonChiffon = 0xffd9,
		RGB565_LightGoldenrodYellow = 0xffda,
		RGB565_PapayaWhip = 0xff7a,
		RGB565_Moccasin = 0xff36,
		RGB565_PeachPuff = 0xfed7,
		RGB565_PaleGoldenrod = 0xef55,
		RGB565_Khaki = 0xf731,
		RGB565_DarkKhaki = 0xbdad,
		RGB565_Gold = 0xfea0,
		RGB565_Cornsilk = 0xffdb,
		RGB565_BlanchedAlmond = 0xff59,
		RGB565_Bisque = 0xff38,
		RGB565_NavajoWhite = 0xfef5,
		RGB565_Wheat = 0xf6f6,
		RGB565_Burlywood = 0xddd0,
		RGB565_Tan = 0xd5b1,
		RGB565_RosyBrown = 0xbc71,
		RGB565_SandyBrown = 0xf52c,
		RGB565_Goldenrod = 0xdd24,
		RGB565_DarkGoldenrod = 0xbc21,
		RGB565_Peru = 0xcc27,
		RGB565_Chocolate = 0xd343,
		RGB565_SaddleBrown = 0x8a22,
		RGB565_Sienna = 0xa285,
		RGB565_Brown = 0xa145,
		RGB565_Maroon = 0x8000,
		RGB565_DarkOliveGreen = 0x5345,
		RGB565_Olive = 0x8400,
		RGB565_OliveDrab = 0x6c64,
		RGB565_YellowGreen = 0x9e66,
		RGB565_LimeGreen = 0x3666,
		RGB565_Lime = 0x07e0,
		RGB565_LawnGreen = 0x7fe0,
		RGB565_Chartreuse = 0x7fe0,
		RGB565_GreenYellow = 0xafe5,
		RGB565_SpringGreen = 0x07ef,
		RGB565_MediumSpringGreen = 0x07d3,
		RGB565_LightGreen = 0x9772,
		RGB565_PaleGreen = 0x9fd3,
		RGB565_DarkSeaGreen = 0x8df1,
		RGB565_MediumAquamarine = 0x6675,
		RGB565_MediumSeaGreen = 0x3d8e,
		RGB565_SeaGreen = 0x2c4a,
		RGB565_ForestGreen = 0x2444,
		RGB565_Green = 0x0400,
		RGB565_DarkGreen = 0x0320,
		RGB565_Aqua = 0x07ff,
		RGB565_Cyan = 0x07ff,
		RGB565_LightCyan = 0xe7ff,
		RGB565_PaleTurquoise = 0xaf7d,
		RGB565_Aquamarine = 0x7ffa,
		RGB565_Turquoise = 0x471a,
		RGB565_MediumTurquoise = 0x4e99,
		RGB565_DarkTurquoise = 0x067a,
		RGB565_LightSeaGreen = 0x2595,
		RGB565_CadetBlue = 0x5cf4,
		RGB565_DarkCyan = 0x0451,
		RGB565_Teal = 0x0410,
		RGB565_LightSteelBlue = 0xb63b,
		RGB565_PowderBlue = 0xb71c,
		RGB565_LightBlue = 0xaedc,
		RGB565_SkyBlue = 0x867d,
		RGB565_LightSkyBlue = 0x867f,
		RGB565_DeepSkyBlue = 0x05ff,
		RGB565_DodgerBlue = 0x1c9f,
		RGB565_CornflowerBlue = 0x64bd,
		RGB565_SteelBlue = 0x4416,
		RGB565_RoyalBlue = 0x435c,
		RGB565_Blue = 0x001f,
		RGB565_MediumBlue = 0x0019,
		RGB565_DarkBlue = 0x0011,
		RGB565_Navy = 0x0010,
		RGB565_MidnightBlue = 0x18ce,
		RGB565_Lavender = 0xe73f,
		RGB565_Thistle = 0xddfb,
		RGB565_Plum = 0xdd1b,
		RGB565_Violet = 0xec1d,
		RGB565_Orchid = 0xdb9a,
		RGB565_Fuchsia = 0xf81f,
		RGB565_Magenta = 0xf81f,
		RGB565_MediumOrchid = 0xbaba,
		RGB565_MediumPurple = 0x939b,
		RGB565_BlueViolet = 0x895c,
		RGB565_DarkViolet = 0x901a,
		RGB565_DarkOrchid = 0x9999,
		RGB565_DarkMagenta = 0x8811,
		RGB565_Purple = 0x8010,
		RGB565_Indigo = 0x4810,
		RGB565_DarkSlateBlue = 0x49f1,
		RGB565_SlateBlue = 0x6ad9,
		RGB565_MediumSlateBlue = 0x7b5d,
		RGB565_White = 0xffff,
		RGB565_Snow = 0xffdf,
		RGB565_Honeydew = 0xf7fe,
		RGB565_MintCream = 0xf7ff,
		RGB565_Azure = 0xf7ff,
		RGB565_AliceBlue = 0xf7df,
		RGB565_GhostWhite = 0xffdf,
		RGB565_WhiteSmoke = 0xf7be,
		RGB565_Seashell = 0xffbd,
		RGB565_Beige = 0xf7bb,
		RGB565_OldLace = 0xffbc,
		RGB565_FloralWhite = 0xffde,
		RGB565_Ivory = 0xfffe,
		RGB565_AntiqueWhite = 0xff5a,
		RGB565_Linen = 0xff9c,
		RGB565_LavenderBlush = 0xff9e,
		RGB565_MistyRose = 0xff3c,
		RGB565_Gainsboro = 0xdefb,
		RGB565_LightGray = 0xd69a,
		RGB565_Silver = 0xc618,
		RGB565_DarkGray = 0xad55,
		RGB565_Gray = 0x8410,
		RGB565_DimGray = 0x6b4d,
		RGB565_LightSlateGray = 0x7453,
		RGB565_SlateGray = 0x7412,
		RGB565_DarkSlateGray = 0x2a69,
		RGB565_Black = 0x0000
	};

	/**
	 * @brief Extract the red channel value from a 16bit color565 (RGB) value
	 *
	 * @param c The color
	 * @return uint8_t The 8-bit red value (0-255)
	 */
	inline uint8_t red( color565 c ) {
		return ( ( c >> 8 ) & 0b11111000 ) | ( ( c >> 13 ) & 0b111 );
	}

	/**
	 * @brief Extract the green channel value from a 32bit color8888 (ARGB) value
	 *
	 * @param c The color
	 * @return uint8_t The 8-bit green value (0-255)
	 */
	inline uint8_t green( color565 c ) {
		return ( ( c >> 3 ) & 0b11111100 ) | ( ( c >> 9 ) & 0b11 );
	}

	/**
	 * @brief Convert RGB565 color to grayscale and return a single 5-bit channel value
	 *
	 * @param c 			The color
	 * @return uint8_t 		The grayscale channel color (0-31)
	 */
	inline uint8_t gray( color565 c ) {
		return ( ( ( c >> 11 ) & 0x1F ) + ( ( c >> 5 ) & 0x3F ) + ( c & 0x1F ) ) >> 2;
	}

	/**
	 * @brief Extract the blue channel value from a 32bit color8888 (ARGB) value
	 *
	 * @param c The color
	 * @return uint8_t The 8-bit blue value (0-255)
	 */
	inline uint8_t blue( color565 c ) {
		return ( ( c << 3 ) & 0b11111000 ) | ( ( c >> 2 ) & 0b111 );
	}

	/**
	 * Convert individual RGB values to RGB565 16bit format
	 * @param	r		Red component
	 * @param	g		Green component
	 * @param	b		Blue component
	 **/
	inline color565 to565( uint8_t r, uint8_t g, uint8_t b ) {
		return ( ( r & 0xF8 ) << 8 ) | ( ( g & 0xFC ) << 3 ) | ( b >> 3 );
	}

	/**
	 * Convert individual RGBA values to RGB8565 24bit format
	 * @param	r		Red component
	 * @param	g		Green component
	 * @param	b		Blue component
	 * @param	a		Alpha component
	 **/
	inline color8565 to8565( uint8_t r, uint8_t g, uint8_t b, uint8_t a ) {
		return ( a << 16 ) | ( ( r & 0xF8 ) << 8 ) | ( ( g & 0xFC ) << 3 ) | ( b >> 3 );
	}

	/**
	 * Convert individual RGB values to RGBA5565 21bit format
	 * @param	r		Red component
	 * @param	g		Green component
	 * @param	b		Blue component
	 * @param	a		Alpha component
	 **/
	inline color5565 to5565( uint8_t r, uint8_t g, uint8_t b, uint8_t a ) {
		return ( ( a & 0xF8 ) << 13 ) | ( ( r & 0xF8 ) << 8 ) | ( ( g & 0xFC ) << 3 ) | ( b >> 3 );
	}

	/**
	 * Convert 32-bit ARGB to 16-bit RGB565 format and 8-bit alpha
	 * @param	colour		The ARGB 32-bit colour
	 * @param	alpha 		(out) The 8-bit alpha (0-255)
	 **/
	inline color565 to565a8( color8888 c, uint8_t& alpha ) {
		alpha = c >> 24;
		return ( ( c >> 8 ) & 0xF800 ) | ( ( c >> 5 ) & 0x07E0 ) | ( ( c >> 3 ) & 0x1F );
	}

	/**
	 * Convert 32-bit ARGB to 16-bit RGB565 format and 5-bit alpha
	 * @param	c			The ARGB 32-bit colour
	 * @param	alpha 		(out) The 5-bit alpha (0-31)
	 **/
	inline color565 to565a5( color8888 c, uint8_t& alpha ) {
		alpha = c >> 27;
		return ( ( c >> 8 ) & 0xF800 ) | ( ( c >> 5 ) & 0x07E0 ) | ( ( c >> 3 ) & 0x1F );
	}

	/**
	 * Convert ARGB 32bit to RGB565 16bit format
	 * @param	c			The RGB 24-bit colour (alpha is ignored)
	 **/
	inline color565 to565( color888 c ) {
		return ( ( c >> 8 ) & 0xF800 ) | ( ( c >> 5 ) & 0x07E0 ) | ( ( c >> 3 ) & 0x1F );
	}

	/**
	 * Convert grayscale 8-bit to RGB565 16-bit format
	 * @param	c			The grayscale color (0-255)
	 **/
	inline color565 to565( uint8_t c ) {
		return ( ( c & 0xF8 ) << 8 ) | ( ( c & 0xFC ) << 3 ) | ( ( c & 0xF8 ) >> 3 );
	}

	/**
	 * Convert mono 1-bit to RGB565 16-bit format
	 * @param	c			The mono color (0,1)
	 **/
	inline color565 monoTo565( uint8_t c ) {
		return ( c & 0b1 ) ? RGB565_White : RGB565_Black;
	}

	/**
	 * Convert HSV to components
	 * @param  H 	Hue component
	 * @param  S  	Saturation component
	 * @param  V 	Value component
	 */
	inline color565 to565( float_t H, float_t S, float_t V ) {
		float_t		p, q, t, ff;
		int8_t		i;
		float_t		r, g, b;

		if ( H >= 360.0 ) H = 0.0;
		H /= 60.0;
		i = (int8_t)H;
		ff = H - i;
		p = V * ( 1.0 - S );
		q = V * ( 1.0 - ( S * ff ) );
		t = V * ( 1.0 - ( S * ( 1.0 - ff ) ) );

		switch ( i ) {
		case 0: r = V; g = t; b = p; break;
		case 1: r = q; g = V; b = p; break;
		case 2: r = p; g = V; b = t; break;
		case 3: r = p; g = q; b = V; break;
		case 4: r = t; g = p; b = V; break;
		case 5:
		default:
			r = V; g = p; b = q; break;
		}

		return ( (uint8_t)( r * 31.0f ) << 11 ) | ( (uint8_t)( g * 63.0f ) << 5 ) | (uint8_t)( b * 31.0f );
	}

	/**
	 * @brief Convert RGB565 color to grayscale in same format
	 *
	 * @param c 			The color
	 * @return color565 	The grayscale color
	 */
	inline color565 to565gs( color565 c ) {
		uint8_t g = ( ( ( c >> 11 ) & 0x1F ) + ( ( c >> 5 ) & 0x3F ) + ( c & 0x1F ) ) >> 2;
		return ( g << 11 ) + ( g << 6 ) + g;
	}

	/*
	 * ### ALPHA BLENDING
	 */

	 /**
	  * Calculate the pre-multiplied value of an RGB565 color for fast blending
	  * @param c  	RGB565 color
	  * @return The prepared color
	  */
	inline uint32_t prepare565( color565 c ) {
		return ( ( (uint32_t)c | ( (uint32_t)c << 16 ) ) & 0b00000111111000001111100000011111 );
	}

	/**
	 * Calculate the pre-multiplied value of a 24-bit RGB color for 565 fast blending
	 * @param c  	RGB888 color
	 * @return The prepared color
	 */
	inline uint32_t prepare565( color888 c ) {
		return ( ( c & 0xF80000 ) >> 8 ) | ( ( c & 0xFC00 ) << 11 ) | ( ( c & 0xF8 ) >> 3 );
	}

	/**
	 * Calculate the pre-multiplied value of 8-bit RGB color components for 565 fast blending.
	 * @param r  		Red color component
	 * @param g  		Green color component
	 * @param b  		Blue color component
	 * @return The prepared color
	 */
	inline uint32_t prepare565( uint8_t r, uint8_t g, uint8_t b ) {
		return ( ( r & 0xF8 ) << 8 ) | ( ( g & 0xFC ) << 19 ) | ( ( b & 0xF8 ) >> 3 );
	}

	/**
	 * Calculate the pre-multiplied value of alpha for fast blending. Converts to range 0-31
	 * @param alpha  	Alpha value 0-255
	 */
	inline uint8_t alpha5bit( uint8_t a ) {
		return a >> 3;
	}
	inline uint8_t alpha5bit( alpha_t a ) {
		return (uint8_t)( alphaClamp( a ) * 31 );
	}

	/**
	 * Blend two 16-bit RGB565 colors. Alpha already in range 0-31 (5-bit).
	 * @param	fg		Color to draw in RGB565 (16bit)
	 * @param	bg		Color to draw over in RGB565 (16bit)
	 * @param	a		Alpha 0 - 31. If in range 0-255, @see blend565a8
	 **/
	inline color565 blend565a5( uint32_t fg, uint32_t bg, uint8_t a ) {
		bg = ( bg | ( bg << 16 ) ) & 0b00000111111000001111100000011111;
		fg = ( fg | ( fg << 16 ) ) & 0b00000111111000001111100000011111;
		uint32_t result = ( ( ( ( fg - bg ) * a ) >> 5 ) + bg ) & 0b00000111111000001111100000011111;
		return (color565)( ( result >> 16 ) | result ); // contract result
	}

	/**
	 * Blend two 16-bit RGB565 colors. Alpha in range 0-255.
	 * @param	fg		Color to draw in RGB565 (16bit)
	 * @param	bg		Color to draw over in RGB565 (16bit)
	 * @param	a		Alpha 0 - 255. If in range 0-31, @see blend565a5
	 **/
	inline color565 blend565a8( uint32_t fg, uint32_t bg, uint8_t a ) {
		a = alpha5bit( a );
		bg = ( bg | ( bg << 16 ) ) & 0b00000111111000001111100000011111;
		fg = ( fg | ( fg << 16 ) ) & 0b00000111111000001111100000011111;
		uint32_t result = ( ( ( ( fg - bg ) * a ) >> 5 ) + bg ) & 0b00000111111000001111100000011111;
		return (color565)( ( result >> 16 ) | result ); // contract result
	}

	/**
	 * Slightly faster blending if the FG color has been pre-prepared.
	 * @param  preparedFg 	Pre-prepared FG color (@see colorPrepare565)
	 * @param  bg  			BG color
	 * @param  a      		Alpha (5-bit 0-31. @see alpha5bit if using 0.0 - 1.0)
	 * @return            	The blended color
	 */
	inline color565 blendPrepared5565( uint32_t preparedFg, uint32_t bg, uint8_t a ) {
		bg = ( bg | ( bg << 16 ) ) & 0b00000111111000001111100000011111;
		uint32_t result = ( ( ( ( preparedFg - bg ) * a ) >> 5 ) + bg ) & 0b00000111111000001111100000011111;
		return (color565)( ( result >> 16 ) | result ); // contract result
	}

	/**
	 * @brief Tint a color with another color
	 *
	 * @param c The color to tint
	 * @param t The color to tint with
	 * @param amount The amount to tint (0.0 - 1.0)
	 * @return color565 The resulting color
	 */
	inline color565 tint( color565 c, color565 t, float_t amount ) {
		amount = alphaClamp( amount );
		uint8_t R = floor( lerp( red( c ), red( t ), amount ) );
		uint8_t G = floor( lerp( green( c ), green( t ), amount ) );
		uint8_t B = floor( lerp( blue( c ), blue( t ), amount ) );
		return to565( R, G, B );
	}

	/**
	 * @brief Darken a colour
	 *
	 * @param c The color to darken
	 * @param amount The amount to darken (0.0 - 1.0)
	 * @return color565 The resulting color
	 */
	inline color565 darken( color565 c, float_t amount ) {
		amount = 1.0 - alphaClamp( amount );
		uint8_t R = floor( red( c ) * amount );
		uint8_t G = floor( green( c ) * amount );
		uint8_t B = floor( blue( c ) * amount );
		return to565( R, G, B );
	}

	/**
	 * @brief Lighten a colour
	 *
	 * @param c The color to lighten
	 * @param amount The amount to lighten (0.0 - 1.0)
	 * @return color565 The resulting color
	 */
	inline color565 lighten( color565 c, float_t amount ) {
		amount = alphaClamp( amount );
		uint8_t R = floor( lerp( red( c ), 255, amount ) );
		uint8_t G = floor( lerp( green( c ), 255, amount ) );
		uint8_t B = floor( lerp( blue( c ), 255, amount ) );
		return to565( R, G, B );
	}

} // namespace

#endif