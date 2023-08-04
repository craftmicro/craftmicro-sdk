#include "../Shape.h"

namespace craft {

    Shape* Shape::Create(Point** points, uint16_t len) {
        Shape* shape = MemoryPool<Shape>::Create();
        shape->set(points, len);
        return shape;
    }

    void Shape::reset() {
        _points = 0;
        _pointsLen = 0;

        DisplayObject::reset();
    }

    void Shape::set(Point** points, uint16_t len) {

        dirty();
    }

    void Shape::update(float_t dt) {
        // Update self

        // Update children
        DisplayObject::update(dt);
    }

    void Shape::transform(Matrix* t) {
        _localBounds->clear();
        uint16_t l = _pointsLen;
        Point* p;
        while (l--) {
            p = _points[l];
            _localBounds->set(
                min(_localBounds->p1.x, p->x),
                min(_localBounds->p1.y, p->y),
                max(_localBounds->p2.x, p->x),
                max(_localBounds->p2.y, p->y)
            );
        }
        DisplayObject::transform(t);
    }

    void Shape::beginLine(int16_t ry) {

    }

    void Shape::calcPixel(int16_t rx, int16_t ry) {
        _ra = 1;
        _rc = color;
    }

} // namespace craft