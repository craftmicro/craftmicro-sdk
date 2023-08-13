#pragma once

#include "Common.h"

namespace craft {

    /**
     * Styles for GUI
     */
    class Style {
    public:
        /**
         * Screen color
         */
        color8888 screenColor = 0xff151617;

        /**
         * Panel colors
         */
        color8888 panelBackgroundColor[3] = {0xff151617, 0xff1C1D1E, 0xff222324};

        /**
         * Fonts
         */
        const packedbdf_t* font = nullptr;
        const packedbdf_t* labelFont = nullptr;

        /**
         * Text colors
         */
        color8888 textColor = 0xffecf0f1;
        color8888 textActiveColor = 0xff08a5ff;
        float_t textInactiveAlpha = 0.1;

        color8888 labelColor = 0xffecf0f1;
        color8888 labelActiveColor = 0xffff8c4c;
        float_t labelInactiveAlpha = 0.1;

        /**
         * Feature colours
         */
        float_t featureHue[3] = {0.0, 1.0, 0.5}; // min, max, start
        uint8_t featureHueSteps = 8;
        float_t featureSaturation = 0.5;
        float_t featureLightness = 0.5;

        /**
         * Icon bitmaps
         */
        const TilemapData* controls = nullptr;
        const TilemapData* icons = nullptr;

        /**
         * Badge
         */
        color8888 badgeTextColor = 0xffecf0f1;
        color8888 badgeColor = 0xffe94b35;
    };

} // namespace craft
