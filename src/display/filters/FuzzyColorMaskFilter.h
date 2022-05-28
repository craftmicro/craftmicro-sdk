#pragma once

#include "Filter.h"

namespace craft {

    /**
     * Fuzzy color-mask filter
     */
    class FuzzyColorMaskFilter : public Filter, public MemoryPool<Filter> {
    public:
        /**
         * @brief Construct a new Fuzzy Color Mask Filter object
         *
         * @param color The color to tint with
         * @param threshhold The threshhold for matching thecolor (0.0 = exact, 1.0 = maximum variation)
         */
        FuzzyColorMaskFilter(color8888 color, float_t threshhold) {
            _r = red(color);
            _g = green(color);
            _b = blue(color);
            _t = alphaClamp(threshhold);
        }

        /**
         * @brief Apply the filter to the specified pixel
         *
         * @param rx The current X position in local coordinates
         * @param ry The current Y position in local coordinates
         * @param a (in/out) The alpha value of the pixel being filtered
         * @param c (in/out) The color value of the pixel being filtered
         */
        void filterPixel(int16_t rx, int16_t ry, float_t& a, color888& c) override {
            if ((diff(red(c), _r) <= _t) && (diff(green(c), _g) <= _t) && (diff(blue(c), _b) <= _t)) a = 0;
        }

        /**
         * @brief Change the mask color
         *
         * @param color The mask color
         */
        void color(color8888 color) {
            _r = red(color);
            _g = green(color);
            _b = blue(color);
        }

        /**
         * @brief Get the mask color
         *
         * @return color888 The mask color
         */
        color8888 color() {
            return to8888(_r, _g, _b);
        }

        /**
         * @brief Set the threshhold (0.0 - 1,.0)
         *
         * @param value The threshhold
         */
        void threshhold(float_t value) {
            _t = alphaClamp(value);
        }

        /**
         * @brief Get the threshhold
         *
         * @return float_t
         */
        float_t threshhold() { return _t; }

        /**
         * @brief Reset filter back to defaults
         */
        void reset() override {
            _r = 0;
            _g = 0;
            _b = 0;
            _t = 0;
        }

    protected:
        uint8_t _r;
        uint8_t _g;
        uint8_t _b;
        float_t _t;

        /**
         * @brief Calculate the different between two components
         *
         * @param v1 The first component
         * @param v2 The second component
         * @return float The difference between 0.0 and 1.0
         */
        inline float diff(uint8_t v1, uint8_t v2) {
            return abs(v1 - v2) / 255.0f;
        }
    };



} // namespace craft
