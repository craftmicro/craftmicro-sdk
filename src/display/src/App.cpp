#include "../App.h"

namespace craft {

    App::App(Display* display) {
        if (display) {
            this->display = display;
            this->display->_mount();
        }
        this->_init();
    }

    void App::_init() {
        this->lastMicros = micros();

        this->stage = new Stage();
        this->stage->width(this->display->_rect.width);
        this->stage->height(this->display->_rect.height);
        this->messenger = new Messenger();
        this->tweens = new Tween();
        this->input = new Input(this->messenger);
    }

    App::~App() {
        delete this->input;
        delete this->tweens;
        delete this->messenger;
        delete this->stage;
    }

    void App::setRenderFPS(uint16_t fps) {
        if (fps == 0) _renderDeltaMicrosMax = 0;
        else _renderDeltaMicrosMax = (1 / (float_t)fps) * 1000000;
    }

    void App::update() {
        // Update timer
        thisMicros = micros();
        deltaMicros = thisMicros - lastMicros;
        deltaSecs = deltaMicros * 0.000001;

        // Update input and messenger as often as possible
        input->update(deltaSecs);
        messenger->update(deltaSecs);
        stage->update(deltaSecs);

        // User update functions
        messenger->sendMessage(Event::update_all);

        // Perform the fps limited functions, which include
        // tweening and rendering.
        renderDeltaMicros += deltaMicros;
        if (renderDeltaMicros >= _renderDeltaMicrosMax) {
            renderDeltaSecs = renderDeltaMicros * 0.000001;

            // Update tweens
            tweens->update(renderDeltaSecs);

            // Update stage
            stage->update(renderDeltaSecs, true);

            // Render the stage
            stage->render(display);

            // User render functions
            messenger->sendMessage(Event::update_render);

            renderDeltaMicros -= _renderDeltaMicrosMax;
        }

        // Update timer. We do this last because someone might want to know
        // value of lastMicros and thisMicros during update.
        lastMicros = thisMicros;
    }

    void App::serialBegin(bool waitUntilReady) {
        // Initialise the serial for debugging info
        Serial.begin(9600);
        if (waitUntilReady) {
            for (uint8_t i = 0; i < 20; i++) {
                delay(100);
                if (Serial) break;
            }
        }
    }

} // namespace craft