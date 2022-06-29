#include "../Text.h"
#include "utils/Math.h"

namespace craft {

    /**
     * @brief Construct a new Text object
     */
    Text::Text() {}

    /**
     * @brief Destroy the Text object
     */
    Text::~Text() {
        while (_glyphs) {
            GlyphInfo* glyph = _glyphs;
            _glyphs = _glyphs->next();
            glyph->recycle();
        }
    }

    /**
     * @brief Create a new object by passing in a font definition, or take one from the pool
     * @return The new or recycled object
     */
    Text* Text::Create(const packedbdf_t* font) {
        Text* object = MemoryPool<Text>::Create();
        object->font(font);
        return object;
    }

    /**
     * @brief Set the font that this text uses
     * @param font 	The font to use
     */
    void Text::font(const packedbdf_t* font) {
        if (_font) delete _font;
        _font = new Font(font);

        dirty();
    }

    /**
     * @brief Set the text color
     * @param c The text color
     */
    void Text::color(color888 c) {
        if (_color == c) return;
        _color = c;
        dirty();
    }

    /**
     * @brief Set the line spacing of the text
     * @param lh 	The line spacing. Usually between 1 - 1.5
     */
    void Text::lineSpacing(float_t lh) {
        if (_lineSpacing == lh) return;
        _lineSpacing = lh;
        _needsCalc = true;
        dirty();
    }

    /**
     * @brief Set the text alignment
     * @param align The alignment
     */
    void Text::align(TextAlign a) {
        if (_align == a) return;
        _align = a;
        dirty();
    }

    /**
     * @brief Set the text wrap type
     * @param w The wrap type
     */
    void Text::wrap(TextWrap w) {
        if (_wrap == w) return;
        _wrap = w;
        _needsCalc = true;
        dirty();
    }

    /**
     * @brief Set the text string
     * @param t The text string
     */
    void Text::text(const char* t) {
        _text = t;
        _needsCalc = true;
        dirty();
    }

    /**
     * @brief Set the width
     * This sets the width of the text area. A string will wrap at or before the text area
     * depending on the wrap setting. If the width is set to 0, the width is calculated
     * automatically based on the maximum width of the text string.
     * @param value The new width
     */
    void Text::width(float_t value) {
        DisplayObject::width(value);
        _autoWidth = (_localBounds->width() == 0);
        _needsCalc = true;
    }

    /**
     * @return float_t The width
     */
    float_t Text::width() {
        if (_needsCalc) _calculateSize();
        return DisplayObject::width();
    }

    /**
     * @brief Set the height
     * This sets the height of the text area. If the height is set to 0, the height is calculated
     * automatically based on the maximum height of the text string (with wrapping).
     * @param value The new height
     */
    void Text::height(float_t value) {
        DisplayObject::height(value);
        _autoHeight = (_localBounds->height() == 0);
        _needsCalc = true;
    }

    /**
     * @return float_t The height
     */
    float_t Text::height() {
        if (_needsCalc) _calculateSize();
        return DisplayObject::height();
    }

    /**
     * @brief Set the tab width in number of spaces
     * @param spaces The number of spaces for a tab
     */
    void Text::tabWidth(uint8_t spaces) {
        _tabWidth = spaces;
    }

    /**
     * @brief Get the tab width in number of spaces
     * @return uint8_t The number of spaces for a tab
     */
    uint8_t Text::tabWidth() {
        return _tabWidth;
    }

    /**
     * @brief Set the global transform of the display object
     *
     * @param t The parent transformation matrix
     */
    void Text::transform(Matrix* t) {
        // Do we need to recalculate text area?
        if (_needsCalc) _calculateSize();

        // Now we can calc global position
        DisplayObject::transform(t);
    }

    /**
     * @brief Called every frame to begin rendering this object
     * @param y The global y coordinate
     */
    void Text::beginRender(ClipRect* updateArea) {
        DisplayObject::beginRender(updateArea);

        // Calculate how many lines of text this is
        uint16_t lines = (uint16_t)(renderBounds->y / _lineHeight);

        // Calculate where the next line will start
        // XXX: Line spacing
        _nextLineY = lines * _lineHeight;

        // Ignore glyphs for specified number of lines
        _endOfText = false;
        _charIndex = 0;
        _justWrapped = false;
        while (lines--) {
            _prepareLine(true);
            if (_endOfText) break;
        }
    }

    /**
     * Prepare to render the next line
     * @param ry The local y coordinate
     */
    void Text::beginLine(int16_t ry) {
        // Exit early if we have no more characters to render
        if (_endOfText && !_glyphs) return;

        // Check if we are starting a new line of glyphs, and add them if we are
        if (ry >= _nextLineY) {
            _prepareLine(false);
            _nextLineY += _lineHeight;
        }

        // Step through all glyphs. Remove any that are complete. Inform others of current line
        GlyphInfo* g = _glyphs;
        GlyphInfo* n;
        while (g) {
            n = g->next();
            if (ry > g->bounds->y2) {
                GlyphInfo* n = g->next();
                g->remove();
                if (g == _glyphs) _glyphs = n;
                g->recycle();
            }
            else {
                _font->beginLine(g, ry);
            }
            g = n;
        }
    }

    /**
     * Read a pixel from the object and advance position
     * @param c (out) color
     * @param a (out) alpha
     */
    void Text::calcPixel(int16_t rx, int16_t ry) {
        _ra = 0;
        _rc = _color;

        // Exit early if we have no more characters to render
        if (_endOfText && !_glyphs) return;

        GlyphInfo* g = _glyphs;
        while (g) {
            if (g->bounds->contains(rx, ry)) {
                _ra = _font->getPixel(g, rx);
            }
            g = g->next();
        }
    }

    /**
     * @brief Called every frame to begin rendering this object
     */
    void Text::endRender() {
        // Clear any remaining glyphs
        while (_glyphs) {
            GlyphInfo* glyph = _glyphs;
            _glyphs = _glyphs->next();
            glyph->recycle();
        }
        _glyphs = 0;
    }

    /**
     * @brief Prepare the next line of glyphs
     *
     * @param skip If true, will not add the glyphs to the render list
     */
    void Text::_prepareLine(bool skip) {
        int32_t startCharIndex = _charIndex;
        int32_t endCharIndex = _charIndex;
        int16_t charWidth = 0;
        int16_t lineWidth = 0;
        int16_t lineWidthAtEndChar = 0;
        GlyphInfo* glyph = 0;
        bool ignoreRest __attribute__((unused)) = false;
        char c = 0;

        lineWidth = 0;
        while (true) {
            c = _text[_charIndex++];
            charWidth = 0;
            if (c == '\0') { // EOF
                _endOfText = true;
                endCharIndex = _charIndex - 1;
                break;
            }
            else if (c == '\t') { // tab
                if (_justWrapped) {
                    charWidth = 0;
                    startCharIndex = _charIndex;
                }
                else {
                    charWidth = _font->spaceWidth() * _tabWidth;
                }
                endCharIndex = _charIndex;
                lineWidthAtEndChar = lineWidth;
            }
            else if (c == ' ') { // space
                if (_justWrapped) {
                    charWidth = 0;
                    startCharIndex = _charIndex;
                }
                else {
                    charWidth = _font->spaceWidth();
                }
                endCharIndex = _charIndex;
                lineWidthAtEndChar = lineWidth;
            }
            else if (c == '\n') { // newline
                _justWrapped = false;
                endCharIndex = _charIndex;
                lineWidthAtEndChar = lineWidth;
                break; // next line
            }
            else if (_isPrintable(c)) { // printable character
                charWidth = _font->charWidth(c);
                if ((c == ',') || (c == '.')) { // Potential wrap point
                    endCharIndex = _charIndex;
                    lineWidthAtEndChar = lineWidth;
                }
                _justWrapped = false;
            }

            // Are we wider than the text area?
            if ((lineWidth + charWidth) > (int)_localBounds->width()) {
                // See if character wrap is set
                if (_wrap == TextWrap::character) {
                    _charIndex--;
                    if (_charIndex == startCharIndex) _charIndex++;
                    endCharIndex = _charIndex;
                    lineWidthAtEndChar = lineWidth;
                    break; // next line
                }
                // Wrap if there is a suitable point earlier in this line to wrap to
                else if (endCharIndex > 0) {
                    // Start next line
                    _justWrapped = true;
                    _charIndex = endCharIndex;
                    break; // next line
                }
                // Long single word on line. Add the current glyph (will be
                // clipped) and skip the rest until a wrap.
                else {
                    ignoreRest = true;
                }
            }

            // Increase line width by character
            lineWidth += charWidth;
        }

        // Adjust for text align
        if (_align == TextAlign::right) {
            lineWidth = Math::max(0, (int)_localBounds->width() - lineWidthAtEndChar);
        }
        else if (_align == TextAlign::center) {
            lineWidth = Math::max(0, ((int)_localBounds->width() - (float_t)lineWidthAtEndChar) / 2);
        }
        else {
            lineWidth = 0;
        }

        // Are we skipping glyphs?
        if (skip) return;

        // Now having start and end indexes in the string, add the glyphs
        while (startCharIndex < endCharIndex) {
            c = _text[startCharIndex++];
            if (_isPrintable(c)) {
                glyph = _font->glyphInfo(c);
                if (glyph) {
                    glyph->bounds->translate(lineWidth - _ox, _nextLineY);
                    if (!_glyphs) _glyphs = glyph;
                    else _glyphs->add(glyph);

                    lineWidth += glyph->width;
                }
            }
            else if (c == ' ') {
                lineWidth += _font->spaceWidth();
            }
            else if (c == '\t') {
                lineWidth += _font->spaceWidth() * _tabWidth;
            }
        }

        /* Debug glyphs
        Serial.println("Glyphs:");
        GlyphInfo* g = _glyphs;
        while (g) {
            Serial.printf("  %c: %d,%d %dx%d\n", g->code, g->bounds->x, g->bounds->y, g->bounds->width, g->bounds->height );
            g = g->next();
        }*/

    }

    /**
     * @brief Calculate the size of the text area based on the text string
     */
    void Text::_calculateSize() {
        _needsCalc = false;
        _lineHeight = (int16_t)((float_t)_font->lineHeight() * _lineSpacing);
        if (_autoWidth) {
            int16_t maxWidth = 0;
            int16_t lineWidth = 0;
            int16_t lineHeight = _lineHeight;
            int16_t index = 0;
            char c = 0;
            while (true) {
                if (lineWidth > maxWidth) maxWidth = lineWidth;
                c = _text[index++];
                if (c == '\0') break; // End of string
                if (c == '\t') { // tab
                    lineWidth += _font->spaceWidth() * _tabWidth;
                    continue;
                }
                if (c == '\n') { // newline
                    lineWidth = 0;
                    if (!_autoHeight && (lineHeight >= (int)_localBounds->height())) break; // Reached height
                    lineHeight += _lineHeight;
                    continue;
                }
                lineWidth += _font->charWidth(c);
            }
            width(maxWidth);
            if (_autoHeight) height(lineHeight);
        }
        else if (_autoHeight) {
            int16_t lineWidth = 0;
            int16_t charWidth = 0;
            int16_t lineHeight = _lineHeight;
            int32_t index = 0;
            int16_t wrapIndex = 0;
            bool justWrapped = false; // Wrap without newline just occured
            char c = 0;
            while (true) {
                c = _text[index++];
                charWidth = 0;
                if (c == '\0') { // EOF
                    if (wrapIndex == index) lineHeight -= _lineHeight; // If just wrapped, don't count this line
                    break;
                }
                else if (c == '\t') { // tab
                    charWidth = justWrapped ? 0 : _font->spaceWidth() * _tabWidth;
                    wrapIndex = index;
                }
                else if (c == ' ') { // space
                    charWidth = justWrapped ? 0 : _font->spaceWidth();
                    wrapIndex = index;
                }
                else if (c == '\n') { // newline
                    justWrapped = false;
                    wrapIndex = index;

                    charWidth = 0;
                    lineWidth = 0;
                    lineHeight += _lineHeight;
                }
                else if (_isPrintable(c)) { // printable character
                    charWidth = _font->charWidth(c);
                    if ((c == ',') || (c == '.')) { // Potential wrap point				
                        wrapIndex = index;
                    }
                    justWrapped = false;
                }

                // Are we wider than the text area?
                if ((lineWidth + charWidth) > (int)_localBounds->width()) {
                    // See if character wrap is set
                    if (_wrap == TextWrap::character) {
                        index--;
                        if (index == wrapIndex) index++;
                        wrapIndex = index;

                        charWidth = 0;
                        lineWidth = 0;
                        lineHeight += _lineHeight;
                    }
                    // Wrap if there is a suitable point earlier in this line to wrap to
                    else if (wrapIndex > 0) {
                        // Start next line
                        justWrapped = true;
                        index = wrapIndex;

                        charWidth = 0;
                        lineWidth = 0;
                        lineHeight += _lineHeight;
                    }
                    // Long single word on line. Add the current glyph (will be
                    // clipped) and skip the rest until a wrap.
                    else {
                        // Ignore
                    }
                }

                // Increase line width by character
                lineWidth += charWidth;
            }
            height(lineHeight);
        }
    }

    /**
     * @brief Check if a character is a printable character (has a glyph)
     *
     * @param c The character
     * @return bool True if printable
     */
    bool Text::_isPrintable(uint8_t c) {
        if (c < 32) return false;
        if (c > 126) return false;
        return true;
    }

} // namespace craft