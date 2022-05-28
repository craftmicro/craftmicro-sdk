#pragma once

#include "display/gui/Widget.h"

namespace craft {

    class MenuItem : public LinkedList<MenuItem>, public MemoryPool<MenuItem> {
    public:
        char* title = nullptr;
        char* acronym = nullptr;
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
         */
        void add(char* title, char* acronym, int icon, uint32_t event, void* eventData);

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
    };

} // namespace craft
