#include "../Menu.h"

namespace craft {

    Menu::Menu() {
        type = WidgetType::Menu;
        _bg = Box::Create();
        addChild(_bg);
    }

    void Menu::reset() {
        Widget::reset();
        clear();
    }

    void Menu::clear() {
        MenuItem* i = _items;
        while (i) {
            MenuItem* n = i->next();
            i->remove();
            i->recycle();
            i = n;
        }
        _items = nullptr;
    }

    boolean Menu::isEmpty() {
        return _items == nullptr;
    }

    void Menu::add(const char* title, const char* acronym, int icon, uint32_t event, void* eventData) {
        MenuItem* item = MenuItem::Create();
        item->title = title;
        item->acronym = acronym;
        item->icon = icon;
        item->event = event;
        item->eventData = eventData;

        add(item);
    }

    void Menu::add(MenuItem* item) {
        if (_items) _items->add(item);
        else _items = item;
    }

    void Menu::remove(char* title) {
        MenuItem* i = _items;
        while (i) {
            if (strcmp((const char*)i->title, (const char*)title) == 0) {
                MenuItem* n = i->next();
                if (_items == i) _items = n;
                i->remove();
                i->recycle();
                i = n;
            }
            else {
                i = i->next();
            }
        }
    }

    void Menu::remove(int index) {
        MenuItem* i = _items;
        int idx = 0;
        while (i) {
            if (idx == index) {
                MenuItem* n = i->next();
                if (_items == i) _items = n;
                i->remove();
                i->recycle();
                return;
            }
            idx++;
            i = i->next();
        }
    }

    void Menu::remove(void* eventData) {
        MenuItem* i = _items;
        while (i) {
            if (i->eventData == eventData) {
                MenuItem* n = i->next();
                if (_items == i) _items = n;
                i->remove();
                i->recycle();
                i = n;
            }
            else {
                i = i->next();
            }
        }
    }

    void Menu::width(float_t w) {
        Widget::width(w);
        _bg->width(w);
    }

    void Menu::height(float_t h) {
        Widget::height(h);
        _bg->height(h);
    }

    void Menu::style(Style* style, bool setForChildren) {
        Widget::style(style, setForChildren);
        _bg->color = _style->panelBackgroundColor[0];
    }

} // namespace craft
