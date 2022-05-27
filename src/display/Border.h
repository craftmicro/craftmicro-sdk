#pragma once

#include "graphics/Color8888.h"

namespace craft {

    /**
     * Border class
     */
    class Border {

    public:

        /**
         * Constructor
         */
        Border();
        Border(float_t size, color888 color, float_t alpha);

        /**
         * @brief Set size, color and alpha in one go
         *
         * @param size The border size
         * @param color The border color
         * @param alpha The alpha
         */
        void set(float_t size, color888 color, float_t alpha);

        /**
         * Border size
         */
        float_t size = 0;

        /**
         * Border color
         */
        color888 color = 0;

        /**
         * Alpha
         */
        float_t alpha = 1.0;

    };



} // namespace craft
