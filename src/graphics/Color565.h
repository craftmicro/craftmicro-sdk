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
	namespace Color565 {
		enum {
			Transparent = 0xf81f,
			Pink = 0xfe19,
			LightPink = 0xfdb8,
			HotPink = 0xfb56,
			DeepPink = 0xf8b2,
			PaleVioletRed = 0xdb92,
			MediumVioletRed = 0xc0b0,
			LightSalmon = 0xfd0f,
			Salmon = 0xfc0e,
			DarkSalmon = 0xecaf,
			LightCoral = 0xf410,
			IndianRed = 0xcaeb,
			Crimson = 0xd8a7,
			Firebrick = 0xb104,
			DarkRed = 0x8800,
			Red = 0xf800,
			OrangeRed = 0xfa20,
			Tomato = 0xfb08,
			Coral = 0xfbea,
			DarkOrange = 0xfc60,
			Orange = 0xfd20,
			Yellow = 0xffe0,
			LightYellow = 0xfffc,
			LemonChiffon = 0xffd9,
			LightGoldenrodYellow = 0xffda,
			PapayaWhip = 0xff7a,
			Moccasin = 0xff36,
			PeachPuff = 0xfed7,
			PaleGoldenrod = 0xef55,
			Khaki = 0xf731,
			DarkKhaki = 0xbdad,
			Gold = 0xfea0,
			Cornsilk = 0xffdb,
			BlanchedAlmond = 0xff59,
			Bisque = 0xff38,
			NavajoWhite = 0xfef5,
			Wheat = 0xf6f6,
			Burlywood = 0xddd0,
			Tan = 0xd5b1,
			RosyBrown = 0xbc71,
			SandyBrown = 0xf52c,
			Goldenrod = 0xdd24,
			DarkGoldenrod = 0xbc21,
			Peru = 0xcc27,
			Chocolate = 0xd343,
			SaddleBrown = 0x8a22,
			Sienna = 0xa285,
			Brown = 0xa145,
			Maroon = 0x8000,
			DarkOliveGreen = 0x5345,
			Olive = 0x8400,
			OliveDrab = 0x6c64,
			YellowGreen = 0x9e66,
			LimeGreen = 0x3666,
			Lime = 0x07e0,
			LawnGreen = 0x7fe0,
			Chartreuse = 0x7fe0,
			GreenYellow = 0xafe5,
			SpringGreen = 0x07ef,
			MediumSpringGreen = 0x07d3,
			LightGreen = 0x9772,
			PaleGreen = 0x9fd3,
			DarkSeaGreen = 0x8df1,
			MediumAquamarine = 0x6675,
			MediumSeaGreen = 0x3d8e,
			SeaGreen = 0x2c4a,
			ForestGreen = 0x2444,
			Green = 0x0400,
			DarkGreen = 0x0320,
			Aqua = 0x07ff,
			Cyan = 0x07ff,
			LightCyan = 0xe7ff,
			PaleTurquoise = 0xaf7d,
			Aquamarine = 0x7ffa,
			Turquoise = 0x471a,
			MediumTurquoise = 0x4e99,
			DarkTurquoise = 0x067a,
			LightSeaGreen = 0x2595,
			CadetBlue = 0x5cf4,
			DarkCyan = 0x0451,
			Teal = 0x0410,
			LightSteelBlue = 0xb63b,
			PowderBlue = 0xb71c,
			LightBlue = 0xaedc,
			SkyBlue = 0x867d,
			LightSkyBlue = 0x867f,
			DeepSkyBlue = 0x05ff,
			DodgerBlue = 0x1c9f,
			CornflowerBlue = 0x64bd,
			SteelBlue = 0x4416,
			RoyalBlue = 0x435c,
			Blue = 0x001f,
			MediumBlue = 0x0019,
			DarkBlue = 0x0011,
			Navy = 0x0010,
			MidnightBlue = 0x18ce,
			Lavender = 0xe73f,
			Thistle = 0xddfb,
			Plum = 0xdd1b,
			Violet = 0xec1d,
			Orchid = 0xdb9a,
			Fuchsia = 0xf81f,
			Magenta = 0xf81f,
			MediumOrchid = 0xbaba,
			MediumPurple = 0x939b,
			BlueViolet = 0x895c,
			DarkViolet = 0x901a,
			DarkOrchid = 0x9999,
			DarkMagenta = 0x8811,
			Purple = 0x8010,
			Indigo = 0x4810,
			DarkSlateBlue = 0x49f1,
			SlateBlue = 0x6ad9,
			MediumSlateBlue = 0x7b5d,
			White = 0xffff,
			Snow = 0xffdf,
			Honeydew = 0xf7fe,
			MintCream = 0xf7ff,
			Azure = 0xf7ff,
			AliceBlue = 0xf7df,
			GhostWhite = 0xffdf,
			WhiteSmoke = 0xf7be,
			Seashell = 0xffbd,
			Beige = 0xf7bb,
			OldLace = 0xffbc,
			FloralWhite = 0xffde,
			Ivory = 0xfffe,
			AntiqueWhite = 0xff5a,
			Linen = 0xff9c,
			LavenderBlush = 0xff9e,
			MistyRose = 0xff3c,
			Gainsboro = 0xdefb,
			LightGray = 0xd69a,
			Silver = 0xc618,
			DarkGray = 0xad55,
			Gray = 0x8410,
			DimGray = 0x6b4d,
			LightSlateGray = 0x7453,
			SlateGray = 0x7412,
			DarkSlateGray = 0x2a69,
			Black = 0x0000
		}; // enum
	}; // namespace Color565

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
		return ( c & 0b1 ) ? Color565::White : Color565::Black;
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