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
        if (!advance) {
            _framePos = 0;
            if (_anim->direction == AnimationDirection::Reverse) {
                _frameIndex = _anim->frameCount - 1;
                _animForward = false;
            }
            else {
                _frameIndex = 0;
                _animForward = true;
            }
        }
        _frame = &_anim->frameData[_frameIndex];
        /*
        int p = pos * 1000;
        while (p > 0) {
            p -= (_frame->duration - _framePos);
            if (p <= 0) {
                if (_animForward) {
                    _frameIndex++;
                    if (_frameIndex >= _anim->frames) {
                        if (_anim->direction == AnimationDirection::PingPong) {
                            _frameIndex--;
                            _animForward = false;
                        }
                        else {
                            _frameIndex = 0;
                        }
                    }
                }
                else {
                    _frameIndex--;
                    if (_frameIndex <= 0) {
                        if (_anim->direction == AnimationDirection::PingPong) {
                            _frameIndex++;
                            _animForward = true;
                        }
                        else {
                            _frameIndex = _anim->frames - 1;
                        }
                    }
                }
                _frame = _anim->frameData[_frameIndex];
                _framePos = 0;
            }
        }
        */
    }

    void LayeredSprite::pause() {
        _playing = false;
    }

    void LayeredSprite::resume() {
        _playing = true;
    }

    void LayeredSprite::update(float_t dt) {
        // Update self
        if (_playing) position(dt, true);

        // Update children
        DisplayObject::update(dt);
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

} // namespace craft