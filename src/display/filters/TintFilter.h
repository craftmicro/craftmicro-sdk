#pragma once

#include "Filter.h"

namespace craft {

    /**
     * Tint filter
     */
    class TintFilter : public Filter, public MemoryPool<Filter> {
    public:
        /**
         * @brief Construct a new Tint Filter object
         *
         * @param color The color to tint with
         * @param amount The amount to tint by
         */
        TintFilter(color888 color, float_t amount) {
            this->color = color;
            _a = alphaClamp(amount);
        }

        /**
         * @brief Apply the filter to the specified pixel
         *
         * @param rx The current X position in local coordinates
         * @param ry The current Y position in local coordinates
         * @param a (in/out) The alpha value of the pixel being filtered
         * @param c (in/out) The color value of the pixel being filtered
         */
        void filterPixel(int16_t rx, int16_t ry, float_t& a, color888& c) {
            c = tint(c, color, _a);
        }

        /**
         * @brief The color to tint
         *
         */
        color888 color;

        /**
         * @brief Set the amount of tint (0.0 - 1,.0)
         *
         * @param value The amount
         */
        void amount(float_t value) {
            _a = alphaClamp(value);
        }

        /**
         * @brief Get the amount
         *
         * @return float_t
         */
        float_t amount() { return _a; }

    protected:

        float_t _a;

    };



} // namespace craft
