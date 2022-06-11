#include "../Font.h"

namespace craft {

    /**
     * @brief Construct a new Font object
     */
    Font::Font(const packedbdf_t* font) {
        _font = font;

        // Anti-aliased (multi-bit pixels)
        if (_font->version == 23) {
            _bpp = (_font->reserved & 0b000011) + 1;
            _alphaMX = 1.0 / ((1 << _bpp) - 1);
        }
        // Aliased (single-bit pixels)
        else {
            _bpp = 1;
            _alphaMX = 1.0;
        }
        _mask = (1 << _bpp) - 1;
        _deltaOffset = 3 + _font->bits_width + _font->bits_height + _font->bits_xoffset + _font->bits_yoffset;
        _spaceWidth = charWidth(32);
    }

    /**
     * @brief Get the line height
     */
    uint8_t Font::lineHeight() {
        return _font->line_space;
    }

    /**
     * @brief Get the width of a space
     */
    uint8_t Font::spaceWidth() {
        return _spaceWidth;
    }

    /**
     * @brief Check if the character is valid
     *
     * @param c The character
     * @return true If the character is part of this font set
     * @return false If the character is not in this font set
     */
    bool Font::isValidChar(uint16_t c) {
        // Check character is supported by the font
        if ((c >= _font->index1_first) && (c <= _font->index1_last)) {
            return true;
        }
        else if ((c >= _font->index2_first) && (c <= _font->index2_last)) {
            return true;
        }
        return false;
    }

    /**
     * @brief Return the pixel width of a character
     *
     * @param c 	The ordinal character code
     * @return uint8_t The width, in pixels (0 if not found)
     */
    uint8_t Font::charWidth(uint16_t c) {
        uint32_t bitoffset;
        const uint8_t* data;

        // Check character is supported by the _font
        if ((c >= _font->index1_first) && (c <= _font->index1_last)) {
            bitoffset = c - _font->index1_first;
            bitoffset *= _font->bits_index;
        }
        else if ((c >= _font->index2_first) && (c <= _font->index2_last)) {
            bitoffset = c - _font->index2_first + _font->index1_last - _font->index1_first + 1;
            bitoffset *= _font->bits_index;
        }
        else if (_font->unicode) {
            return 0;
        }
        else {
            return 0;
        }

        // Char data
        uint32_t goffset = _fetchbits_unsigned(_font->index, bitoffset, _font->bits_index);
        data = _font->data + goffset;
        return _fetchbits_unsigned(data, _deltaOffset, _font->bits_delta);
    }

    /**
     * @brief Return the glyph info for the specified character
     *
     * @param c 	The ordinal character code
     * @return GlyphInfo*	The GlyphInfo
     */
    GlyphInfo* Font::glyphInfo(uint16_t c) {
        // Get teh glyph info object to populate
        GlyphInfo* g = GlyphInfo::Create(c);

        // Check character is supported by the _font
        if ((c >= _font->index1_first) && (c <= _font->index1_last)) {
            g->dataOffset = c - _font->index1_first;
            g->dataOffset *= _font->bits_index;
        }
        else if ((c >= _font->index2_first) && (c <= _font->index2_last)) {
            g->dataOffset = c - _font->index2_first + _font->index1_last - _font->index1_first + 1;
            g->dataOffset *= _font->bits_index;
        }
        else if (_font->unicode) {
            return g;
        }
        else {
            return g;
        }

        // Char data
        uint32_t goffset = _fetchbits_unsigned(_font->index, g->dataOffset, _font->bits_index);
        g->charData = _font->data + goffset;

        uint32_t encoding = _fetchbits_unsigned(g->charData, 0, 3);
        if (encoding != 0) return g;

        int16_t width = _fetchbits_unsigned(g->charData, 3, _font->bits_width);
        g->dataOffset = _font->bits_width + 3;
        int16_t height = _fetchbits_unsigned(g->charData, g->dataOffset, _font->bits_height);
        g->dataOffset += _font->bits_height;

        int32_t xoffset = _fetchbits_signed(g->charData, g->dataOffset, _font->bits_xoffset);
        g->dataOffset += _font->bits_xoffset;
        int32_t yoffset = _fetchbits_signed(g->charData, g->dataOffset, _font->bits_yoffset);
        g->dataOffset += _font->bits_yoffset;

        g->bounds->setPosAndSize(xoffset, _font->line_space - height - yoffset, width, height);
        g->width = _fetchbits_unsigned(g->charData, g->dataOffset, _font->bits_delta);
        g->dataOffset += _font->bits_delta;

        // For anti-aliased (multi-bit pixel) fonts pixel data start at a byte boundary
        if (_bpp > 1) g->dataOffset = ((g->dataOffset + 7) & (-8));

        return g;
    }

    /**
     * Prepare to render the next line
     * @param y The y position in local coordinates
     */
    void beginLine(GlyphInfo* glyph, int16_t y);

    /**
     * @Brief Prepare to render the next line
     *
     * @param glyph The glyph info object containing the character details
     * @param y The local y coordinate
     */
    void Font::beginLine(GlyphInfo* glyph, int16_t y) {
        // Check if render has started
        if (!glyph->renderStarted) {
            int16_t dy = y - glyph->bounds->y;
            // reached the first line of the glyph
            if (dy >= 0) {
                // Start rendering this glyph
                glyph->renderStarted = true;
                // For aliased fonts, calculate data offset from start of data down to current line
                if (_bpp == 1) {
                    if (_fetchbit(glyph->charData, glyph->dataOffset++)) {
                        glyph->lineRepeat = _fetchbits_unsigned(glyph->charData, glyph->dataOffset, 3) + 1;
                        glyph->dataOffset += 3;
                    }
                    while (dy--) beginLine(glyph, y);
                }
                // Anti-alias fonts don't support line repeat, so calc offset directly
                else {
                    glyph->dataOffset += dy * glyph->bounds->width * _bpp;
                }
            }
        }
        // Already started
        else {
            // Check if we are repeating the same line again
            if (glyph->lineRepeat > 0) glyph->lineRepeat--;
            // Otherwise, advance offset to point to the data for the next line
            else {
                // Next line
                glyph->dataOffset += glyph->bounds->width * _bpp;
                // just aliased fonts, check for line repeat
                if (_bpp == 1) {
                    if (_fetchbit(glyph->charData, glyph->dataOffset++)) {
                        glyph->lineRepeat = _fetchbits_unsigned(glyph->charData, glyph->dataOffset, 3) + 1;
                        glyph->dataOffset += 3;
                    }
                }
            }
        }
    }

    /**
     * @brief Fetch a pixel on the current line at the specified x coordinate
     *
     * @see beginLine
     *
     * @param glyph The glyph info object containing the character details
     * @param x The x position in local coordinates
     * @return float_t The pixel value (0.0 - 1.0)
     */
    float_t Font::getPixel(GlyphInfo* glyph, int16_t x) {
        uint32_t index = glyph->dataOffset + (x - glyph->bounds->x) * _bpp;
        if (_bpp == 1) {
            return (float_t)_fetchbit(glyph->charData, index);
        }
        else {
            uint8_t shift = (8 - (index & 7) - _bpp);
            uint8_t b = (glyph->charData[index >> 3] >> shift) & _mask;
            return (float_t)b * _alphaMX;
        }
    }

    /**
     * @brief Fetch a single bit
     * @param p Pointer to the data
     * @param index Bit index into the data
     * @return uint32_t The value of the bit
     */
    uint32_t Font::_fetchbit(const uint8_t* p, uint32_t index) {
        if (p[index >> 3] & (1 << (7 - (index & 7)))) return 1;
        return 0;
    }

    /**
     * @brief Fetch specified number of bits as an unsigned integer
     *
     * @param p Pointer to the data
     * @param index Bit index into the data
     * @param required Number of bits required
     * @return uint32_t The value of the bits
     */
    uint32_t Font::_fetchbits_unsigned(const uint8_t* p, uint32_t index, uint32_t required) {
        uint32_t val = 0;
        do {
            uint8_t b = p[index >> 3];
            uint32_t avail = 8 - (index & 7);
            if (avail <= required) {
                val <<= avail;
                val |= b & ((1 << avail) - 1);
                index += avail;
                required -= avail;
            }
            else {
                b >>= avail - required;
                val <<= required;
                val |= b & ((1 << required) - 1);
                break;
            }
        } while (required);
        return val;
    }

    /**
     * @brief Fetch specified number of bits as a signed integer
     *
     * @param p Pointer to the data
     * @param index Bit index into the data
     * @param required Number of bits required
     * @return int32_t The value of the bits
     */
    int32_t Font::_fetchbits_signed(const uint8_t* p, uint32_t index, uint32_t required) {
        uint32_t val = _fetchbits_unsigned(p, index, required);
        if (val & (1 << (required - 1))) {
            return (int32_t)val - (1 << required);
        }
        return (int32_t)val;
    }

} // namespace craft