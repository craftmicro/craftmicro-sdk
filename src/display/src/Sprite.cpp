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

    void Sprite::update(float_t dt, boolean isRenderUpdate) {
        // Update self

        // Update children
        DisplayObject::update(dt, isRenderUpdate);
    }

    void Sprite::beginLine(int16_t ry) {
        switch (transform) {
            case Transform::FlipH:
                _dataOffset = (tileIndex * tilemapData->tileHeight + ry + 1) * tilemapData->tileWidth - renderBounds->x - 1;
                _dataStep = -1;
                break;
            case Transform::FlipV:
                _dataOffset = ((tileIndex + 1) * tilemapData->tileHeight - ry - 1) * tilemapData->tileWidth + renderBounds->x;
                _dataStep = 1;
                break;
            case Transform::FlipH | Transform::FlipV:
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
            case BlendMode::Stamp:
                _ra = (_rc & 255) / 255.0;
                _rc = color;
                break;
            default:
                _ra = (_rc >> 24) / 255.0;
        }
    }

    /**
     * Layered Sprite
     */

    LayeredSprite* LayeredSprite::Create(const LayeredSpriteData* data, uint8_t animation, bool start) {
        LayeredSprite* sprite = MemoryPool<LayeredSprite>::Create();
        sprite->set(data, animation, start);
        return sprite;
    }

    void LayeredSprite::reset() {
        _data = nullptr;
        _anim = nullptr;
        _frame = nullptr;
        _playing = false;
        _framePos = 0;
        _frameIndex = 0;
        _animForward = true;
    }

    void LayeredSprite::set(const LayeredSpriteData* data, uint8_t animation, bool start) {
        reset();
        if (data) {
            _data = data;
            width(_data->width);
            height(_data->height);
            this->animation(animation);
            if (start) this->resume();
        }
        dirty();
    }

    void LayeredSprite::animation(int index) {
        if (index < 0 || index >= _data->animCount) {
            _anim = nullptr;
            _frame = nullptr;
            _frameIndex = 0;
            _animForward = true;
            return;
        }
        _anim = &_data->animData[index];
        if (_anim->direction == AnimationDirection::Reverse) {
            _frameIndex = _anim->frameCount - 1;
            _animForward = false;
        }
        else {
            _frameIndex = 0;
            _animForward = true;
        }
        _frame = &_anim->frameData[_frameIndex];
    }

    void LayeredSprite::position(float_t pos, bool advance) {
        int8_t newIndex = _frameIndex;
        if (!advance) {
            _framePos = 0;
            if (_anim->direction == AnimationDirection::Reverse) {
                newIndex = _anim->frameCount - 1;
                _animForward = false;
            }
            else {
                newIndex = 0;
                _animForward = true;
            }
            if (newIndex != _frameIndex) {
                _frameIndex = newIndex;
                _frame = &_anim->frameData[_frameIndex];
                dirty();
            }
        }
        float_t r;
        while (pos > 0) {
            r = (_frame->duration - _framePos) - pos;
            if (r < 0) {
                if (_animForward) {
                    newIndex++;
                    if (newIndex >= _anim->frameCount) {
                        if (_anim->direction == AnimationDirection::PingPong) {
                            newIndex = _anim->frameCount - 2;
                            if (newIndex < 0) newIndex = 0;
                            _animForward = false;
                        }
                        else {
                            newIndex = 0;
                        }
                    }
                }
                else {
                    newIndex--;
                    if (newIndex < 0) {
                        if (_anim->direction == AnimationDirection::PingPong) {
                            newIndex = 1;
                            if (_anim->frameCount < 2) newIndex = 0;
                            _animForward = true;
                        }
                        else {
                            newIndex = _anim->frameCount - 1;
                        }
                    }
                }
                _frame = &_anim->frameData[newIndex];
                _framePos = 0;
                pos += r;
            }
            else {
                _framePos += pos;
                pos = -1.0f;
            }
        }
        if (newIndex != _frameIndex) {
            _frameIndex = newIndex;
            _frame = &_anim->frameData[_frameIndex];
            dirty();
        }
    }

    void LayeredSprite::pause() {
        _playing = false;
    }

    void LayeredSprite::resume() {
        _playing = true;
    }

    void LayeredSprite::update(float_t dt, boolean isRenderUpdate) {
        // Update self
        if (isRenderUpdate) {
            if (_playing) position(dt, true);
        }

        // Update children
        DisplayObject::update(dt, isRenderUpdate);
    }

    int LayeredSprite::getAnimationIndex(string name) {
        int offset = 0;
        int len = 0;
        for (int a = 0; a < _data->animCount; a++) {
            len = _data->animNames[offset];
            for (int c = 0; c < len; c++) {
                if (_data->animNames[offset + 1 + c] != name.c_str()[c]) {
                    offset += (len + 1);
                    break;
                }
            }
            return a;
        }
        return -1;
    }

    void LayeredSprite::beginLine(int16_t ry) {}

    void LayeredSprite::calcPixel(int16_t rx, int16_t ry) {
        if (!_frame) return;

        // Step through each layer
        _ra = 0.0;
        const LayeredSpriteLayer* layer;
        const LayeredSpritePart* part;
        color8888 c;
        uint8_t a;
        for (int i = 0; i < _frame->layerCount; i++) {
            layer = &_frame->layerData[i];
            part = &_data->partData[layer->partIndex];
            int partWidth = part->width;
            int partHeight = part->height;
            if (layer->orientation & Transform::Rotate90) {
                partWidth = part->height;
                partHeight = part->width;
            }
            // Check if part visible
            if (rx >= layer->x && rx < (layer->x + partWidth) && ry >= layer->y && ry < (layer->y + partHeight)) {
                // Draw pixel
                c = _data->paletteData[part->partData[layer->start + (ry - layer->y) * layer->strideY + (rx - layer->x) * layer->strideX]];
                a = c >> 24;
                if (a > 0) {
                    _rc = c;
                    _ra = 1.0; //(_rc >> 24) / 255.0;
                }
            }
        }
    }

} // namespace craft