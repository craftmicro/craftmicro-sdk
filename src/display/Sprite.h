#pragma once

#include "display/DisplayObject.h"
#include "graphics/Bitmap.h"

namespace craft {

    /**
     * Blend modes supported by Sprite
     */
    enum class BlendMode {
        normal,
        stamp
    };

    /**
     * Transformations supported by Sprite
     */
    enum class Transform {
        normal,
        flipH,
        flipV,
        flipHV,
        rotate180
    };

    /**
     * A sprite
     */
    class Sprite : public DisplayObject, public MemoryPool<Sprite> {
    public:

        /**
         * Create a new object or take one from the pool
         * @return The new or recycled object
         */
        static Sprite* Create(const TilemapData* tilemapData, uint16_t tileIndex = 0);

        /**
         * @brief Reset the sprite back to defaults
         */
        void reset() override;

        /**
         * Update the display object.
         * @param	dt 			Time since last update in seconds
         */
        void update(float_t dt) override;

        /**
         * The tilemap that contains the sprite bitmap data.
         * Do not change directly. Use set() to change this.
         */
        const TilemapData* tilemapData;

        /**
         * The index of the tile within the tilemap.
         */
        uint16_t tileIndex;

        /**
         * transform for sprite
         */
        Transform transform = Transform::normal;

        /**
         * Blend mode for sprite
         */
        BlendMode blendMode = BlendMode::normal;

        /**
         * Color (used for some blend modes)
         */
        color888 color;

        /**
         * @brief Whether to smooth/anti-alias the sprite when it is rotated
         * Setting this to false results in faster performance. Setting it to true
         * results in a more accurate render.
         */
        bool smoothing = false;

        /**
         * Set the tilemap and the tileIndex that the sprite uses.
         * @param tilemap 	The tilemap to use
         * @param tileIndex The index of the active tile
         */
        virtual void set(const TilemapData* tilemapData, uint16_t tileIndex = 0);

        /**
         * prepare to render the next line
         * @param ry The y position in local coordinates
         */
        virtual void beginLine(int16_t ry);

        /**
         * Read a pixel from the sprite and advance position
         * @param rx The x position in local coordinates
         * @param ry The y position in local coordinates
         */
        virtual void calcPixel(int16_t rx, int16_t ry);

    protected:
        /**
         * Pixel accessor for correct tilemap pixel format
         */
        access8888 _getPixelAs8888;

        /**
         * Current offset into the pixel data
         */
        int32_t _dataOffset;

        /**
         * Current setp with each drawn pixel
         */
        int32_t _dataStep;

    };

} // namespace craft
