#pragma once

#include "utils/MemoryPool.h"
#include "geom/ClipRect.h"
#include "geom/Matrix.h"
#include "geom/Rect.h"
#include "display/filters/Filter.h"
#include "display/IDrawable.h"
#include "display/Messenger.h"
#include "physics/Tween.h"
#include "graphics/Color8888.h"

namespace craft {

    /**
     * @brief Origin position type
     */
    enum class OriginType {
        leftTop,
        centerTop,
        rightTop,
        leftCenter,
        center,
        rightCenter,
        leftBottom,
        centerBottom,
        rightBottom,
    };

    /**
     * @brief Type of masking
     */
    enum class MaskType {
        none,
        mask,
        inverse,
    };

    /**
     * The base class for all display objects (@see Stage)
     */
    class DisplayObject : public Listener, public IDrawable {
        friend class Stage;
    public:
        /**
         * Constructor
         */
        DisplayObject();

        /**
         * Destructor
         */
        virtual ~DisplayObject();

        /**
         * @brief type (for RTTI)
         */
        int type = 0;

        /**
         * Reset back to default settings
         */
        virtual void reset();

        /**
         * ID of the object. Implementation specific.
         */
        uint32_t id = 0;

        /**
         * Listener for events
         */
        Messenger* messenger = nullptr;

        /**
         * Tween object for animations
         */
        Tween* tweens = nullptr;

        /**
         * @brief Rect describing the bounds in global space (relative to stage)
         * This is calculated automatically from the origin and the local bounds during the rendering
         * sweep.
         */
        ClipRect* globalBounds = nullptr;

        /**
         * @brief Rect describing the part of this object being rendered in the current cycle, in local space
         * This is calculated when beginRender is called
         */
        ClipRect* renderBounds = nullptr;

        /**
         * @brief Rect describing the last dirty area in global space (relative to stage)
         */
        ClipRect* cleanBounds = nullptr;

        /**
         * Alpha of entire object
         */
        float_t alpha = 1.0;

        /**
         * Display depth
         */
        uint32_t depth = 0;

        /**
         * If true, this display object will mask objects below it
         */
        MaskType mask = MaskType::none;

        /**
         * Set the Visibility of the object
         * @param v 	The visibility
         */
        void visible(bool v);

        /**
         * Get the visibility of an object
         * @return bool The visibility
         */
        bool visible();

        /**
         * @brief Return parent
         * @return DisplayObject* The parent display object, or null
         */
        DisplayObject* parent();

        /**
         * Return true if there is a parent
         */
        bool hasParent();

        /**
         * Add a display object to the top of the list
         */
        void addChild(DisplayObject* child);

        /**
         * Add a display object before a sibling object
         */
        void addChildBefore(DisplayObject* child, DisplayObject* sibling);

        /**
         * Remove a child from the list
         * @param 	child 		The object to remove
         */
        void removeChild(DisplayObject* child);

        /**
         * Remove a child from the list by ID
         * @param 	id 		The ID of the object
         */
        void removeChild(uint32_t id);

        /**
         * Remove all children from the list
         * @param 	free		If true, will delete the objects from memory.
         */
        void removeAllChildren(bool free = true);

        /**
         * Return the first child
         */
        DisplayObject* firstChild();

        /**
         * Return the last child
         */
        DisplayObject* lastChild();

        /**
         * Return a child from the list by ID
         * @param 	id 		The ID of the object
         */
        DisplayObject* getChild(uint32_t id);

        /**
         * Return the number of children
         */
        uint32_t numChildren();

        /**
         * Return true if there are children
         */
        bool hasChildren();

        /**
         * Get next sibling in the list
         */
        DisplayObject* next(void);

        /**
         * Get previous sibling in the list
         */
        DisplayObject* prev(void);

        /**
         * @brief Set the origin x coordinate within the object
         * @param value The origin x coordinate
         */
        virtual void originX(float_t value);

        /**
         * @return float_t The origin x coordinate
         */
        virtual float_t originX();

        /**
         * @brief Set the origin y coordinate within the object
         * @param value The origin y coordinate
         */
        virtual void originY(float_t value);

        /**
         * @return float_t The origin y coordinate
         */
        virtual float_t originY();

        /**
         * @brief Set the origin within the object to predefined position
         * @param position The position of the origin
         * @param roundToInt If true, will round the x and y cooridnates using floor
         */
        virtual void origin(OriginType position, bool roundToInt = false);

        /**
         * @brief Set the x coordinate
         * @param value The new width
         */
        virtual void x(float_t value);

        /**
         * @return float_t The x coordinate
         */
        virtual float_t x();

        /**
         * @brief Set the y coordinate
         * @param value The new width
         */
        virtual void y(float_t value);

        /**
         * @return float_t The y coordinate
         */
        virtual float_t y();

        /**
         * @brief Set the x and y coordinates
         * @param x The x coordinate
         * @param y The y coordinate
         */
        virtual void position(float_t x, float_t y);

        /**
         * @brief Set the width
         * @param value The new width
         */
        virtual void width(float_t value);

        /**
         * @return float_t The width
         */
        virtual float_t width();

        /**
         * @brief Set the height
         * @param value The new height
         */
        virtual void height(float_t value);

        /**
         * @return float_t The height
         */
        virtual float_t height();

        /**
         * @brief Set the scale
         * @param s The new scale
         */
        virtual void scale(float_t s);

        /**
         * @brief Set the scale
         * @param sx The new scale is x direction
         * @param sy The new scale is y direction
         */
        virtual void scale(float_t sx, float_t sy);

        /**
         * @return float_t The scale in the x direction
         */
        virtual float_t scaleX();

        /**
         * @return float_t The scale in the y direction
         */
        virtual float_t scaleY();

        /**
         * @brief Set the rotation, in degrees
         * @param s The new rotation, in degrees
         */
        virtual void rotation(float_t r);

        /**
         * @brief Adjust the rotation by a value in degrees
         * @param s The adjustment, in degrees
         */
        virtual void rotate(float_t r);

        /**
         * @return float_t The rotation, in degrees
         */
        virtual float_t rotation();

        /**
         * Update the display object.
         * @param	dt 			    Time since last update in seconds
         * @param   isRenderUpdate  True if this update is during the render phase, false otherwise
         */
        virtual void update(float_t dt, boolean isRenderUpdate = false);

        /**
         * @brief Set the global transform of the display object
         *
         * @param t The parent transformation matrix
         */
        virtual void transform(Matrix* t);

        /**
         * @brief Convert a global X coordinate to a local coord
         *
         * @param x The global X coordinate
         * @return float_t The local X coordinate
         */
        float_t globalToLocalX(float_t x);

        /**
         * @brief Convert a global Y coordinate to a local coord
         *
         * @param x The global Y coordinate
         * @return float_t The local Y coordinate
         */
        float_t globalToLocalY(float_t y);

        /**
         * @brief Convert a rect in global coordinates to local coordinates
         *
         * @param rect (out) The rext with global coordinate
         */
        void globalToLocal(ClipRect* rect);

        /**
         * Set dirty
         */
        void dirty();

        /**
         * Check if object is dirty
         */
        bool isDirty();

        /**
         * @brief Filters to apply during rendering
         */
        Filter* filters = nullptr;

        /**
         * @brief Clear all filters
         */
        void clearFilters();

        /**
         * @brief Begin the render sweep for the current frame
         * @param updateArea The area of the display being updated
         */
        virtual void beginRender(ClipRect* updateArea);

    protected:

        /**
         * Add a sibling as the next one in the list
         */
        void _add(DisplayObject* sibling);

        /**
         * @brief Called whenever a child is added to this display object
         * Override this to perform actions on display objects added using
         * any of the 'add' methods.
         * @see addChild
         * @see addChildBefore
         * @see _removed
         * @param child The display object that was added
         */
        virtual void _added(DisplayObject* child) {}

        /**
         * @brief Called whenever a child is removed from this display object
         * Override this to perform actions on display objects removed using
         * any of the 'remove' methods.
         * @see removeChild
         * @see removeAllChildren
         * @see _added
         * @param child The display object that was removed
         */
        virtual void _removed(DisplayObject* child) {}

        /**
         * Flag to indicate that the object needs to be redrawn
         */
        bool _dirty = true;

        /**
         * Visibility of the object. If false, object is updated but not rendered.
         */
        bool _visible = true;

        /**
         * Active flag. If false, object does not accept input.
         */
        bool _active = true;

        /**
         * Animation flag. If false, object does not animate.
         */
        bool _animate = false;

        /**
         * Masked flag. If true, this display object is masked.
         */
        bool _hasMask = false;

        /**
         * X offset of origin
         */
        float_t _ox = 0;

        /**
         * Y offset of origin
         */
        float_t _oy = 0;

        /**
         * X scale
         */
        float_t _sx = 1.0;

        /**
         * Y scale
         */
        float_t _sy = 1.0;

        /**
         * @brief Rotation, in degrees
         */
        float_t _rotation = 0;

        /**
         * @brief Rect describing the bounds in local space
         *
         * The width and height must contain the pixels completely. The x and y values are the
         * position of the object (relative to the parent).
         */
        Rect* _localBounds;

        /**
         * @brief The global transform
         * Calculated during each render cycle.
         */
        Matrix* _transform;

        /**
         * List of children
         **/
        DisplayObject* _parent = 0;
        DisplayObject* _children = 0;
        DisplayObject* _childrenTop = 0;
        DisplayObject* _next = 0;
        DisplayObject* _prev = 0;

    }; // class

} // namespace craft
