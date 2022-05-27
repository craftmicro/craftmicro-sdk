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
	namespace Color8888 {
		enum {
			Transparent = 0x00000000,
			Pink = 0xffffc0cb,
			LightPink = 0xffffb6c1,
			HotPink = 0xffff69b4,
			DeepPink = 0xffff1493,
			PaleVioletRed = 0xffdb7093,
			MediumVioletRed = 0xffc71585,
			LightSalmon = 0xffffa07a,
			Salmon = 0xfffa8072,
			DarkSalmon = 0xffe9967a,
			LightCoral = 0xfff08080,
			IndianRed = 0xffcd5c5c,
			Crimson = 0xffdc143c,
			Firebrick = 0xffb22222,
			DarkRed = 0xff8b0000,
			Red = 0xffff0000,
			OrangeRed = 0xffff4500,
			Tomato = 0xffff6347,
			Coral = 0xffff7f50,
			DarkOrange = 0xffff8c00,
			Orange = 0xffffa500,
			Yellow = 0xffffff00,
			LightYellow = 0xffffffe0,
			LemonChiffon = 0xfffffacd,
			LightGoldenrodYellow = 0xfffafad2,
			PapayaWhip = 0xffffefd5,
			Moccasin = 0xffffe4b5,
			PeachPuff = 0xffffdab9,
			PaleGoldenrod = 0xffeee8aa,
			Khaki = 0xfff0e68c,
			DarkKhaki = 0xffbdb76b,
			Gold = 0xffffd700,
			Cornsilk = 0xfffff8dc,
			BlanchedAlmond = 0xffffebcd,
			Bisque = 0xffffe4c4,
			NavajoWhite = 0xffffdead,
			Wheat = 0xfff5deb3,
			Burlywood = 0xffdeb887,
			Tan = 0xffd2b48c,
			RosyBrown = 0xffbc8f8f,
			SandyBrown = 0xfff4a460,
			Goldenrod = 0xffdaa520,
			DarkGoldenrod = 0xffb8860b,
			Peru = 0xffcd853f,
			Chocolate = 0xffd2691e,
			SaddleBrown = 0xff8b4513,
			Sienna = 0xffa0522d,
			Brown = 0xffa52a2a,
			Maroon = 0xff800000,
			DarkOliveGreen = 0xff556b2f,
			Olive = 0xff808000,
			OliveDrab = 0xff6b8e23,
			YellowGreen = 0xff9acd32,
			LimeGreen = 0xff32cd32,
			Lime = 0xff00ff00,
			LawnGreen = 0xff7cfc00,
			Chartreuse = 0xff7fff00,
			GreenYellow = 0xffadff2f,
			SpringGreen = 0xff00ff7f,
			MediumSpringGreen = 0xff00fa9a,
			LightGreen = 0xff90ee90,
			PaleGreen = 0xff98fb98,
			DarkSeaGreen = 0xff8fbc8f,
			MediumAquamarine = 0xff66cdaa,
			MediumSeaGreen = 0xff3cb371,
			SeaGreen = 0xff2e8b57,
			ForestGreen = 0xff228b22,
			Green = 0xff008000,
			DarkGreen = 0xff006400,
			Aqua = 0xff00ffff,
			Cyan = 0xff00ffff,
			LightCyan = 0xffe0ffff,
			PaleTurquoise = 0xffafeeee,
			Aquamarine = 0xff7fffd4,
			Turquoise = 0xff40e0d0,
			MediumTurquoise = 0xff48d1cc,
			DarkTurquoise = 0xff00ced1,
			LightSeaGreen = 0xff20b2aa,
			CadetBlue = 0xff5f9ea0,
			DarkCyan = 0xff008b8b,
			Teal = 0xff008080,
			LightSteelBlue = 0xffb0c4de,
			PowderBlue = 0xffb0e0e6,
			LightBlue = 0xffadd8e6,
			SkyBlue = 0xff87ceeb,
			LightSkyBlue = 0xff87cefa,
			DeepSkyBlue = 0xff00bfff,
			DodgerBlue = 0xff1e90ff,
			CornflowerBlue = 0xff6495ed,
			SteelBlue = 0xff4682b4,
			RoyalBlue = 0xff4169e1,
			Blue = 0xff0000ff,
			MediumBlue = 0xff0000cd,
			DarkBlue = 0xff00008b,
			Navy = 0xff000080,
			MidnightBlue = 0xff191970,
			Lavender = 0xffe6e6fa,
			Thistle = 0xffd8bfd8,
			Plum = 0xffdda0dd,
			Violet = 0xffee82ee,
			Orchid = 0xffda70d6,
			Fuchsia = 0xffff00ff,
			Magenta = 0xffff00ff,
			MediumOrchid = 0xffba55d3,
			MediumPurple = 0xff9370db,
			BlueViolet = 0xff8a2be2,
			DarkViolet = 0xff9400d3,
			DarkOrchid = 0xff9932cc,
			DarkMagenta = 0xff8b008b,
			Purple = 0xff800080,
			Indigo = 0xff4b0082,
			DarkSlateBlue = 0xff483d8b,
			SlateBlue = 0xff6a5acd,
			MediumSlateBlue = 0xff7b68ee,
			White = 0xffffffff,
			Snow = 0xfffffafa,
			Honeydew = 0xfff0fff0,
			MintCream = 0xfff5fffa,
			Azure = 0xfff0ffff,
			AliceBlue = 0xfff0f8ff,
			GhostWhite = 0xfff8f8ff,
			WhiteSmoke = 0xfff5f5f5,
			Seashell = 0xfffff5ee,
			Beige = 0xfff5f5dc,
			OldLace = 0xfffdf5e6,
			FloralWhite = 0xfffffaf0,
			Ivory = 0xfffffff0,
			AntiqueWhite = 0xfffaebd7,
			Linen = 0xfffaf0e6,
			LavenderBlush = 0xfffff0f5,
			MistyRose = 0xffffe4e1,
			Gainsboro = 0xffdcdcdc,
			LightGray = 0xffd3d3d3,
			Silver = 0xffc0c0c0,
			DarkGray = 0xffa9a9a9,
			Gray = 0xff808080,
			DimGray = 0xff696969,
			LightSlateGray = 0xff778899,
			SlateGray = 0xff708090,
			DarkSlateGray = 0xff2f4f4f,
			Black = 0xff000000
		}; // enum
	}; // namespace

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
	inline color8888 monoTo8888( uint8_t c, color8888 lo = Color8888::Black, color8888 hi = Color8888::White ) {
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