#pragma once
#ifndef _CRAFTMICRO_FONTH_
#define _CRAFTMICRO_FONTH_ 1

#include "Common.h"
#include "display/PackedBDF.h"
#include "display/GlyphInfo.h"

namespace craft {

	/**
	 * A font class that implements the packed BDF format
	 */
	class Font {
	public:

		/**
		 * @brief Construct a new Font object
		 */
		Font( packedbdf_t* font );

		/**
		 * @brief Get the line height
		 */
		uint8_t lineHeight();

		/**
		 * @brief Return the pixel width of a character
		 *
		 * @param c 	The ordinal character code
		 * @return uint8_t The width, in pixels
		 */
		uint8_t charWidth( uint16_t c );

		/**
		 * @brief Return the pixel width of spaces
		 *
		 * @return uint8_t The width of a space
		 */
		uint8_t spaceWidth();

		/**
		 * @brief Check if the character is valid
		 *
		 * @param c The character
		 * @return true If the character is part of this font set
		 * @return false If the character is not in this font set
		 */
		bool isValidChar( uint16_t c );

		/**
		 * @brief Return the glyph info for the specified character
		 *
		 * @param c 	The ordinal character code
		 * @return GlyphInfo*	The GlyphInfo
		 */
		GlyphInfo* glyphInfo( uint16_t c );

		/**
		 * @Brief Prepare to render the next line
		 *
		 * @param glyph The glyph info object containing the character details
		 * @param y The local y coordinate
		 */
		void beginLine( GlyphInfo* glyph, int16_t y );

		/**
		 * @brief Fetch a pixel on the current line at the specified x coordinate
		 *
		 * @see beginLine
		 *
		 * @param glyph The glyph info object containing the character details
		 * @param x The x coordinate
		 * @return float_t The pixel value (0.0 - 1.0)
		 */
		float_t getPixel( GlyphInfo* glyph, int16_t x );

	protected:

		/**
		 * @brief The packed font data
		 */
		packedbdf_t* _font = 0;

		/**
		 * @brief Bits Per Pixel
		 * BPP is 1 (1 bit per pixel, so either on or off) For non-anti-aliased fonts. The BPP can
		 * be either 2, 4 or 8 for anti-aliased fonts.
		 */
		uint8_t _bpp = 1;

		/**
		 * @brief The mask used to extract bits from a byte
		 */
		uint8_t _mask = 1;

		/**
		 * @brief Alpha multiplier
		 * This is used to calculate the pixel alpha based on the bit value
		 */
		float_t _alphaMX = 1;

		/**
		 * @brief Data offset to read the delta (spaced to next character)
		 */
		uint32_t _deltaOffset = 0;

		/**
		 * @brief Width of the space character
		 */
		uint32_t _spaceWidth = 0;

		/**
		 * @brief Fetch a single bit
		 * @param p Pointer to the data
		 * @param index Bit index into the data
		 * @return uint32_t The value of the bit
		 */
		uint32_t _fetchbit( const uint8_t* p, uint32_t index );

		/**
		 * @brief Fetch specified number of bits as an unsigned integer
		 *
		 * @param p Pointer to the data
		 * @param index Bit index into the data
		 * @param required Number of bits required
		 * @return uint32_t The value of the bits
		 */
		uint32_t _fetchbits_unsigned( const uint8_t* p, uint32_t index, uint32_t required );

		/**
		 * @brief Fetch specified number of bits as a signed integer
		 *
		 * @param p Pointer to the data
		 * @param index Bit index into the data
		 * @param required Number of bits required
		 * @return int32_t The value of the bits
		 */
		int32_t _fetchbits_signed( const uint8_t* p, uint32_t index, uint32_t required );

	};

} // namespace

#endif