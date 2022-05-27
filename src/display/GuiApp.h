#pragma once

#include "display/App.h"
#include "display/PackedBDF.h"
#include "display/gui/Style.h"
#include "display/gui/Window.h"

namespace craft {

    /**
     * Intention:
     *
     * Window:
     *      Icon
     *      Name
     *      Acronym
     *      Content (children)
     *          Child panels are added an item to the menu automatically
     *          Child content displays in the content area
     */
    class GuiApp : public App {
    public:
        /**
         * @brief Construct a new Gui App object with display adapter object
         *
         * @param display           A Display instance for the hardware display being used.
         * @param style             The style object to use
         * @param title             A title for the application (displayed in main window)
         * @param acronym           A short acronym when the full title cannot be displayed. Max 4 characters.
         * @param icon              Index of the icon (0 for no icon)
         * @param bufferHeight      The height of the line buffer, in lines. Default = 1. Full framebuffer = 0.
         */
        GuiApp(Display* display, Style* style, char* title, char* acronym = nullptr, int icon = 0, int bufferHeight = 1);

        /**
         * Destructor
         **/
        ~GuiApp() {}

        /**
         * @brief Set the style object for the GUI app
         * The style of each GUI object can also be set independently. For example
         * `app->window->style( myStyle );` or `app->window->getChild( VOLUME_SLIDER )->style( myStyle );`
         * @param style The style object
         */
        void style(Style* style);

        /**
         * @brief Return the stype of the GUI app
         * @return Style* The style object
         */
        Style* style() {
            if (!window) return nullptr;
            Style* s = ((Widget*)window)->style();
            return s;
        }

        /**
         * @brief The base window
         */
        Window* window = nullptr;

    };

} // namespace craft
