#pragma once

#include "display/DisplayList.h"
#include "display/Display.h"
#include "display/Pixel.h"
// Display object types
#include "display/DisplayObject.h"
#include "display/Sprite.h"
#include "display/Text.h"
#include "display/Shape.h"
#include "display/Box.h"
// Gradients
#include "display/LinearGradient.h"
// Filters
#include "display/filters/TintFilter.h"
#include "display/filters/ColorMaskFilter.h"
#include "display/filters/FuzzyColorMaskFilter.h"
#include "display/filters/HSVFilter.h"
#include "display/filters/ShadeFilter.h"
#include "display/filters/BumpFilter.h"

namespace craft {

    /**
     * The main stage object
     */
    class Stage : public DisplayObject {
    public:
        /**
         * Construct a new Stage object
         */
        Stage();

        /**
         * Destroy the Stage objectD
         */
        ~Stage();

        /**
         * Create a new object or take one from the pool
         * @return The new or recycled object
         */
        static Stage* Create();

        /**
         * Update all objects on the stage. This will advance animations, messages etc but
         * will not update the objects to the display.
         * @param	dt 			Time since last update in seconds
         * @param   isRenderUpdate      True if this update is during the render phase, false otherwise
         */
        void update(float_t dt, boolean isRenderUpdate = false) override;

        /**
         * Render the objects to the display
         */
        void render(Display* display);

        /**
         * Set the background color
         * @param bgColor The background color
         */
        void backgroundColor(color888 bgColor);

        /**
         * Get the background color
         * @return color The background color
         */
        color888 backgroundColor();

        /**
         * @brief Enable visual debugging of update area
         */
        bool debug = false;

        /**
         * @brief Color for visual debugging
         */
        color888 debugColor = Color8888::IndianRed;

    protected:
        /**
         * Stage color
         */
        color888 _backgroundColor = 0;

        /**
         * Area of the display that is dirty
         */
        ClipRect* _dirtyBounds;

        /**
         * Increments as the display list is traversed. Used to calculate
         * relative depth of all children
         */
        uint32_t _displayListDepth;

        /**
         * Ordered list of all visible display objects in the order that they
         * are added to the render list.
         */
        DisplayList* _displayList;

        /**
         * Ordered list of visible display objects to be rendered
         * on the current scan line.
         */
        DisplayList* _renderList;

        /**
         * Area of the display that is dirty
         */
        ClipRect* _scaledRenderBounds;

        /**
         * @brief Traverse through display objects and insert into display list
         *
         * @param display 		The display (for accessing display size)
         * @param child 		The display object to process
         * @param forceDirty	True to force the child to be redrawn
         * @param px			The x-coordinate
         * @param py			The y-coordinate
         * @param isMask		True to force the child to be processed as a mask
         */
        void _traverse(Display* display, DisplayObject* child, bool forceDirty, Matrix* t, bool isMask);

        /**
         * Clear a DisplayList
         * @param list The list to recycle
         */
        void _recycleList(DisplayList* list);

        /**
         * @brief Helper to begin rendering an object
         * @param object The display object
         */
        void _beginRender(DisplayObject* object);

        /**
         * @brief Helper to begin rendering a line on an object
         * @param object The display object
         * @param y		 The y-coordinate of the line in global space
         */
        void _beginLine(DisplayObject* object, uint16_t y);

        /**
         * @brief Helper to end rendering an object
         * @param object The display object
         */
        void _endRender(DisplayObject* object);

    };

} // namespace craft
