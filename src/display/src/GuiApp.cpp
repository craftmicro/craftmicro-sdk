#include "../GuiApp.h"

namespace craft {

    GuiApp::GuiApp(Display* display, Style* style, char* title, char* acronym, int icon, int bufferHeight) : App(display, bufferHeight) {
        serialBegin(true);

        window = Window::Create(title, acronym, icon);
        window->width(display->width());
        window->height(display->height());
        window->style(style);
        stage->addChild(window);
        window->arrange();
        stage->backgroundColor(style->screenColor);
    }

    void GuiApp::style(Style* style) {
        window->style(style, true);
    }

} // namespace craft
