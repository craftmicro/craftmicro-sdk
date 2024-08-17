#pragma once

#include "Common.h"
#include "graphics/Color.h"
#include "utils/LinkedList.h"
#include "utils/MemoryPool.h"

namespace craft {

    /**
     * Stacked pixel class for blending and masking pixels during rendering (used by Stage)
     */
    class PixelStack {
    public:
        uint16_t length = 0;
        uint16_t capacity = 0;
        color888* c;
        float_t* a;
        bool solid = false;

        PixelStack();

        ~PixelStack();

        bool push(color888 color, float_t alpha);

        color888 flatten(color888 base);
    };

} // namespace craft
