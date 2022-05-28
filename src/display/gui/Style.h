#pragma once

#include "Common.h"
#include "fonts/OpenSans11.h"
#include "fonts/OpenSansExtraBold11.h"

namespace craft {

    /**
     * Styles for a text element
     */
    class TextStyle {
        color888 color = 0xecf0f1;
        color888 inactiveColor = 0x95a5a6;
    };

    /**
     * Styles for a panel element
     */
    class PanelStyle {
        color888 backgroundColor = 0x1c1d1e;
        color888 borderColor = 0x121314;
        color888 highlightColor = 0x202122;
    };

    /**
     * Styles for GUI
     */
    class Style {
    public:
        /**
         * Screen color
         */
        color888 screenColor = 0x151617;

        /**
         * Panel colors
         */
        color888 panelBackgroundColor[2] = { 0x1c1d1e, 0x222324 };
        color888 panelBorderColor[2] = { 0x121314, 0x18191a };
        color888 panelHighlightColor[2] = { 0x202122, 0x262728 };

        /**
         * Fonts
         */
        packedbdf_t* font = (packedbdf_t*)&OpenSans11;
        packedbdf_t* labelFont = (packedbdf_t*)&OpenSans11;

        /**
         * Text colors
         */
        color888 textColor = 0xecf0f1;
        color888 textInactiveColor = 0x95a5a6;

        color888 labelColor = 0x7f8c8d;
        color888 labelInactiveColor = 0x454646;

        /**
         * Icon bitmaps
         */
        const TilemapData* controls = nullptr; //&guiControls;
        const TilemapData* icons = nullptr; //&guiIcons;

        /**
         * Icon colors
         */
        color888 iconColor = 0xecf0f1;
        color888 badgeTextColor = 0xecf0f1;
        color888 badgeColor = 0xe94b35;
    };

} // namespace craft
