#include "../Window.h"

namespace craft {

    Window* Window::pool = nullptr;

    Window::Window() {
        type = WidgetType::Window;
    }

    Window* Window::Create() {
        return MemoryPool<Window>::Create();
    }

    Window* Window::Create(const char* title, const char* acronym, int icon) {
        Window* window = Window::Create();
        window->title(title, acronym);
        window->icon = icon;
        return window;
    }

    void Window::reset() {
        Widget::reset();
    }

    void Window::_added(DisplayObject* child) {
        Widget::_added(child);

        // if the child is a window...
        if (child->type == WidgetType::Window) {
            //Window* w = (Window*)child;
            // Add it to the menu
            // TODO
        }
    }

    void Window::_removed(DisplayObject* child) {
        Widget::_removed(child);
        // if the child is a window...
        if (child->type == WidgetType::Window) {
            //Window* w = (Window*)child;
            // Remove it from the menu
            // TODO
        }
    }

    void Window::arrange() {
        if (_parent) {
            if (_parent->type >= WidgetType::Min && _parent->type <= WidgetType::Max) {
                // If the parent is a widget, get the available area
                // _parent->contentRect();
            }
        }

        Widget::arrange();
    }

} // namespace craft