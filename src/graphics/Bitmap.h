#pragma once
#ifndef _CRAFTMICRO_BITMAPH_
#define _CRAFTMICRO_BITMAPH_ 1

#include "Common.h"
#include "graphics/Color.h"
#include "graphics/Color8888.h"
#include "graphics/Color565.h"

/**
 * Bitmap and tilemap
 **/
namespace craft {

	/**
	 * Pixel formats
	 **/
	typedef enum {
		PF_UNKNOWN = 0,
		PF_565 = 1,	//  RGB 565		5 bits red, 6 bits green, 5 bits blue
		PF_4444 = 2,	// ARGB 4444	4 bits alpha, 4 bits each color channel (16 bits total)
		PF_6666 = 3,	// ARGB 6666	6 bits alpha, 6 bits each color channel (24 bits total)
		PF_8565 = 4,	// ARGB 8565	565 with leading 8-bit alpha (24 bits total)
		PF_888 = 5,	//  RGB 888		24-bit color, no alpha
		PF_8888 = 6,	// ARGB 8888	32-bit color with leading b-bit alpha
		PF_INDEXED = 7,	// 				Indexed color (0-255)
		PF_MONO = 8,	// 				Mono (on/off) color
		PF_GRAYSCALE8 = 9,	// 				256 levels of gray (intensity)
		PF_GRAYSCALE4 = 10,	//				16 levels of gray (intensity)
		PF_GRAYSCALE2 = 11	//				4 levels of gray (intensity)
	} PixelFormat;

	/**
	 * Check whether a pixel format includes an alpha channel or not
	 * @param  pixelFormat The pixel format to check
	 * @return             Return true if the pixel format has an alpha channel, otherwise false
	 */
	bool pixelFormatHasAlpha( PixelFormat pixelFormat );

	/**
	 * Return the width, in bits, of a pixel stored in this format
	 * @param  pixelFormat The pixel format to check
	 * @return             The width in number of bits
	 */
	uint8_t pixelFormatBitWidth( PixelFormat pixelFormat );

	/**
	 * Return the width, in bytes, of a pixel stored in this format
	 * @param  pixelFormat The pixel format to check
	 * @return             The width in number of bytes
	 */
	uint8_t pixelFormatByteWidth( PixelFormat pixelFormat );

	/**
	 * Holds details of a bitmap in flash memory
	 **/
	typedef struct BitmapS {
		PixelFormat pixelFormat;			// The format of each pixel
		uint32_t transparentColor;			// For non-alpha pixel formats, the color to treat as fully transparent. Usually fuchsia.
		uint32_t dataSize;					// The total number of bytes in the data
		uint32_t width;						// Width of bitmap
		uint32_t height;					// height of bitmap
		const uint8_t* data __attribute__( ( aligned( 4 ) ) ); // Data, aligned to 4-byte boundary
	} BitmapData;

	/**
	 * Holds details of a tile map in flash memory
	 **/
	typedef struct TilemapS {
		PixelFormat pixelFormat;			// The format of each pixel
		uint32_t transparentColor;			// For non-alpha pixel formats, the color to treat as fully transparent. Usually fuchsia.
		uint32_t dataSize;					// The total number of bytes in the data
		const uint8_t* data __attribute__( ( aligned( 4 ) ) ); // Data, aligned to 4-byte boundary
		uint32_t tileWidth;					// Width of each tile in the map
		uint32_t tileHeight;				// height of each tile in the map
		uint32_t tileCount;					// Number of tiles in the map
		uint32_t tileStride;				// Stride of each tile in bytes
	} TilemapData;

	/**
	 *  ######   #####  ######
	 *  ##      ##      ##
	 *  #####   #####   #####
	 *      ##  ##  ##      ##
	 *  #####    ####   #####
	 */

	 /*
	  * ### BITMAP ACCESS
	  */

	  /**
	   * The following functions get a pixel from a bitmap and convert to RGB565 and 5-bit alpha.
	   * Use these functions if you are using the fast alpha-blending function below that requires
	   * 5-bit alpha (0-31). If you are using libraries that require 8-bit alpha, use the ...as8565
	   * functions instead.
	   */
	void get565as5565( uint8_t* p, uint16_t& c, uint8_t& a );
	void get4444as5565( uint8_t* p, uint16_t& c, uint8_t& a );
	void get6666as5565( uint8_t* p, uint16_t& c, uint8_t& a );
	void get8565as5565( uint8_t* p, uint16_t& c, uint8_t& a );
	void get888as5565( uint8_t* p, uint16_t& c, uint8_t& a );
	void get8888as5565( uint8_t* p, uint16_t& c, uint8_t& a );
	void get8as5565( uint8_t* p, uint16_t& c, uint8_t& a );
	void get1as5565( uint8_t* p, uint16_t& c, uint8_t& a );

	/**
	 * Accessor function type to get pixels in 5565 format
	 */
	typedef void ( *access5565 )( uint8_t*, uint16_t&, uint8_t& );

	/**
	 * Use getAccessor5565 on a tilemap to choose the correct data access function.
	 */
	access5565 getAccessor5565( PixelFormat pixelFormat );

	/**
	 * The following functions get a pixel from a bitmap and convert to RGB565 and 8-bit alpha.
	 */
	void get565as8565( uint8_t* p, uint16_t& c, uint8_t& a );
	void get4444as8565( uint8_t* p, uint16_t& c, uint8_t& a );
	void get6666as8565( uint8_t* p, uint16_t& c, uint8_t& a );
	void get8565as8565( uint8_t* p, uint16_t& c, uint8_t& a );
	void get888as8565( uint8_t* p, uint16_t& c, uint8_t& a );
	void get8888as8565( uint8_t* p, uint16_t& c, uint8_t& a );
	void get8as8565( uint8_t* p, uint16_t& c, uint8_t& a );
	void get1as8565( uint8_t* p, uint16_t& c, uint8_t& a );

	/**
	 * Use getAccessor8565 on a tilemap to choose the correct data access function.
	 */
	typedef void ( *access8565 )( uint8_t*, uint16_t&, uint8_t& );
	access8565 getAccessor8565( PixelFormat pixelFormat );

	/**
	 * The following functions get a pixel from the bitmap and convert to 8-bit per channel A,R,G,B components.
	 */
	void get565asARGB( uint8_t* p, uint8_t& a, uint8_t& r, uint8_t& g, uint8_t& b );
	void get4444asARGB( uint8_t* p, uint8_t& a, uint8_t& r, uint8_t& g, uint8_t& b );
	void get6666asARGB( uint8_t* p, uint8_t& a, uint8_t& r, uint8_t& g, uint8_t& b );
	void get8565asARGB( uint8_t* p, uint8_t& a, uint8_t& r, uint8_t& g, uint8_t& b );
	void get888asARGB( uint8_t* p, uint8_t& a, uint8_t& r, uint8_t& g, uint8_t& b );
	void get8888asARGB( uint8_t* p, uint8_t& a, uint8_t& r, uint8_t& g, uint8_t& b );
	void get8asARGB( uint8_t* p, uint8_t& a, uint8_t& r, uint8_t& g, uint8_t& b );
	void get1asARGB( uint8_t* p, uint8_t& a, uint8_t& r, uint8_t& g, uint8_t& b );

	/**
	 * Use getAccessorARGB on a tilemap to choose the correct data access function.
	 */
	typedef void ( *accessARGB )( uint8_t*, uint8_t&, uint8_t&, uint8_t&, uint8_t& );
	accessARGB getAccessorARGB( PixelFormat pixelFormat );

	/**
	 * The following functions get a pixel from the bitmap and convert to 32-bit ARGB value.
	 * Use getAccessor8888 to select the correct function to use. The parameters are:
	 * @param p Pointer to the pixel data
	 * @param i Index, in pixels, into the pixel data
	 * @param c (out) the color of the pixel in 8888 format
	 */
	void get565as8888( uint8_t* p, uint32_t i, uint32_t& c );
	void get4444as8888( uint8_t* p, uint32_t i, uint32_t& c );
	void get6666as8888( uint8_t* p, uint32_t i, uint32_t& c );
	void get8565as8888( uint8_t* p, uint32_t i, uint32_t& c );
	void get888as8888( uint8_t* p, uint32_t i, uint32_t& c );
	void get8888as8888( uint8_t* p, uint32_t i, uint32_t& c );
	void get8as8888( uint8_t* p, uint32_t i, uint32_t& c );
	void get4as8888( uint8_t* p, uint32_t i, uint32_t& c );
	void get2as8888( uint8_t* p, uint32_t i, uint32_t& c );
	void get1as8888( uint8_t* p, uint32_t i, uint32_t& c );

	/**
	 * Use getAccessor8888 on a tilemap to choose the correct data access function.
	 */
	typedef void ( *access8888 )( uint8_t*, uint32_t, uint32_t& );
	access8888 getAccessor8888( PixelFormat pixelFormat );

} // ns

#endif