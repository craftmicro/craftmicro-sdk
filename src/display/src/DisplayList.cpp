#include "../DisplayList.h"

namespace craft {

    /**
     * Compare two display objects by position
     * @param a First display object
     * @param b Second display object
     * @return int8_t >0 if a is first, <0 if b is first, 0 if equal
     */
    int compareDisplayObjectByPosition(DisplayObject* a, DisplayObject* b) {
        if ((int)a->globalBounds->y < (int)b->globalBounds->y) return 1;	// Y is lower
        if ((int)a->globalBounds->y > (int)b->globalBounds->y) return -1;	// y is higher
        return (int)b->globalBounds->x - (int)a->globalBounds->x;
    }

    /**
     * Compare two display objects by depth
     * @param a First display object
     * @param b Second display object
     * @return int8_t >0 if a is first, <0 if b is first, 0 if equal
     */
    int compareDisplayObjectByDepth(DisplayObject* a, DisplayObject* b) {
        return (int)b->depth - (int)a->depth;
    }

    /**
     * Inserts an object into the list into sorted order by depth
     * Assumes object is visible and on the display.
     * @param object The object to insert
     */
    void DisplayList::insertByDepth(DisplayObject* object) {
        this->_insert(object, &compareDisplayObjectByDepth);
    }

    /**
     * Inserts an object into the list into sorted order by position
     * Assumes object is visible and on the display.
     * @param object The object to insert
     */
    void DisplayList::insertByPosition(DisplayObject* object) {
        this->_insert(object, &compareDisplayObjectByPosition);
    }

    /**
     * The internal function that inserts the object into the list using the
     * specified compare function for sorting.
     * @param object The object to insert
     * @param compare The compare function
     */
    void DisplayList::_insert(DisplayObject* object, displayObjectCompareFunc compare) {
        DisplayList* item;

        // If no next item, add as next item
        if (!_next) {
            item = DisplayList::Create(object);
            after(item);
            return;
        }

        // See where to insert
        int d = compare(object, next()->object);
        // If lower, move down the list
        if (d < 0) {
            next()->_insert(object, compare);
            return;
        }
        // If higher than next item, insert before next item (after this one)
        else {
            item = DisplayList::Create(object);
            after(item);
            return;
        }

    }

} // namespace craft