#pragma once

#include "display/DisplayObject.h"
#include "graphics/Bitmap.h"
#include "display/Font.h"
#include "display/GlyphInfo.h"
#include "geom/ClipRect.h"

namespace craft {

    /**
     * Text alignment
     */
    enum class TextAlign {
        left,
        right,
        center
    };

    /**
     * Text wrap
     */
    enum class TextWrap {
        word,
        character,
        none
    };

    /**
     * A text area
     */
    class Text : public DisplayObject, public MemoryPool<Text> {
    public:

        /**
         * @brief Construct a new Text object
         */
        Text();

        /**
         * @brief Destroy the Text object
         */
        ~Text();

        /**
         * Create a new object or take one from the pool
         * @return The new or recycled object
         */
        static Text* Create(const packedbdf_t* font);

        /**
         * @brief Set the font that this text uses
         * @param font 	The font to use
         */
        void font(const packedbdf_t* font);

        /**
         * @brief Set the text color
         * @param c The text color
         */
        void color(color888 c);

        /**
         * @brief Set line spacing of the text
         * @param lh 	The line spacing. Usually between 1 - 1.5
         */
        void lineSpacing(float_t lh);

        /**
         * @brief Set the text alignment
         * @param a The alignment
         */
        void align(TextAlign a);

        /**
         * @brief Set the text wrap type
         * @param w The wrap type
         */
        void wrap(TextWrap w);

        /**
         * @brief Set the text string
         * @param t The text string
         */
        void text(const char* t);

        /**
         * @brief Set the width
         * This sets the width of the text area. A string will wrap at or before the text area
         * depending on the wrap setting. If the width is set to 0, the width is calculated
         * automatically based on the maximum width of the text string.
         * @param value The new width
         */
        void width(float_t value);

        /**
         * @return float_t The width
         */
        float_t width();

        /**
         * @brief Set the height
         * This sets the height of the text area. If the height is set to 0, the height is calculated
         * automatically based on the maximum height of the text string (with wrapping).
         * @param value The new height
         */
        void height(float_t value);

        /**
         * @return float_t The height
         */
        float_t height();

        /**
         * @brief Set the tab width in number of spaces
         * @param spaces The number of spaces for a tab
         */
        void tabWidth(uint8_t spaces);

        /**
         * @brief Get the tab width in number of spaces
         * @return uint8_t The number of spaces for a tab
         */
        uint8_t tabWidth();

        /**
         * @brief Set the global position of the display object
         *
         * @param x The global X position
         * @param y The global Y position
         */
        virtual void globalPos(float_t x, float_t y);

        /**
         * @brief Begin the render sweep for the current frame
         * @param updateArea The area of the display being updated
         */
        virtual void beginRender(ClipRect* updateArea);

        /**
         * Prepare to render the next line
         * @param ry The y position in local coordinates
         */
        virtual void beginLine(int16_t ry);

        /**
         * Read a pixel from the sprite and advance position
         * @param rx The x position in local coordinates
         * @param ry The y position in local coordinates
         */
        virtual void calcPixel(int16_t rx, int16_t ry);

        /**
         * @brief End the render cycle for the current frame
         * @see beginRender
         */
        virtual void endRender();

    protected:
        const char* _text = 0;				// The text string
        Font* _font = 0;				// The font to use
        color888 _color = 0;			// The color of the text

        boolean _needsCalc = false;		// Need to recaculate text area metrics
        boolean _endOfText = false;		// Have reached the end of the text string

        float_t _lineSpacing = 1.25f;		// Spacing from one line of text to the next, based on font line height
        int16_t _lineHeight = 0;		// Linme height in pixels calculated from font size and lineSpacing
        TextAlign _align = TextAlign::left;	// Horizontal text alignment
        TextWrap _wrap = TextWrap::word;	// Type of wrapping
        boolean _autoWidth = true;		// Text area width set automatically cased on text
        boolean _autoHeight = true;		// Text area height set automatically based on text
        uint8_t _tabWidth = 4;			// number of spaces in tab

        GlyphInfo* _glyphs = 0;			// List of glyphs currently being rendered
        int16_t _nextLineY = 0;			// Start y position of the next line
        int32_t _charIndex = 0;			// Current character index
        boolean _justWrapped = false; 	// Unforced wrap just occured

        /**
         * @brief Calculate the size of the text area based on the text string
         *
         * Will automatically calculate width and height based on the _autoWidth and _autoHeight settings
         */
        void _calculateSize();

        /**
         * @brief Prepare the next line of glyphs
         *
         * @param skip If true, will not add the glyphs to the render list
         */
        void _prepareLine(boolean skip);

        /**
         * @brief Check if a character is a printable character (has a glyph)
         *
         * @param c The character
         * @return boolean True if printable
         */
        boolean _isPrintable(uint8_t c);

    };

} // namespace craft
