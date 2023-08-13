#pragma once

#include "display/gui/Widget.h"
#include "display/gui/Menu.h"
#include "display/gui/Window.h"
#include "display/Box.h"

namespace craft {

    /**
     * A GUI layout containing a menu
     * The only children that may be added are windows
     */
    class Gui : public Widget {
    public:
        /**
         * @brief Construct a new Window object
         *
         * @param style The style object to use
         */
        Gui(Style* style);

        /**
         * @brief Set the gui style
         * @param style The style to set
         * @param setForChildren If true, will also set the style (recursively) for all children
         */
        void style(Style* style, bool setForChildren = true) override;

        /**
         * @brief Arrange children to fit this object
         */
        void arrange() override;

        /**
         * @brief The menu
         */
        Menu* menu = nullptr;

        /**
         * @brief The active window (could be a nested window at any depth)
         */
        Window* window = nullptr;

    protected:
        /**
         * @brief Called when a display object is added to this object
         * Ensure child GUI widgets are processed correctly
         * @param child The object being added
         */
        void _added(DisplayObject* child) override;

        /**
         * @brief Called when a display object is removed from this object
         * Ensure child GUI widgets are processed correctly
         * @param child The object being removed
         */
        void _removed(DisplayObject* child) override;

        /**
         * @brief The background behind the window area
         */
        Box* _bg = nullptr;

    };

} // namespace craft
