#include "../Gui.h"

namespace craft {

    Gui::Gui(Style* style) {
        type = WidgetType::Gui;
        menu = new Menu();
        addChild(menu);
        _bg = Box::Create();
        addChild(_bg);
        this->style(style, true);
    }

    void Gui::_added(DisplayObject* child) {
        Widget::_added(child);

        // If the child is a window...
        if (child->type == WidgetType::Window) {
            Window* w = (Window*)child;
            // Add it to the menu
            menu->add(w->title(), w->acronym(), w->icon, Event::gui_menuitem_selected, (void*)child);
            // See if it should be default
            if (!window) window = w;
        }
    }

    void Gui::_removed(DisplayObject* child) {
        Widget::_removed(child);

        // if the child is a window...
        if (child->type == WidgetType::Window) {
            // Remove it from the menu
            menu->remove((void*)child);
            // See if it's default
            if (window == child) window = nullptr;
        }
    }

    void Gui::style(Style* style, bool setForChildren) {
        Widget::style(style, setForChildren);
        if (_style) _bg->color = _style->panelBackgroundColor[1];
        // TODO: We only need to arrange if the style is able to affect layout. This
        // could bne teh case if the menu width is based on font size. At the moment
        // this is not the case, but it is planned.
        //needsArrange = true;
    }

    void Gui::arrange() {
        Serial.println("Gui::arrange");
        // Display menu only if it has items
        if (!menu->isEmpty()) {
            menu->visible(true);
            // TODO: Work out menu width based on font size
            menu->width(40);
            menu->height(height());
            if (window) {
                window->position(menu->width(), 0);
                window->width(width() - menu->width());
                window->height(height());
            }
            _bg->position(menu->width(), 0);
            _bg->width(width() - menu->width());
            _bg->height(height());
        }
        else {
            menu->visible(false);
            if (window) {
                window->position(0, 0);
                window->width(width());
                window->height(height());
            }
            _bg->width(width());
            _bg->height(height());
        }
    }

} // namespace craft