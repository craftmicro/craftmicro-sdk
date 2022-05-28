#pragma once

namespace craft {

    /**
     * Double-linked list. Inherit from this object to add list functionallity.
     */
    template <class T> class LinkedList {
    public:
        /**
         * Return the next item
         */
        T* next() {
            return _next;
        }

        /**
         * Set the next item. Don't use this unless you know what you are doing. The
         * normal way to insert items in the list is to call add, before or after.
         */
        void next(T* item) {
            _next = item;
        }

        /**
         * Return the previous item
         */
        T* prev() {
            return _prev;
        }

        /**
         * Set the prev item. Don't use this unless you know what you are doing. The
         * normal way to insert items in the list is to call add, before or after.
         */
        void prev(T* item) {
            _prev = item;
        }

        /**
         * Add an item to the end of the linked list
         */
        void add(T* item) {
            if (_next) _next->add(item);
            else {
                item->_prev = (T*)this;
                _next = item;
            }
        }

        /**
         * Insert an item as the previous item in the list
         */
        void before(T* item) {
            item->_next = (T*)this;
            item->_prev = _prev;
            if (_prev) _prev->_next = item;
            _prev = item;
        }

        /**
         * Insert an item as the next item in the list
         */
        void after(T* item) {
            item->_prev = (T*)this;
            item->_next = _next;
            if (_next) _next->_prev = item;
            _next = item;
        }

        /**
         * Remove the current item from the list
         * @return	The removed item (this)
         */
        T* remove() {
            if (_prev) {
                _prev->_next = _next;
            }
            if (_next) {
                _next->_prev = _prev;
            }
            return (T*)this;
        }

        /**
         * Remove the specified item from the list
         * @return	The removed item, or null if not found
         */
        T* remove(T* item) {
            if (this == item) return remove();
            if (_next) return _next->remove(item);
            return 0;
        }

    protected:

        /**
         * Previous object in list
         */
        T* _prev = 0;

        /**
         * Next object in list
         */
        T* _next = 0;
    };

} // namespace craft
