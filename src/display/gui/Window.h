#pragma once
#ifndef _CRAFTMICRO_GUIWINDOWH_
#define _CRAFTMICRO_GUIWINDOWH_ 1

#include "display/gui/Widget.h"
#include "display/gui/Menu.h"
#include "display/Box.h"

namespace craft {

    /**
     * A GUI window
     */
    class Window : public Widget, public MemoryPool<Window> {
    private:
        /**
         * Create a new object or take one from the pool
         * @return The new or recycled object
         */
        static Window* Create();

    public:
        /**
         * Memory pool of recycled objects
         */
        static Window* pool;

        /**
         * @brief Create a new object or take one from the pool
         *
         * @param title The window title
         * @param acronym A short acronym when the full title cannot be displayed. Max 4 characters.
         * @param icon The icon index (-1 is no icon)
         * @return Window* The new or recycled object
         */
        static Window* Create( char* title, char* acronym = nullptr, int icon = -1 );

        /**
         * @brief Construct a new Window object
         */
        Window();

        /**
         * Reset the object back to default settings
         */
        void reset();

        /**
         * @brief The window menu
         * Child windows are automatically added to this menu. Custom
         * items may also be added.
         */
        Menu* menu = nullptr;

        /**
         * @brief Set the window style
         * @param style The style to set
         * @param setForChildren If true, will also set the style (recursively) for all children
         */
        void style( Style* style, bool setForChildren = true ) override;

        /**
         * @brief Set the window width
         *
         * @param w The window width
         */
        void width( float_t w ) override;

        /**
         * @brief Return the window width
         *
         * @return float_t The window width
         */
        float_t width() override { return Widget::width(); }

        /**
         * @brief Set the window height
         *
         * @param h The window height
         */
        void height( float_t h ) override;

        /**
         * @brief Return the window height
         *
         * @return float_t The window height
         */
        float_t height() override { return Widget::height(); }

        /**
         * @brief Arrange children to fit thie object
         */
        void arrange() override;

    protected:
        /**
         * @brief Called when a display object is added to this object
         * Ensure child GUI widgets are processed correctly
         * @param child The object being added
         */
        void _added( DisplayObject* child ) override;

        /**
         * @brief Called when a display object is removed from this object
         * Ensure child GUI widgets are processed correctly
         * @param child The object being removed
         */
        void _removed( DisplayObject* child ) override;

        /**
         * @brief The window background
         */
        Box* _bg = nullptr;

    };

} // namespace

#endif