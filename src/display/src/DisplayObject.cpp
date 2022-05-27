#include "../DisplayObject.h"

namespace craft {

    /**
     * Constructor
     */
    DisplayObject::DisplayObject() {
        globalBounds = new ClipRect();
        _localBounds = new ClipRect();
        cleanBounds = new ClipRect();
        renderBounds = new ClipRect();
    }

    /**
     * Destructor
     **/
    DisplayObject::~DisplayObject() {
        reset();
        delete renderBounds;
        delete cleanBounds;
        delete _localBounds;
        delete globalBounds;
    }

    /**
     * Reset the object back to default settings
     */
    void DisplayObject::reset() {
        clearFilters();
        removeAllChildren();
        id = 0;
        _ox = 0.0;
        _oy = 0.0;
        _dirty = true;
        _visible = true;
        _active = true;
        mask = MaskType::none;
        _hasMask = false;
        width(0);
        height(0);
        globalBounds->clear();
        _localBounds->clear();
        cleanBounds->clear();
        renderBounds->clear();
    }

    void DisplayObject::visible(boolean v) {
        _visible = v;
        _dirty = true;
    }

    /**
     * Get the visibility of an object
     * @return boolean The visibility
     */
    boolean DisplayObject::visible() {
        return _visible;
    }

    /**
     * @brief Return parent
     * @return DisplayObject* The parent display object, or null
     */
    DisplayObject* DisplayObject::parent() {
        return _parent;
    }

    /**
     * Return true if there is a parent
     */
    boolean DisplayObject::hasParent() {
        return (_parent != 0);
    }

    /**
     * Add a child to the list
     */
    void DisplayObject::addChild(DisplayObject* child) {
        //Serial.println("DisplayObject::addChild");
        if (!_children) {
            _children = child;
            child->_parent = this;
            child->_next = 0;
        }
        else {
            _childrenTop->_add(child);
        }
        _childrenTop = child;
        dirty();
        _added(child);
    }

    /**
     * Remove a child from the list
     * @param 	child 		The widget to remove
     */
    void DisplayObject::removeChild(DisplayObject* child) {
        if (!_children) return;
        DisplayObject* displayObject = _children;
        while (displayObject) {
            if (displayObject == child) {
                if (displayObject->_next) {
                    displayObject->_next->_prev = displayObject->_prev;
                }
                if (displayObject->_prev) {
                    displayObject->_prev->_next = displayObject->_next;
                }
                if (_children == displayObject) {
                    _children = displayObject->_next;
                }
                if (_childrenTop == displayObject) {
                    _childrenTop = displayObject->_prev;
                }
                displayObject->_parent = 0;
                dirty();
                _removed(child);
                break;
            }
            displayObject = displayObject->next();
        }
    }

    /**
     * Remove a child from the list by ID
     * @param 	id 		The ID of the widget to remove
     */
    void DisplayObject::removeChild(uint32_t id) {
        if (!_children) return;
        DisplayObject* displayObject = _children;
        while (displayObject) {
            if (displayObject->id == id) {
                if (displayObject->_next) {
                    displayObject->_next->_prev = displayObject->_prev;
                }
                if (displayObject->_prev) {
                    displayObject->_prev->_next = displayObject->_next;
                }
                if (_children == displayObject) {
                    _children = displayObject->_next;
                }
                if (_childrenTop == displayObject) {
                    _childrenTop = displayObject->_prev;
                }
                displayObject->_parent = 0;
                dirty();
                _removed(displayObject);
                break;
            }
            displayObject = displayObject->next();
        }
    }

    /**
     * Remove all children from the list
     */
    void DisplayObject::removeAllChildren(boolean free) {
        if (!_children) return;
        DisplayObject* displayObject = _children;
        DisplayObject* nextDisplayObject;
        while (displayObject) {
            nextDisplayObject = displayObject->next();
            _removed(displayObject);
            if (free) delete displayObject;
            else {
                displayObject->_parent = 0;
                displayObject->_next = 0;
                displayObject->_prev = 0;
            }
            displayObject = nextDisplayObject;
        }
        _children = 0;
        _childrenTop = 0;
        dirty();
    }

    /**
     * Return the first child
     */
    DisplayObject* DisplayObject::firstChild() {
        return _children;
    }

    /**
     * Return the first child
     */
    DisplayObject* DisplayObject::lastChild() {
        DisplayObject* displayObject = _children;
        DisplayObject* nextDisplayObject;
        while (displayObject) {
            nextDisplayObject = displayObject->next();
            if (!nextDisplayObject) return displayObject;
            displayObject = nextDisplayObject;
        }
        return 0;
    }

    /**
     * Return a child from the list by ID
     * @param 	id 		The ID of the widget
     */
    DisplayObject* DisplayObject::getChild(uint32_t id) {
        if (!_children) return 0;
        DisplayObject* displayObject = _children;
        while (displayObject) {
            if (displayObject->id == id) return displayObject;
            displayObject = displayObject->next();
        }
        return 0;
    }

    /**
     * Return the number of children
     */
    uint32_t DisplayObject::numChildren() {
        uint32_t count = 0;
        DisplayObject* displayObject = _children;
        while (displayObject) {
            count++;
            displayObject = displayObject->next();
        }
        return count;
    }

    /**
     * Return true if there are children
     */
    boolean DisplayObject::hasChildren() {
        return (boolean)_children;
    }

    /**
     * Get next sibling in the list
     */
    DisplayObject* DisplayObject::next(void) {
        return _next;
    }

    /**
     * Get previous sibling in the list
     */
    DisplayObject* DisplayObject::prev(void) {
        return _prev;
    }

    /**
     * Add or insert a sibling after this one
     */
    void DisplayObject::_add(DisplayObject* sibling) {
        if (_next) {
            _next->_prev = sibling;
            sibling->_next = _next;
        }
        else {
            sibling->_next = 0;
        }
        _next = sibling;
        sibling->_prev = this;
        sibling->_parent = _parent;
    }

    /**
     * Update and render the display object
     */
    void DisplayObject::update(float_t dt) {
        if (!_children) return;
        DisplayObject* displayObject = _children;
        while (displayObject) {
            displayObject->update(dt);
            displayObject = displayObject->next();
        }
    }

    /**
     * @brief Set the origin x coordinate within the object
     * @param value The origin x coordinate
     */
    void DisplayObject::originX(float_t value) {
        _ox = -value;
        dirty();
    }

    /**
     * @return float_t The origin x coordinate
     */
    float_t DisplayObject::originX() {
        return -_ox;
    }

    /**
     * @brief Set the origin y coordinate within the object
     * @param value The origin y coordinate
     */
    void DisplayObject::originY(float_t value) {
        _oy = -value;
        dirty();
    }

    /**
     * @return float_t The origin y coordinate
     */
    float_t DisplayObject::originY() {
        return -_oy;
    }

    /**
     * @brief Set the origin within the object to predefined position
     * @param position The position of the origin
     * @param roundToInt If true, will round the x and y cooridnates using floor
     */
    void DisplayObject::origin(OriginType position, boolean roundToInt) {
        switch (position) {
            case OriginType::centerTop:
            case OriginType::center:
            case OriginType::centerBottom:
                _ox = -width() / 2;
                break;
            case OriginType::rightTop:
            case OriginType::rightCenter:
            case OriginType::rightBottom:
                _ox = -width();
                break;
            case OriginType::leftTop:
            case OriginType::leftCenter:
            case OriginType::leftBottom:
            default:
                _ox = 0;
                break;
        }
        switch (position) {
            case OriginType::leftCenter:
            case OriginType::center:
            case OriginType::rightCenter:
                _oy = -height() / 2;
                break;
            case OriginType::leftBottom:
            case OriginType::centerBottom:
            case OriginType::rightBottom:
                _oy = -height();
                break;
            case OriginType::leftTop:
            case OriginType::centerTop:
            case OriginType::rightTop:
            default:
                _oy = 0;
                break;
        }
        if (roundToInt) {
            _ox = floor(_ox);
            _oy = floor(_oy);
        }
        _dirty = true;
    }

    /**
     * @brief Set the x coordinate
     * @param value The x coordinate
     */
    void DisplayObject::x(float_t value) {
        _localBounds->setPos(value, _localBounds->y);
        dirty();
    }

    /**
     * @return float_t The x coordinate
     */
    float_t DisplayObject::x() {
        return _localBounds->x;
    }

    /**
     * @brief Set the y coordinate
     * @param value The y coordinate
     */
    void DisplayObject::y(float_t value) {
        _localBounds->setPos(_localBounds->x, value);
        dirty();
    }

    /**
     * @return float_t The y coordinate
     */
    float_t DisplayObject::y() {
        return _localBounds->y;
    }

    /**
     * @brief Set the width
     * @param value The new width
     */
    void DisplayObject::width(float_t value) {
        _localBounds->setWidth((value > 0) ? value : 0);
        dirty();
    }

    /**
     * @return float_t The width
     */
    float_t DisplayObject::width() {
        return _localBounds->width;
    }

    /**
     * @brief Set the height
     * @param value The new height
     */
    void DisplayObject::height(float_t value) {
        _localBounds->setHeight((value > 0) ? value : 0);
        dirty();
    }

    /**
     * @return float_t The height
     */
    float_t DisplayObject::height() {
        return _localBounds->height;
    }

    /**
     * Set self to dirty
     */
    void DisplayObject::dirty() {
        if (_visible) _dirty = true;
    }

    /**
     * Check if object is dirty
     */
    boolean DisplayObject::isDirty() {
        return _dirty;
    }

    /**
     * @brief Set the global position of the display object
     *
     * @param x The global X position
     * @param y The global Y position
     */
    void DisplayObject::globalPos(float_t x, float_t y) {
        globalBounds->setPosAndSize(
            x + _ox + _localBounds->x,
            y + _oy + _localBounds->y,
            _localBounds->width,
            _localBounds->height
        );
    }

    /**
     * @brief Convert a global X coordinate to a local coord
     *
     * @param x The global X coordinate
     * @return float_t The local X coordinate
     */
    float_t DisplayObject::globalToLocalX(float_t x) {
        return x - (float_t)(globalBounds->x);
    }

    /**
     * @brief Convert a global Y coordinate to a local coord
     *
     * @param x The global Y coordinate
     * @return float_t The local Y coordinate
     */
    float_t DisplayObject::globalToLocalY(float_t y) {
        return y - (float_t)(globalBounds->y);
    }

    /**
     * @brief Convert a rect in global coordinates to local coordinates
     *
     * @param rect (out) The rext with global coordinate
     */
    void DisplayObject::globalToLocal(ClipRect* rect) {
        rect->translate(-globalBounds->x, -globalBounds->y);
    }

    void DisplayObject::clearFilters() {
        Filter* f;
        while (this->filters) {
            f = this->filters->next();
            this->filters->recycle();
            this->filters = f;
        }
    }

    /**
     * @brief Begin the render sweep for the current frame
    * @param updateArea The area of the display being updated
    */
    void DisplayObject::beginRender(ClipRect* updateArea) {
        _dirty = false;
        renderBounds->set(updateArea);
        renderBounds->clip(globalBounds);
        globalToLocal(renderBounds);
    }

} // namespace craft