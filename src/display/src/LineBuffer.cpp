#include "../LineBuffer.h"

namespace craft {

    LineBuffer::LineBuffer( Display* display, int bufferHeight ) {
        _display = display;
        rect.setPosAndSize( 0, 0, _display->width(), _display->height() );
        _region.set( &rect );
        if ( bufferHeight == 0 || bufferHeight > _display->height() ) bufferHeight = _display->height();
        else if ( bufferHeight < 0 ) bufferHeight = 1;
        _bufferHeight = bufferHeight;
        _bufferWidth = _display->width();
        _data[0].pixels = new color888[_bufferWidth * _bufferHeight];
        _data[1].pixels = new color888[_bufferWidth * _bufferHeight];
        _yOffset = 0;
    }

    LineBuffer::~LineBuffer() {
        delete[] _data[0].pixels;
        delete[] _data[1].pixels;
    }

    void LineBuffer::setRegion( ClipRect* rect ) {
        // Ensure region is within display area
        _region.set(
            max( 0, rect->x ),
            max( 0, rect->y ),
            min( _bufferWidth, rect->x2 ),
            min( _bufferWidth, rect->y2 )
        );
        resetRegion();
    }

    void LineBuffer::resetRegion() {
        _data[_frontIndex].rect.set(
            _region.x,
            _region.y,
            _region.x2,
            _region.y + _bufferHeight - 1
        );
        _y = _region.y;
        _yOffset = 0;
    }

    void LineBuffer::flip( bool flush ) {
        // Advance a line
        _y++;
        _yOffset += _bufferWidth;

        // If we have filled the buffer or reached the end of the region, flip and push
        if ((_y > _data[_frontIndex].rect.y2) || (_y > _region.y2) || flush) {
            // Filp the buffers
            _backIndex = _frontIndex;
            _frontIndex ^= 1;
            // Update the back buffer region
            _data[_backIndex].rect.y2 = _y - 1;
            _data[_backIndex].rect.height = _y - _data[_backIndex].rect.y;
            // Set the new front buffer region
            if (_y > _region.y2) _y = _region.y;
            _data[_frontIndex].rect.set(
                _data[_backIndex].rect.x,
                _y,
                _data[_backIndex].rect.x2,
                _y + _bufferHeight - 1
            );
            _yOffset = 0;
            // Flush to the hardware from the back buffer
            while ( !_display->ready ) yield();
            _display->draw( _data[_backIndex] );
        }
    }

} // namespace