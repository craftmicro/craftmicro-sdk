#include "../Pixel.h"
#include "graphics/Color8888.h"

namespace craft {

    Pixel* Pixel::Create( color888 color, float_t alpha, boolean mask ) {
        Pixel* p = MemoryPool<Pixel>::Create();
        p->c = color;
        p->a = alpha;
        p->m = mask;
        return p;
    }

    void Pixel::recycle() {
        if ( next() ) next()->recycle();
        _next = nullptr;
        _prev = nullptr;
        MemoryPool<Pixel>::recycle();
    }

    color8888 Pixel::flatten() {
        // See if there is a child
        Pixel* p = next();
        if ( p ) {
            // If the child is a mask, calculate the alpha and apply it
            if ( p->m ) {
                float_t ma = p->_flattenMask();
                a *= ma;
                if ( a == 0 ) return 0;
            }
            // If the child is not a mask, blend it down
            else {
                p->flatten();
                return blend8888( c, p->c, p->a );
            }
        }

        // Return own color
        return  ( (uint8_t)( a * 255.0 ) << 24 ) | ( c & 0xffffff );
    }

    float_t Pixel::_flattenMask() {
        return a;
    }

} // namespace
