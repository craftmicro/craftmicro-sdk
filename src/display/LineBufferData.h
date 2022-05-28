#pragma once

#include "Common.h"
#include "geom/ClipRect.h"

namespace craft {

    /**
     * Holds the pixel data and state of the line buffer. There
     * are two of these - one for the front and one for the back.
     */
    typedef struct {

        // The pixel data as 32bit words. There is a storage overhead of 1 byte
        // per pixel, but this is made up for by the faster math this allows.
        uint32_t* pixels;

        // The display area covered by the buffer
        ClipRect rect;

    } LineBufferData;

} // namespace craft
