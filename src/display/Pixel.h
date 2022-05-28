#pragma once

#include "Common.h"
#include "graphics/Color.h"
#include "utils/LinkedList.h"
#include "utils/MemoryPool.h"

namespace craft {

    /**
     * Stacked pixel class for blending and masking pixels during rendering (sued by Stage)
     */
    class Pixel : public LinkedList<Pixel>, public MemoryPool<Pixel> {
    public:
        color888 c = 0;
        float_t a = 0.0;
        boolean m = false;

        /**
         * @brief Recycle the pixel list
         */
        void recycle() override;

        /**
         * Create a new object or take one from the pool
         * @return The new or recycled object
         */
        static Pixel* Create(color888 color, float_t alpha, boolean mask);

        /**
         * @brief Flattens pixel list
         * Will flatten the pixels by blending them downward, respecting masks.
         * Will also recycle the pixels, results in an empty list
         * @param c
         * @return color8888
         */
        color8888 flatten();

    protected:
        float_t _flattenMask();
    };

} // namespace craft
