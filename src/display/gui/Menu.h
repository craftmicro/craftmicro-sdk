#pragma once

#include "display/gui/Widget.h"
#include "display/Box.h"

namespace craft {

    class MenuItem : public LinkedList<MenuItem>, public MemoryPool<MenuItem> {
    public:
        const char* title = nullptr;
        const char* acronym = nullptr;
        int icon = 0;
        uint32_t event = 0;
        void* eventData = nullptr;
    };

    /**
     * A GUI menu
     */
    class Menu : public Widget, public MemoryPool<Menu> {
    public:
        /**
         * @brief Construct a new Menu object
         */
        Menu();

        /**
         * Reset the object back to default settings
         */
        void reset();

        /**
         * @brief Add a user-defined menu item
         *
         * @param title The title to display in the menu
         * @param acronym A shorter acronym to display if the title does not fit
         * @param icon The index of the icon (0 = no icon). @see style->icons
         * @param event The event to dispatch when this menu item is selected
         * @param eventData User data that can be stored against the event
         */
        void add(const char* title, const char* acronym, int icon, uint32_t event, void* eventData);

        /**
         * @brief Remove a menu item by title
         * @param title The title
         */
        void remove(char* title);

        /**
         * @brief Remove a menu item by its position in the menu
         * @param title The title
         */
        void remove(int index);

        /**
         * @brief Remove a menu item based on the event data pointer
         * @param data The data pointer
         */
        void remove(void* eventData);

        /**
         * @brief Remove all menu items from the menu
         */
        void clear();

        /**
         * @brief Check if there are any menu items
         */
        boolean isEmpty();

        /**
         * @brief Set the menu width
         *
         * @param w The menu width
         */
        void width(float_t w) override;

        /**
         * @brief Return the window width
         *
         * @return float_t The window width
         */
        float_t width() override { return Widget::width(); }

        /**
         * @brief Set the menu height
         *
         * @param h The menu height
         */
        void height(float_t h) override;

        /**
         * @brief Return the window height
         *
         * @return float_t The window height
         */
        float_t height() override { return Widget::height(); }

        /**
         * @brief Set style
         *
         * @param style The style to set
         * @param setForChildren If true, will also set the style (recursively) for all children
         */
        void style(Style* style, bool setForChildren) override;

    protected:
        void add(MenuItem* item);
        void remove(MenuItem* item);

        /**
         * @brief The items in the menu
         */
        MenuItem* _items = nullptr;

        /**
         * @brief The currently active item
         */
        MenuItem* _activeItem = nullptr;

        /**
         * @brief The menu background
         */
        Box* _bg = nullptr;
    };

} // namespace craft
