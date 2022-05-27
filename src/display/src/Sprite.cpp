#include "../Sprite.h"

namespace craft {

    Sprite* Sprite::Create(const TilemapData* tilemapData, uint16_t tileIndex) {
        Sprite* sprite = MemoryPool<Sprite>::Create();
        sprite->set(tilemapData, tileIndex);
        return sprite;
    }

    void Sprite::reset() {
        tilemapData = nullptr;
        tileIndex = 0;
        _getPixelAs8888 = nullptr;
    }

    void Sprite::set(const TilemapData* tilemapData, uint16_t tileIndex) {
        reset();
        if (tilemapData) {
            this->tilemapData = tilemapData;
            this->tileIndex = tileIndex;
            width(tilemapData->tileWidth);
            height(tilemapData->tileHeight);
            _getPixelAs8888 = getAccessor8888(tilemapData->pixelFormat);
        }
        dirty();
    }

    void Sprite::update(float_t dt) {
        // Update self

        // Update children
        DisplayObject::update(dt);
    }

    void Sprite::beginLine(int16_t ry) {
        switch (transform) {
            case Transform::flipH:
                _dataOffset = (tileIndex * tilemapData->tileHeight + ry + 1) * tilemapData->tileWidth - renderBounds->x - 1;
                _dataStep = -1;
                break;
            case Transform::flipV:
                _dataOffset = ((tileIndex + 1) * tilemapData->tileHeight - ry - 1) * tilemapData->tileWidth + renderBounds->x;
                _dataStep = 1;
                break;
            case Transform::flipHV:
            case Transform::rotate180:
                _dataOffset = ((tileIndex + 1) * tilemapData->tileHeight - ry) * tilemapData->tileWidth - renderBounds->x - 1;
                _dataStep = -1;
                break;
            default:
                _dataOffset = (tileIndex * tilemapData->tileHeight + ry) * tilemapData->tileWidth + renderBounds->x;
                _dataStep = 1;
        }
    }

    void Sprite::calcPixel(int16_t rx, int16_t ry) {
        _getPixelAs8888((uint8_t*)tilemapData->data, _dataOffset, _rc);
        _dataOffset += _dataStep;
        switch (blendMode) {
            case BlendMode::stamp:
                _ra = (_rc & 255) / 255.0;
                _rc = color;
                break;
            default:
                _ra = (_rc >> 24) / 255.0;
        }
    }

} // namespace craft