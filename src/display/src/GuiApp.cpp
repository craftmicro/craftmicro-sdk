#include "../GuiApp.h"

namespace craft {

    GuiApp::GuiApp(Display* display, Style* style, int bufferHeight) : App(display, bufferHeight) {
        gui = new Gui(style);
        gui->width(display->width());
        gui->height(display->height());
        stage->addChild(gui);

        if (style) stage->backgroundColor(style->screenColor);
    }

    GuiApp::~GuiApp() {
        stage->removeChild(gui);
        delete gui;
    }

    void GuiApp::style(Style* style) {
        if (style) stage->backgroundColor(style->screenColor);
        gui->style(style, true);
    }

    Style* GuiApp::style() {
        Style* s = ((Widget*)gui)->style();
        return s;
    }

} // namespace craft
