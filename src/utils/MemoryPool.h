#pragma once

namespace craft {

    /**
     * @brief Base class for memory pooled objects
     */
    template <class T> class MemoryPool {
    public:
        /**
         * @brief Destroy the Pool object
         */
        virtual ~MemoryPool() {}

        /**
         * @brief Set all object properties back to defaults ready for re-use
         */
        virtual void reset() {}

        /**
         * Create factory method. Uses memory pool for object re-use.
         */
        static T* Create() {
            T* obj;
            if (_pool) {
                obj = _pool;
                _pool = obj->_poolNext;
            }
            else {
                obj = new T();
            }
            return obj;
        }

        /**
         * Return this object to the pool
         */
        virtual void recycle() {
            #ifdef MAC_OBJECT_REUSE
            this->reset();
            this->_poolNext = _pool;
            _pool = (T*)this;
            #else
            delete (T*)this;
            #endif
        }

        /**
         * Frees all objects in the memory pool
         */
        static void Destroy() {
            T* obj;
            while (*_pool) {
                obj = _pool;
                _pool = obj->_poolNext;
                delete obj;
            }
        }

    protected:

        static T* _pool;
        T* _poolNext = nullptr;

    };

    template <class T>
    T* MemoryPool<T>::_pool = nullptr;

} // namespace craft
