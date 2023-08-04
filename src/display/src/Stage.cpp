#include "../Stage.h"

namespace craft {

    Stage::Stage() {
        _dirtyBounds = new ClipRect();
        id = 0;
    }

    Stage::~Stage() {
        delete _dirtyBounds;
    }

    void Stage::update(float_t dt) {
        // Update self

        // Update children
        DisplayObject::update(dt);
    }

    void Stage::render(LineBuffer* buffer) {
        //Serial.println("Stage::render");

        // Set stage to match display
        _localBounds->setSize(buffer->rect.width, buffer->rect.height);

        // Build display list. At the same time, determine the area of the display that is dirty
        // The display list is a list of all visible display objects (both with 'visibility' flag
        // set to true, and at least partially visible on the display) ordered from top to bottom
        // and left to right.
        if (_dirty) _dirtyBounds->set(&buffer->rect);
        else _dirtyBounds->clear();
        _displayListDepth = 0;
        _displayList = DisplayList::Create(this);
        if (_children) _traverse(buffer, _children, _dirty, _transform, _children->mask != MaskType::none);

        // Calculate the updated area of ths display
        renderBounds->set(_dirtyBounds);
        renderBounds->clip(&buffer->rect);
        //Serial.println("Render bounds");
        //Serial.printf("  %d,%d %dx%d\n", renderBounds->x, renderBounds->y, renderBounds->width, renderBounds->height);

        // TODO: Handle this. For now do nothing
        if (_displayListDepth == 0) {}
        if (renderBounds->isEmpty()) {
            _recycleList(_renderList);
            _recycleList(_displayList);
            _dirty = false;
            return;
        }

        /* Debug display list and render bounds
        Serial.println("DisplayList");
        DisplayList* debugNode = _displayList->next();
        while (debugNode) {
            Serial.printf(
                "  ID %d: %d,%d %dx%d (d=%d) (m=%d,%d)\n",
                debugNode->object->id,
                debugNode->object->globalBounds->x,
                debugNode->object->globalBounds->y,
                debugNode->object->globalBounds->width,
                debugNode->object->globalBounds->height,
                debugNode->object->depth,
                (debugNode->object->mask != MaskType::none),
                debugNode->object->_hasMask
            );
            debugNode = debugNode->next();
        }
        Serial.println("Render bounds");
        Serial.printf("  %d,%d %dx%d\n", renderBounds->x, renderBounds->y, renderBounds->width, renderBounds->height);
        */

        // Initialise the display to draw only the dirty area
        buffer->begin(renderBounds);

        Filter* filter;
        DisplayList* head = _displayList->next();
        DisplayList* next;
        _renderList = DisplayList::Create(this); // Start with just stage (this)
        float_t localx;
        float_t localy;
        for (uint16_t y = renderBounds->y; y <= renderBounds->y2; y++) {

            //Serial.printf("\nStart line y=%d\n", y);

            // For this line, grab the active display objects and add to the render list
            // in reverse order (stage at the end)
            while (head && (head->object->globalBounds->y <= y)) {
                _renderList->insertByDepth(head->object);
                _beginRender(head->object);
                head = head->next();
            }

            /* Debug render list
            if (y == renderBounds->y) {
                Serial.println("RenderList\n");
                DisplayList* list = _renderList;
                while (list) {
                    Serial.printf("  ID:%d at y=%d, x=%d (%dx%d) with d=%d is masked %d\n",
                        list->object->id,
                        int16_t(list->object->y()), int16_t(list->object->x()),
                        int16_t(list->object->width()), int16_t(list->object->height()),
                        list->object->depth,
                        list->object->_hasMask
                    );
                    list = list->next();
                }
            } */

            // For this line, remove the display objects that are complete, and set the
            // start read position for those that aren't. Skip the first one because it's
            // the stage.
            DisplayList* node = _renderList->next();
            while (node) {
                // Todo precalculate BR corner (x2 and y2) 
                if (y > node->object->globalBounds->y2) {
                    _endRender(node->object);
                    next = node->next();
                    node->remove()->recycle();
                    node = next;
                }
                else {
                    _beginLine(node->object, y);
                    node = node->next();
                }
            }

            // Step pixels in this line
            for (uint16_t x = renderBounds->x; x <= renderBounds->x2; x++) {

                // Debug the render bounds
                if (debug && ((y == renderBounds->y) || (y == renderBounds->y2) || (x == renderBounds->x) || (x == renderBounds->x2))) {
                    buffer->pixel(this->debugColor, x);
                    continue;
                }

                // Base color
                buffer->pixel(this->_backgroundColor, x);

                // Step through the objects in the display buffer
                node = _renderList->next();
                while (node) {
                    if (node->object->globalBounds->containsX(x)) {

                        // Calculate color and alpha 
                        localx = node->object->globalToLocalX(x);
                        localy = node->object->globalToLocalY(y);
                        node->object->calcPixel(localx, localy);
                        node->object->_ra *= node->object->alpha;

                        // Apply filters
                        filter = node->object->filters;
                        while (filter) {
                            filter->filterPixel(localx, localy, node->object->_ra, node->object->_rc);
                            filter = filter->next();
                        }

                        // Calculate masking
                        if (node->object->_hasMask) {
                            DisplayObject* child = node->object->firstChild();
                            float_t ma = 0;
                            while (child) {
                                if (child->mask != MaskType::none && child->visible()) {
                                    if ((child->alpha > 0) && child->globalBounds->contains(x, y)) {
                                        localx = child->globalToLocalX(x);
                                        localy = child->globalToLocalY(y);
                                        child->calcPixel(localx, localy);
                                        if (child->mask == MaskType::inverse) child->_ra = 1 - child->_ra;
                                        child->_ra *= child->alpha;
                                        ma = (1 - child->_ra) * ma + child->_ra;
                                    }
                                    else if (child->mask == MaskType::inverse) {
                                        ma = 1;
                                    }
                                }
                                child = child->next();
                            }
                            node->object->_ra *= ma;
                        }

                        // Draw to buffer
                        if (node->object->_ra == 1.0) buffer->pixel(node->object->_rc, x);
                        else if (node->object->_ra > 0) buffer->blend(node->object->_rc, alphaClamp(node->object->_ra), x);
                    }
                    node = node->next();
                }
            }

            // Flip the buffer (auto-advances to next line)
            buffer->flip();
        }
        buffer->end();

        _recycleList(_renderList);
        _renderList = 0;
        _recycleList(_displayList);
        _displayList = 0;
        _dirty = false;
    }

    void Stage::_beginRender(DisplayObject* object) {
        // Process object
        object->beginRender(renderBounds);
        // Process filters
        Filter* filter = object->filters;
        while (filter) {
            filter->beginRender(renderBounds);
            filter = filter->next();
        }
        // Process masks
        if (object->_hasMask) {
            DisplayObject* child = object->firstChild();
            while (child) {
                if (child->mask != MaskType::none && child->visible()) {
                    _beginRender(child);
                }
                child = child->next();
            }
        }
    }

    void Stage::_beginLine(DisplayObject* object, uint16_t y) {
        // Process object
        float_t ly = object->globalToLocalY(y);
        object->beginLine(ly);
        // Process filters
        Filter* filter = object->filters;
        while (filter) {
            filter->beginLine(ly);
            filter = filter->next();
        }
        // Process masks
        if (object->_hasMask) {
            DisplayObject* child = object->firstChild();
            while (child) {
                if (child->mask != MaskType::none && child->visible()) {
                    _beginLine(child, y);
                }
                child = child->next();
            }
        }
    }

    void Stage::_endRender(DisplayObject* object) {
        // Process object
        object->endRender();
        // Process filters
        Filter* filter = object->filters;
        while (filter) {
            filter->endRender();
            filter = filter->next();
        }
        // Process masks
        if (object->_hasMask) {
            DisplayObject* child = object->firstChild();
            while (child) {
                if (child->mask != MaskType::none && child->visible()) {
                    _endRender(child);
                }
                child = child->next();
            }
        }
    }

    void Stage::backgroundColor(color888 bgColor) {
        _backgroundColor = bgColor;
    }

    color888 Stage::backgroundColor() {
        return _backgroundColor;
    }

    void Stage::_traverse(LineBuffer* buffer, DisplayObject* child, bool forceDirty, Matrix* t, bool isMask) {
        // Step all children
        while (child) {

            // Mask
            if (child->mask != MaskType::none && child->visible()) {
                child->parent()->_hasMask = true;
            }

            // Force dirty?
            if (forceDirty) child->dirty();

            // If not visible and not dirty, skip to next child
            else if ((!child->visible() || (child->alpha <= 0)) && !child->isDirty()) {
                child = child->next();
                continue;
            }

            // Get child to calculate global bounds
            child->transform(t);

            // If child is dirty, include it's old position
            if (child->isDirty() && !child->cleanBounds->isEmpty()) {
                _dirtyBounds->grow(child->cleanBounds);
            }

            // Check if on the display and is not a mask
            if (child->globalBounds->overlaps(&buffer->rect) && child->mask == MaskType::none && !isMask) {

                // Calculate depth
                child->depth = ++_displayListDepth;

                // Add to display list
                _displayList->insertByPosition(child);

                // Add current position to screen dirty area
                if (child->isDirty()) {
                    _dirtyBounds->grow(child->globalBounds);
                    child->cleanBounds->set(child->globalBounds);

                    /* Debug transforms
                    Serial.printf("Traversing child ID:%d\n", child->id);
                    Serial.printf("  Local bounds %.2f,%.2f %.2fx%.2f\n", child->_localBounds->p1.x, child->_localBounds->p1.y, child->_localBounds->width(), child->_localBounds->height());
                    Serial.printf("  Transform %.2f,%.2f, Offset %.2f,%.2f\n", child->_transform->tx, child->_transform->ty, child->_ox, child->_oy);
                    Serial.printf("  Global bounds %d,%d %dx%d\n", child->globalBounds->x, child->globalBounds->y, child->globalBounds->width, child->globalBounds->height);
                    */
                }

            }

            // Recurse
            if (child->hasChildren()) _traverse(buffer, child->firstChild(), child->isDirty(), child->_transform, isMask || child->mask != MaskType::none);

            // Next sibling
            child = child->next();
        }
    }

    void Stage::_recycleList(DisplayList* list) {
        DisplayList* next = list;
        while (list) {
            next = list->next();
            list->object->_hasMask = false;
            list->recycle();
            list = next;
        }
    }

} // namespace craft