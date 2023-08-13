#pragma once

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
        static Window* Create(const char* title, const char* acronym = nullptr, int icon = -1);

        /**
         * @brief Construct a new Window object
         */
        Window();

        /**
         * Reset the object back to default settings
         */
        void reset();

        /**
         * @brief Arrange children to fit this object
         */
        void arrange() override;

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

    };

} // namespace craft
