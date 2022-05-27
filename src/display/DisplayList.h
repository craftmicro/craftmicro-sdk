#pragma once

#include "utils/LinkedList.h"
#include "display/DisplayObject.h"

namespace craft {

    /**
     * The compare function type
     */
    typedef int (*displayObjectCompareFunc)(DisplayObject*, DisplayObject*);

    /**
     * Display list that stores a list of display objects in render order.
     */
    class DisplayList : public LinkedList<DisplayList>, public MemoryPool<DisplayList> {
    public:

        /**
         * Create factory method. Uses memory pool
         * for object re-use.
         */
        static DisplayList* Create(DisplayObject* object) {
            DisplayList* obj = MemoryPool<DisplayList>::Create();
            obj->object = object;
            return obj;
        }

        /**
         * The display object at this position
         */
        DisplayObject* object;

        /**
         * Inserts an object into the list into sorted order by depth
         * Assumes object is visible and on the display.
         * @param object The object to insert
         */
        void insertByDepth(DisplayObject* object);

        /**
         * Inserts an object into the list into sorted order by position.
         * Assumes object is visible and on the display.
         * @param object The object to insert
         */
        void insertByPosition(DisplayObject* object);

    protected:

        /**
         * The internal function that inserts the object into the list using the
         * specified compare function for sorting.
         * @param object The object to insert
         * @param compare The compare function
         */
        void _insert(DisplayObject* object, displayObjectCompareFunc compare);
    };

} // namespace craft
