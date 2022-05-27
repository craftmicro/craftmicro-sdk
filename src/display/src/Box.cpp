#include "../Box.h"

namespace craft {

    Box* Box::Create() {
        return MemoryPool<Box>::Create();
    }

    Box* Box::Create(int16_t x, int16_t y, int16_t w, int16_t h) {
        Box* box = MemoryPool<Box>::Create();
        box->set(x, y, w, h);
        return box;
    }

    Box* Box::Create(ClipRect* rect) {
        Box* box = MemoryPool<Box>::Create();
        box->set(rect->x, rect->y, rect->width, rect->height);
        return box;
    }

    Box::Box() {
        borders = new Borders();
    }

    Box::~Box() {
        delete borders;
        if (gradient) delete gradient;
    }

    void Box::reset() {
        DisplayObject::reset();
    }

    void Box::set(int16_t x, int16_t y, int16_t w, int16_t h) {
        this->x(x);
        this->y(y);
        this->width(w);
        this->height(h);
        dirty();
    }

    void Box::beginRender(ClipRect* updateArea) {
        DisplayObject::beginRender(updateArea);
        if (gradient) gradient->beginRender(renderBounds);
    }

    void Box::beginLine(int16_t ry) {
        if (gradient) gradient->beginLine(ry);
    }

    void Box::calcPixel(int16_t rx, int16_t ry) {
        if (gradient) {
            gradient->calcPixel(rx, ry);
            _ra = gradient->ra;
            _rc = gradient->rc;
        }
        else {
            _ra = 1;
            _rc = color;
        }
    }

    void Box::skipPixel(int16_t rx, int16_t ry) {
        if (gradient) gradient->skipPixel(rx, ry);
    }

} // namespace craft