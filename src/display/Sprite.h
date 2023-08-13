#pragma once

#include "display/DisplayObject.h"
#include "graphics/Bitmap.h"

namespace craft {

    /**
     * Blend modes supported by Sprite
     */
    enum class BlendMode {
        Normal,
        Stamp
    };

    /**
     * Transformations supported by Sprite
     * E.g. rotate = Rotate90 | FlipH
     */
    typedef enum {
        None = 0,
        FlipH = 1,
        FlipV = 2,
        Rotate90 = 4,
    } Transform;

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
         * @param	dt 			    Time since last update in seconds
         * @param   isRenderUpdate  True if this update is during the render phase, false otherwise
         */
        void update(float_t dt, boolean isRenderUpdate = false) override;

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
        Transform transform = Transform::None;

        /**
         * Blend mode for sprite
         */
        BlendMode blendMode = BlendMode::Normal;

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
        void set(const TilemapData* tilemapData, uint16_t tileIndex = 0);

        /**
         * prepare to render the next line
         * @param ry The y position in local coordinates
         */
        void beginLine(int16_t ry);

        /**
         * Read a pixel from the sprite and advance position
         * @param rx The x position in local coordinates
         * @param ry The y position in local coordinates
         */
        void calcPixel(int16_t rx, int16_t ry);

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

    typedef enum {
        Forward = 0,
        Reverse = 1,
        PingPong = 2,
    } AnimationDirection;

    struct LayeredSpritePart {
        uint16_t width;                         // Size of part
        uint16_t height;
        int16_t anchorX;                        // Coord of anchor of part
        int16_t anchorY;
        const uint8_t* partData;                // Pixel data (palette indexes)
    };

    struct LayeredSpriteLayer {
        uint8_t partIndex;                      // The part in this layer
        uint8_t orientation;                    // Orientation of the part
        int16_t x;                              // Coords of the part in this layer
        int16_t y;
        uint32_t start;                         // The index into the data to start drawing from (depends on orientation)
        int16_t strideX;                        // The stride in each direction (depends on orientation)
        int16_t strideY;
    };

    struct LayeredSpriteFrame {
        float_t duration;                       // seconds
        uint8_t layerCount;                     // Number of layers
        const LayeredSpriteLayer* layerData;    // Layer structs
    };

    struct LayeredSpriteAnim {
        uint8_t direction;                      // AnimationDirection
        uint8_t frameCount;                     // Number of frames
        const LayeredSpriteFrame* frameData;    // Frame structs
    };

    struct LayeredSpriteData {
        uint8_t paletteCount;                   // Number of palette entries
        const color8888* paletteData;           // ARGB color
        uint8_t partCount;                      // Number of parts
        const LayeredSpritePart* partData;      // Part structs
        uint8_t animCount;                      // Number of animations
        const LayeredSpriteAnim* animData;      // Animation structs
        const int8_t* animNames;                // Animation name data (0=len,1...len=name)
        uint16_t width;                         // Size of sprite
        uint16_t height;
        int16_t anchorX;                        // Coord of anchor of sprite
        int16_t anchorY;
    };

    class LayeredSprite : public DisplayObject, public MemoryPool<LayeredSprite> {
    public:
        /**
         * @brief Construct a new Layered Sprite object
         * The data is usually stored in flashmem
         * @param data The data for the sprite
         * @param animation The index of the active animation
         */
        static LayeredSprite* Create(const LayeredSpriteData* data, uint8_t animation = 0, bool start = false);

        /**
         * @brief Reset the layered sprite back to defaults
         */
        void reset() override;

        /**
         * Update the display object.
         * @param	dt 			    Time since last update in seconds
         * @param   isRenderUpdate  True if this update is during the render phase, false otherwise
         */
        void update(float_t dt, boolean isRenderUpdate = false) override;

        /**
         * Set the data and the animation that the sprite uses.
         * @param tilemap 	The layered sprite data to use
         * @param animation The index of the active animation
         * @param start     True if the animation should start immediately from the beginning
         */
        void set(const LayeredSpriteData* data, uint8_t animation = 0, bool start = false);

        /**
         * @brief Set the active animation
         *
         * @param index The index of the animation
         */
        void animation(int index);

        /**
         * @brief Set the active animation
         *
         * @param name The animation name
         * @return int The index of the animation
         */
        int animation(const char* name);

        /**
         * @brief Set or change the position of the animation
         *
         * @param dt The time from which to start the animation
         * @param advance If true, will advance the position from the current position. Otherwise will start at the beginning
         */
        void position(float_t dt = 0, bool advance = false);

        /**
         * @brief Pause the animation at the current position
         */
        void pause();

        /**
         * @brief Resume the animation from the current position
         */
        void resume();

        /**
         * prepare to render the next line
         * @param ry The y position in local coordinates
         */
        void beginLine(int16_t ry);

        /**
         * Read a pixel from the sprite and advance position
         * @param rx The x position in local coordinates
         * @param ry The y position in local coordinates
         */
        void calcPixel(int16_t rx, int16_t ry);

        /**
         * @brief Get the index of the animation by name
         * String comparison is slow. Use it once and cache the index.
         * @param name The animation name
         * @return int The index
         */
        int getAnimationIndex(const char* name);

    protected:
        // The sprite data
        const LayeredSpriteData* _data = nullptr;

        // The active animation
        const LayeredSpriteAnim* _anim = nullptr;
        // The current advance direction
        bool _animForward = true;

        // The active frame
        const LayeredSpriteFrame* _frame = nullptr;
        // The active frame index
        uint8_t _frameIndex = 0;
        // Total millis into the frame
        float_t _framePos = 0;

        // Flag to indicate whether the animation is playing
        bool _playing = false;
    };

} // namespace craft
