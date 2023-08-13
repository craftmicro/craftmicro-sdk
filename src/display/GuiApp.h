#pragma once

#include "display/App.h"
#include "display/gui/Gui.h"

namespace craft {

    /**
     * A shortcut for creating an app with a gui widget
     */
    class GuiApp : public App {
    public:
        /**
         * @brief Construct a new Gui App object with display adapter object
         *
         * @param display           A Display instance for the hardware display being used.
         * @param style             The style object to use
         * @param bufferHeight      The height of the line buffer, in lines. Default = 1. Full framebuffer = 0.
         */
        GuiApp(Display* display, Style* style, int bufferHeight = 1);

        /**
         * Destructor
         **/
        ~GuiApp();

        /**
         * @brief Set the style object for the GUI app
         * The style of each GUI object can also be set independently.
         * @param style The style object
         */
        void style(Style* style);

        /**
         * @brief Return the stype of the GUI app
         * @return Style* The style object
         */
        Style* style();

        /**
         * @brief The base gui
         */
        Gui* gui = nullptr;
    };

} // namespace craft
