#include "../Pixel.h"
#include "graphics/Color8888.h"

namespace craft {

    PixelStack::PixelStack() {
        this->capacity = 16;
        c = new color888[capacity];
        a = new float_t[capacity];
    }

    PixelStack::~PixelStack() {
        delete[] c;
        delete[] a;
    }

    bool PixelStack::push(color888 color, float_t alpha) {
        if (length >= capacity) {
            delete[] c;
            delete[] a;
            capacity += 16;
            c = new color888[capacity];
            a = new float_t[capacity];
        }
        c[length] = color;
        a[length] = alpha;
        length++;
        if (alpha == 1.0f) {
            solid = true;
        }
        return solid;
    }

    color888 PixelStack::flatten(color888 base = 0) {
        if (solid) {
            base = c[--length];
        }
        while (length--) {
            base = blend8888(base, c[length], a[length]);
        }
        length = 0;
        solid = false;
        return base;
    }

} // namespace craft
