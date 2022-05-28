#include "../Window.h"
#include "display/LinearGradient.h"

namespace craft {

    Window* Window::pool = nullptr;

    Window::Window() {
        type = WidgetType::WTWindow;
        _bg = Box::Create();
        addChild(_bg);
    }

    Window* Window::Create() {
        return MemoryPool<Window>::Create();
    }

    Window* Window::Create(char* title, char* acronym, int icon) {
        Window* window = Window::Create();
        window->title(title, acronym);
        window->icon = icon;
        window->menu = Menu::Create();
        window->addChild(window->menu);
        return window;
    }

    void Window::reset() {
        Widget::reset();
        if (menu) {
            menu->recycle();
            menu = nullptr;
        }
    }

    void Window::_added(DisplayObject* child) {
        Widget::_added(child);

        // if the child is a window...
        if (child->type == WidgetType::WTWindow) {
            Window* w = (Window*)child;
            // Add it to the menu
            menu->add(
                w->_title,
                w->_acronym,
                w->icon,
                Event::gui_menuitem_selected,
                (void*)w
            );
        }
    }

    void Window::_removed(DisplayObject* child) {
        Widget::_removed(child);
        // if the child is a window...
        if (child->type == WidgetType::WTWindow) {
            Window* w = (Window*)child;
            // Remove it from the menu
            menu->remove(w);
        }
    }

    void Window::width(float_t w) {
        Widget::width(w);
        _bg->width(w);
    }

    void Window::height(float_t h) {
        Widget::height(h);
        _bg->height(h);
    }

    void Window::style(Style* style, bool setForChildren) {
        Widget::style(style, setForChildren);
        if (_bg->gradient) _bg->gradient->recycle();
        LinearGradient* g = LinearGradient::Create(2);
        g->stop(0, lighten(style->panelBackgroundColor[0], 0.1), 1.0, 0.0)->stop(1, style->panelBackgroundColor[0], 1.0, 0.35);
        _bg->gradient = g;
        _bg->dirty();
        _needsArrange = true;
    }

    void Window::arrange() {
        if (_parent) {
            if (_parent->type >= WidgetType::WTMin && _parent->type <= WidgetType::WTMax) {
                // If the parent is a widget, get the available area
                // _parent->contentRect();
            }
        }
        if (_bg->gradient) _bg->gradient->position(0, 0, 0, height());
        Widget::arrange();
    }

} // namespace craft