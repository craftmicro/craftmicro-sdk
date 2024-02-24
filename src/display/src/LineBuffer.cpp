#include "../LineBuffer.h"

namespace craft {

    LineBuffer::LineBuffer(Display* display) {
        this->display = display;
        int scaledWidth = (int)(display->width / display->pixelScale);
        int scaledHeight = (int)(display->height / display->pixelScale);

        maxRegion.setPosAndSize(0, 0, scaledWidth, scaledHeight);
        region.set(&maxRegion);
        if (display->lineBufferHeight == 0 || display->lineBufferHeight > scaledHeight) display->lineBufferHeight = scaledHeight;
        else if (display->lineBufferHeight < 0) display->lineBufferHeight = 1;
        _bufferHeight = display->lineBufferHeight;
        _bufferWidth = scaledWidth;
        _data[0].pixels = new color888[_bufferWidth * _bufferHeight];
        _data[1].pixels = new color888[_bufferWidth * _bufferHeight];
        _yOffset = 0;
    }

    LineBuffer::~LineBuffer() {
        delete[] _data[0].pixels;
        delete[] _data[1].pixels;
    }

    void LineBuffer::begin(ClipRect* targetRect) {
        // Ensure region is within display area
        region.set(
            max(maxRegion.x, targetRect->x),
            max(maxRegion.y, targetRect->y),
            min(maxRegion.x2, targetRect->x2),
            min(maxRegion.y2, targetRect->y2)
        );
        resetRegion();
        scaledRegion.setPosAndSize(
            region.x * display->pixelScale,
            region.y * display->pixelScale,
            region.width * display->pixelScale,
            region.height * display->pixelScale
        );
        display->beginDrawing(scaledRegion);
    }

    void LineBuffer::end() {
        display->endDrawing();
    }

    void LineBuffer::resetRegion() {
        _data[_frontIndex].rect.set(
            region.x,
            region.y,
            region.x2,
            region.y + _bufferHeight - 1
        );
        _y = region.y;
        _yOffset = 0;
    }

    void LineBuffer::flip(bool flush) {
        // Advance a line
        _y++;
        _yOffset += _bufferWidth;

        // If we have filled the buffer or reached the end of the region, flip and push
        if ((_y > _data[_frontIndex].rect.y2) || (_y > region.y2) || flush) {
            // Flip the buffers
            _backIndex = _frontIndex;
            _frontIndex ^= 1;
            // Update the back buffer region
            _data[_backIndex].rect.y2 = _y - 1;
            _data[_backIndex].rect.height = _y - _data[_backIndex].rect.y;
            // Set the new front buffer region
            if (_y > region.y2) _y = region.y;
            _data[_frontIndex].rect.set(
                _data[_backIndex].rect.x,
                _y,
                _data[_backIndex].rect.x2,
                _y + _bufferHeight - 1
            );
            _yOffset = 0;

            // Flush to the hardware from the back buffer
            display->draw(_data[_backIndex], _data[_backIndex].rect.width);
        }
    }

} // namespace craft