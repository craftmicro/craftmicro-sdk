#ifndef _CRAFTMICRO_COLOR8888H_
#define _CRAFTMICRO_COLOR8888H_ 1

#include "Common.h"
#include "graphics/Color.h"

/**
 * 32-bit color 8888 (ARGB)
 **/
namespace craft {

	/**
	 * RGB888 colors
	 */
	enum Color8888 {
		ARGB8888_Transparent = 0x00000000,
		ARGB8888_Pink = 0xffffc0cb,
		ARGB8888_LightPink = 0xffffb6c1,
		ARGB8888_HotPink = 0xffff69b4,
		ARGB8888_DeepPink = 0xffff1493,
		ARGB8888_PaleVioletRed = 0xffdb7093,
		ARGB8888_MediumVioletRed = 0xffc71585,
		ARGB8888_LightSalmon = 0xffffa07a,
		ARGB8888_Salmon = 0xfffa8072,
		ARGB8888_DarkSalmon = 0xffe9967a,
		ARGB8888_LightCoral = 0xfff08080,
		ARGB8888_IndianRed = 0xffcd5c5c,
		ARGB8888_Crimson = 0xffdc143c,
		ARGB8888_Firebrick = 0xffb22222,
		ARGB8888_DarkRed = 0xff8b0000,
		ARGB8888_Red = 0xffff0000,
		ARGB8888_OrangeRed = 0xffff4500,
		ARGB8888_Tomato = 0xffff6347,
		ARGB8888_Coral = 0xffff7f50,
		ARGB8888_DarkOrange = 0xffff8c00,
		ARGB8888_Orange = 0xffffa500,
		ARGB8888_Yellow = 0xffffff00,
		ARGB8888_LightYellow = 0xffffffe0,
		ARGB8888_LemonChiffon = 0xfffffacd,
		ARGB8888_LightGoldenrodYellow = 0xfffafad2,
		ARGB8888_PapayaWhip = 0xffffefd5,
		ARGB8888_Moccasin = 0xffffe4b5,
		ARGB8888_PeachPuff = 0xffffdab9,
		ARGB8888_PaleGoldenrod = 0xffeee8aa,
		ARGB8888_Khaki = 0xfff0e68c,
		ARGB8888_DarkKhaki = 0xffbdb76b,
		ARGB8888_Gold = 0xffffd700,
		ARGB8888_Cornsilk = 0xfffff8dc,
		ARGB8888_BlanchedAlmond = 0xffffebcd,
		ARGB8888_Bisque = 0xffffe4c4,
		ARGB8888_NavajoWhite = 0xffffdead,
		ARGB8888_Wheat = 0xfff5deb3,
		ARGB8888_Burlywood = 0xffdeb887,
		ARGB8888_Tan = 0xffd2b48c,
		ARGB8888_RosyBrown = 0xffbc8f8f,
		ARGB8888_SandyBrown = 0xfff4a460,
		ARGB8888_Goldenrod = 0xffdaa520,
		ARGB8888_DarkGoldenrod = 0xffb8860b,
		ARGB8888_Peru = 0xffcd853f,
		ARGB8888_Chocolate = 0xffd2691e,
		ARGB8888_SaddleBrown = 0xff8b4513,
		ARGB8888_Sienna = 0xffa0522d,
		ARGB8888_Brown = 0xffa52a2a,
		ARGB8888_Maroon = 0xff800000,
		ARGB8888_DarkOliveGreen = 0xff556b2f,
		ARGB8888_Olive = 0xff808000,
		ARGB8888_OliveDrab = 0xff6b8e23,
		ARGB8888_YellowGreen = 0xff9acd32,
		ARGB8888_LimeGreen = 0xff32cd32,
		ARGB8888_Lime = 0xff00ff00,
		ARGB8888_LawnGreen = 0xff7cfc00,
		ARGB8888_Chartreuse = 0xff7fff00,
		ARGB8888_GreenYellow = 0xffadff2f,
		ARGB8888_SpringGreen = 0xff00ff7f,
		ARGB8888_MediumSpringGreen = 0xff00fa9a,
		ARGB8888_LightGreen = 0xff90ee90,
		ARGB8888_PaleGreen = 0xff98fb98,
		ARGB8888_DarkSeaGreen = 0xff8fbc8f,
		ARGB8888_MediumAquamarine = 0xff66cdaa,
		ARGB8888_MediumSeaGreen = 0xff3cb371,
		ARGB8888_SeaGreen = 0xff2e8b57,
		ARGB8888_ForestGreen = 0xff228b22,
		ARGB8888_Green = 0xff008000,
		ARGB8888_DarkGreen = 0xff006400,
		ARGB8888_ARGB8888_Aqua = 0xff00ffff,
		ARGB8888_Cyan = 0xff00ffff,
		ARGB8888_LightCyan = 0xffe0ffff,
		ARGB8888_PaleTurquoise = 0xffafeeee,
		ARGB8888_Aquamarine = 0xff7fffd4,
		ARGB8888_Turquoise = 0xff40e0d0,
		ARGB8888_MediumTurquoise = 0xff48d1cc,
		ARGB8888_DarkTurquoise = 0xff00ced1,
		ARGB8888_LightSeaGreen = 0xff20b2aa,
		ARGB8888_CadetBlue = 0xff5f9ea0,
		ARGB8888_DarkCyan = 0xff008b8b,
		ARGB8888_Teal = 0xff008080,
		ARGB8888_LightSteelBlue = 0xffb0c4de,
		ARGB8888_PowderBlue = 0xffb0e0e6,
		ARGB8888_LightBlue = 0xffadd8e6,
		ARGB8888_SkyBlue = 0xff87ceeb,
		ARGB8888_LightSkyBlue = 0xff87cefa,
		ARGB8888_DeepSkyBlue = 0xff00bfff,
		ARGB8888_DodgerBlue = 0xff1e90ff,
		ARGB8888_CornflowerBlue = 0xff6495ed,
		ARGB8888_SteelBlue = 0xff4682b4,
		ARGB8888_RoyalBlue = 0xff4169e1,
		ARGB8888_Blue = 0xff0000ff,
		ARGB8888_MediumBlue = 0xff0000cd,
		ARGB8888_DarkBlue = 0xff00008b,
		ARGB8888_Navy = 0xff000080,
		ARGB8888_MidnightBlue = 0xff191970,
		ARGB8888_Lavender = 0xffe6e6fa,
		ARGB8888_Thistle = 0xffd8bfd8,
		ARGB8888_Plum = 0xffdda0dd,
		ARGB8888_Violet = 0xffee82ee,
		ARGB8888_Orchid = 0xffda70d6,
		ARGB8888_Fuchsia = 0xffff00ff,
		ARGB8888_Magenta = 0xffff00ff,
		ARGB8888_MediumOrchid = 0xffba55d3,
		ARGB8888_MediumPurple = 0xff9370db,
		ARGB8888_BlueViolet = 0xff8a2be2,
		ARGB8888_DarkViolet = 0xff9400d3,
		ARGB8888_DarkOrchid = 0xff9932cc,
		ARGB8888_DarkMagenta = 0xff8b008b,
		ARGB8888_Purple = 0xff800080,
		ARGB8888_Indigo = 0xff4b0082,
		ARGB8888_DarkSlateBlue = 0xff483d8b,
		ARGB8888_SlateBlue = 0xff6a5acd,
		ARGB8888_MediumSlateBlue = 0xff7b68ee,
		ARGB8888_White = 0xffffffff,
		ARGB8888_Snow = 0xfffffafa,
		ARGB8888_Honeydew = 0xfff0fff0,
		ARGB8888_MintCream = 0xfff5fffa,
		ARGB8888_Azure = 0xfff0ffff,
		ARGB8888_AliceBlue = 0xfff0f8ff,
		ARGB8888_GhostWhite = 0xfff8f8ff,
		ARGB8888_WhiteSmoke = 0xfff5f5f5,
		ARGB8888_Seashell = 0xfffff5ee,
		ARGB8888_Beige = 0xfff5f5dc,
		ARGB8888_OldLace = 0xfffdf5e6,
		ARGB8888_FloralWhite = 0xfffffaf0,
		ARGB8888_Ivory = 0xfffffff0,
		ARGB8888_AntiqueWhite = 0xfffaebd7,
		ARGB8888_Linen = 0xfffaf0e6,
		ARGB8888_LavenderBlush = 0xfffff0f5,
		ARGB8888_MistyRose = 0xffffe4e1,
		ARGB8888_Gainsboro = 0xffdcdcdc,
		ARGB8888_LightGray = 0xffd3d3d3,
		ARGB8888_Silver = 0xffc0c0c0,
		ARGB8888_DarkGray = 0xffa9a9a9,
		ARGB8888_Gray = 0xff808080,
		ARGB8888_DimGray = 0xff696969,
		ARGB8888_LightSlateGray = 0xff778899,
		ARGB8888_SlateGray = 0xff708090,
		ARGB8888_DarkSlateGray = 0xff2f4f4f,
		ARGB8888_Black = 0xff000000
	};

	/**
	 * @brief Extract the alpha value from a 32bit color8888 (ARGB) value
	 *
	 * @param c The color
	 * @return uint8_t The 8-bit alpha (0-255)
	 */
	inline uint8_t alpha( color8888 c ) {
		return c >> 24;
	}

	/**
	 * @brief Extract the red channel value from a 32bit color8888 (ARGB) value
	 *
	 * @param c The color
	 * @return uint8_t The 8-bit red value (0-255)
	 */
	inline uint8_t red( color8888 c ) {
		return ( c >> 16 ) & 0xff;
	}

	/**
	 * @brief Extract the green channel value from a 32bit color8888 (ARGB) value
	 *
	 * @param c The color
	 * @return uint8_t The 8-bit green value (0-255)
	 */
	inline uint8_t green( color8888 c ) {
		return ( c >> 8 ) & 0xff;
	}

	/**
	 * @brief Extract the blue channel value from a 32bit color8888 (ARGB) value
	 *
	 * @param c The color
	 * @return uint8_t The 8-bit blue value (0-255)
	 */
	inline uint8_t blue( color8888 c ) {
		return c & 0xff;
	}

	/**
	 * Convert individual RGB values and alpha to RGB8888 32bit format
	 * @param	r		Red component
	 * @param	g		Green component
	 * @param	b		Blue component
	 * @return		The RGB888 color
	 **/
	inline color8888 to8888(
		uint8_t r,
		uint8_t g,
		uint8_t b,
		float_t a
	) {
		return ( alpha8bit( a ) << 24 ) | ( r << 16 ) | ( g << 8 ) | b;
	}

	/**
	 * Convert individual RGB values to RGB8888 32bit format
	 * @param	r		Red component
	 * @param	g		Green component
	 * @param	b		Blue component
	 * @return		The RGB888 color
	 **/
	inline color8888 to8888(
		uint8_t r,
		uint8_t g,
		uint8_t b
	) {
		return ( r << 16 ) | ( g << 8 ) | b;
	}

	/**
	 * Converts RGB565 format to RGB8888 32bit format
	 * @param	color	The RGB565 color to convert
	 * @return		The RGB888 color
	 **/
	inline color8888 to8888( uint16_t c ) {
		return ( ( c & 0b1111100000000000 ) << 8 ) | ( ( c & 0b11100000000 ) << 3 )
			| ( ( c & 0b11111100000 ) << 5 ) | ( ( c & 0b11000000000 ) >> 1 )
			| ( ( c & 0b11111 ) << 3 ) | ( ( c & 0b11100 ) >> 2 );
	}

	/**
	 * Converts grayscale (8-bit) to RGB8888 32bit format
	 * @param  c 	The grayscale value (0-255)
	 * @return		The RGB888 color
	 */
	inline color8888 to8888( uint8_t c ) {
		return ( c << 16 ) | ( c << 8 ) | c;
	}

	/**
	 * Converts mono (1-bit) to RGB8888 32bit format
	 * @param  c 	The mono value (0-1)
	 * @return		The RGB888 color
	 */
	inline color8888 monoTo8888( uint8_t c, color8888 lo = ARGB8888_Black, color8888 hi = ARGB8888_White ) {
		return ( c & 0b1 ) ? hi : lo;
	}

	/**
	 * Convert HSV to an RGB color value
	 * @param  h 	Hue component (0.0 - 360.0)
	 * @param  s  	Saturation component (0.0 - 1.0)
	 * @param  v 	Value component (0.0 - 1.0)
	 * @return color8888 The resulting color
	 */
	inline color8888 to8888( float_t h, float_t s, float_t v ) {
		int i;
		float f, p, q, t;
		float r, g, b;
		v = alphaClamp( v );
		s = alphaClamp( s );
		h = fmod( h, 360.0f );
		if ( h < 0 ) h = 360.0f + h;
		if ( s == 0 ) {
			// achromatic (grey)
			r = g = b = v;
			return ( (uint8_t)( r * 255.0f ) << 16 ) | ( (uint8_t)( g * 255.0f ) << 8 ) | (uint8_t)( b * 255.0f );
		}
		h /= 60;			// sector 0 to 5
		i = floor( h );
		f = h - i;			// factorial part of h
		p = v * ( 1.0f - s );
		q = v * ( 1.0f - s * f );
		t = v * ( 1.0f - s * ( 1.0f - f ) );
		switch ( i ) {
			case 0:
				r = v;
				g = t;
				b = p;
				break;
			case 1:
				r = q;
				g = v;
				b = p;
				break;
			case 2:
				r = p;
				g = v;
				b = t;
				break;
			case 3:
				r = p;
				g = q;
				b = v;
				break;
			case 4:
				r = t;
				g = p;
				b = v;
				break;
			default:		// case 5:
				r = v;
				g = p;
				b = q;
				break;
		}

		return ( (uint8_t)( r * 255.0f ) << 16 ) | ( (uint8_t)( g * 255.0f ) << 8 ) | (uint8_t)( b * 255.0f );
	}

	/**
	 * @brief Convert an 8888 color value to HSV
	 *
	 * @param c The color
	 * @param h (out) Hue
	 * @param s (out) Saturation
	 * @param v (out) Value
	 */
	inline void toHSV( color8888 c, float_t& h, float_t& s, float_t& v ) {
		float_t cmin, cmax, delta;
		float_t r = red( c ) / 255.0f;
		float_t g = green( c ) / 255.0f;
		float_t b = blue( c ) / 255.0f;
		cmin = min( min( r, g ), b );
		cmax = max( max( r, g ), b );
		v = cmax;
		delta = cmax - cmin;
		if ( cmax != 0 ) s = delta / cmax;
		else {
			// r = g = b = 0		// s = 0, v is undefined
			v = 0;
			s = 0;
			h = 0;
			return;
		}
		if ( r == cmax )
			h = delta == 0 ? 0 : ( g - b ) / delta;		// between yellow & magenta
		else if ( g == cmax )
			h = delta == 0 ? 0 : 2 + ( b - r ) / delta;	// between cyan & yellow
		else
			h = delta == 0 ? 0 : 4 + ( r - g ) / delta;	// between magenta & cyan
		h *= 60;						// degrees
		if ( h < 0 ) h += 360;
	}

	/**
	 * Blend two RGB888 pixels
	 * @param	fg		Color to draw in RGB 8-bit (24 bit)
	 * @param	bg		Color to draw over in RGB 8-bit (24 bit)
	 * @param	alpha	Alpha 0-255
	 * @return       Blended color
	 */
	inline color888 blend888( color888 fg, color888 bg, alpha_t alpha ) {
		uint8_t a = alpha8bit( alpha );
		uint32_t rb = fg & 0xff00ff;
		uint32_t g = fg & 0x00ff00;
		rb += ( ( bg & 0xff00ff ) - rb ) * a >> 8;
		g += ( ( bg & 0x00ff00 ) - g ) * a >> 8;
		return ( rb & 0xff00ff ) | ( g & 0xff00 );
	}
	// XXX: fg and bg can have alpha value. premultiply alpha, then blend?
	inline color8888 blend8888( color8888 fg, color8888 bg, alpha_t alpha ) {
		return blend888( fg, bg, alpha );
	}

	/**
	 * Calculate the pre-multiplied value of a 32-bit RGB color to the two
	 * split components required for 888 fast blending.
	 * @param color  	RGB888 color
	 * @param color  	(out) RB split component
	 * @param color  	(out) G split component
	 */
	inline void prepare888( color888 c, uint32_t& rb, uint32_t& g ) {
		rb = c & 0xff00ff;
		g = c & 0x00ff00;
	}

	/**
	 * Calculate the pre-multiplied value of RGB color components to the two
	 * split components required for 888 fast blending.
	 * @param r  		Red color component
	 * @param g  		Green color component
	 * @param b  		Blue color component
	 * @param orb  	(out) RB split component
	 * @param og  	(out) G split component
	 */
	inline void prepareRGB( uint8_t r, uint8_t g, uint8_t b, uint32_t& orb, uint32_t& og ) {
		orb = ( r << 16 ) | b;
		og = g << 8;
	}

	/**
	 * Blend two RGB888 pixels
	 * @param  preparedRB 	Pre-prepared RB split color components (@see colorPrepare888)
	 * @param  preparedG 	Pre-prepared G split color components (@see colorPrepare888)
	 * @param	bg			Color to draw over in RGB 8-bit (24 bit)
	 * @param	alpha		Alpha 0-255 (@see alpha8bit if using 0.0 - 1.0)
	 * @return       Blended color
	 */
	inline color888 blendPrepared888( uint32_t preparedRB, uint32_t preparedG, color888 bg, uint8_t alpha ) {
		preparedRB += ( ( bg & 0xff00ff ) - preparedRB ) * alpha >> 8;
		preparedG += ( ( bg & 0x00ff00 ) - preparedG ) * alpha >> 8;
		return ( preparedRB & 0xff00ff ) | ( preparedG & 0xff00 );
	}

	/**
	 * @brief Tint a color with another color
	 * The alpha of the orginal color is preserved
	 * @param c The color to tint
	 * @param t The color to tint with
	 * @param amount The amount to tint (0.0 - 1.0)
	 * @return color8888 The resulting color
	 */
	inline color8888 tint( color8888 c, color8888 t, float_t amount ) {
		amount = alphaClamp( amount );
		uint8_t R = floor( lerp( red( c ), red( t ), amount ) );
		uint8_t G = floor( lerp( green( c ), green( t ), amount ) );
		uint8_t B = floor( lerp( blue( c ), blue( t ), amount ) );
		return to8888( R, G, B, c >> 24 );
	}

	/**
	 * @brief Darken a colour
	 * The alpha of the orginal color is preserved
	 * @param c The color to darken
	 * @param amount The amount to darken (0.0 - 1.0)
	 * @return color8888 The resulting color
	 */
	inline color8888 darken( color8888 c, float_t amount ) {
		amount = 1.0 - alphaClamp( amount );
		uint8_t R = floor( red( c ) * amount );
		uint8_t G = floor( green( c ) * amount );
		uint8_t B = floor( blue( c ) * amount );
		return to8888( R, G, B, c >> 24 );
	}

	/**
	 * @brief Lighten a colour
	 * The alpha of the orginal color is preserved
	 * @param c The color to lighten
	 * @param amount The amount to lighten (0.0 - 1.0)
	 * @return color8888 The resulting color
	 */
	inline color8888 lighten( color8888 c, float_t amount ) {
		amount = alphaClamp( amount );
		uint8_t R = floor( lerp( red( c ), 255, amount ) );
		uint8_t G = floor( lerp( green( c ), 255, amount ) );
		uint8_t B = floor( lerp( blue( c ), 255, amount ) );
		return to8888( R, G, B, c >> 24 );
	}

} // namespace

#endif