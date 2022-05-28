#include "../App.h"

namespace craft {

    App::App() {
        this->_init();
    }

    App::App(Display* display, int bufferHeight) {
        // Graphics
        this->display = display;
        this->buffer = new LineBuffer(this->display, bufferHeight);
        this->_init();
    }

    void App::_init() {
        this->lastMicros = micros();

        this->stage = new Stage();
        this->stage->width(this->display->width());
        this->stage->height(this->display->height());
        this->messenger = new Messenger();
        this->tweens = new Tween();
        this->input = new Input(this->messenger);
    }

    App::~App() {
        if (this->display) delete this->display;
        delete this->buffer;
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

        // User update functions
        messenger->sendMessage(Event::update_all);

        // Perform the fps limited functions, which include
        // tweening and rendering.
        renderDeltaMicros += deltaMicros;
        if (renderDeltaMicros >= _renderDeltaMicrosMax) {
            renderDeltaSecs = renderDeltaMicros * 0.000001;

            // Update tweens
            tweens->update(renderDeltaSecs);

            // Render the stage
            stage->render(buffer);

            // User render functions
            messenger->sendMessage(Event::update_render);

            renderDeltaMicros -= _renderDeltaMicrosMax;
        }

        // Update timer. We do this last because someone might want to know
        // value of lastMicros and thisMicros during update.
        lastMicros = thisMicros;
    }

    void App::serialBegin(boolean waitUntilReady) {
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