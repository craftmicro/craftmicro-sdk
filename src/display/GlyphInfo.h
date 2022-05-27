#pragma once

#include "Common.h"
#include "geom/ClipRect.h"
#include "utils/MemoryPool.h"
#include "utils/LinkedList.h"

namespace craft {

    /**
     * Display list that stores a list of display objects in render order.
     */
    class GlyphInfo : public LinkedList<GlyphInfo>, public MemoryPool<GlyphInfo> {

    public:

        /**
         * Create factory method. Uses memory pool
         * for object re-use.
         */
        static GlyphInfo* Create(char c) {
            GlyphInfo* obj = MemoryPool<GlyphInfo>::Create();
            obj->code = c;
            return obj;
        }

        /**
         * @brief Construct a new Glyph Info object
         */
        GlyphInfo();

        /**
         * @brief Destroy the Glyph Info object
         */
        ~GlyphInfo();

        /**
         * Reset all properties
         */
        void reset();

        /**
         * @brief Set the glyph to a new character and position
         *
         * @param c 	The character code
         * @param x 	The x position
         * @param baseline The y position of the baseline
         */
        void set(char c);

        /**
         * @brief The character code of this glyph
         */
        char code = 0;

        /**
         * @brief Rect describing the graphical bounds of the glyph
         */
        ClipRect* bounds = nullptr;

        /**
         * @brief Pointer to the character data
         */
        const uint8_t* charData = nullptr;

        /**
         * @brief Pointer to the current line of character data
         */
        uint32_t dataOffset = 0;

        /**
         * @brief Indicate whether the glyph has started rendering yet
         */
        boolean renderStarted = false;

        /**
         * @brief Number of repeats left on current line
         */
        int8_t lineRepeat = 0;

        /**
         * @brief Width of the glyph (to next character)
         */
        uint32_t width = 0;

        /**
         * Inserts a glyph into the list into sorted order by x position
         * @param glyph The glyph to insert
         */
        void insert(GlyphInfo* glyph);

    };

} // namespace craft
