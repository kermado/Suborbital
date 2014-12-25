#ifndef SUBORBITAL_WATCH_PTR_HPP
#define SUBORBITAL_WATCH_PTR_HPP

#include <cstddef>
#include <cassert>
#include <iostream>

namespace suborbital
{
    // Forward declarations.
    class Watchable;

    /**
     * Base class for the template `watch_ptr` class.
     */
    class watch_ptr_base
    {
    friend Watchable;
    protected:
        /**
         * Pointer to the object that the watch_ptr is watching.
         *
         * This pointer will be null when the object being watched is deleted.
         */
        const Watchable* ptr = nullptr; // Payload.

        /**
         * Pointer to the previous watch_ptr node in the linked list.
         */
        watch_ptr_base* previous = nullptr; // Pointer to the previous node.

        /**
         * Pointer to the next watch_ptr node in the linked list.
         */
        watch_ptr_base* next = nullptr; // Pointer to the next node.

    protected:
        /**
         * Links the watch_ptr to the supplied watchable object.
         */
        void link(const Watchable* watchable_object);

        /**
         * Unlinks the watch_ptr from the object that it is currently watching.
         */
        void unlink();
    };

    /**
     * Watch pointer.
     *
     * A watch pointer is a type of smart pointer that automatically becomes NULL and evaluates to false when the object
     * that it watches is deleted. This is similar to weak references used in other languages. Note that watchable
     * objects must derive from `Watchable`.
     *
     * Credit to Stephen Nichols whom described the concept in a blog posting:
     * http://www.codingwisdom.com/codingwisdom/2012/09/reference-counted-smart-pointers-are-for-retards.html
     *
     * Further credit to Arthur Danskin for implementation details:
     * http://www.anisopteragames.com/how-to-prevent-dangling-pointers-to-deleted-game-objects-in-c/
     */
    template<typename T>
    class watch_ptr : public watch_ptr_base
    {
    public:
        /**
         * Constructor.
         */
        watch_ptr() = default;

        /**
         * Constructor.
         */
        watch_ptr(std::nullptr_t) {};

        /**
         * Constructor.
         */
        explicit watch_ptr(T* t)
        {
            link(t);
        }

        /**
         * Copy constructor.
         */
        watch_ptr(const watch_ptr& t)
        {
            link(t.ptr);
        }

        /**
         * Copy constructor.
         */
        template<typename U>
        watch_ptr(const watch_ptr<U>& t)
        {
            link(t.ptr);
        }

        /**
         * Destructor.
         */
        ~watch_ptr()
        {
            unlink();
        }

        /**
         * Copy assignment operator.
         *
         * @param t Pointer to the object to watch.
         * @return Reference to this watch_ptr.
         */
        watch_ptr& operator=(T* t)
        {
            unlink();
            link(t);
            return *this;
        }

        /**
         * Copy assignment operator.
         *
         * @param other Other watch_ptr to copy from.
         * @return Reference to this watch_ptr.
         */
        watch_ptr& operator=(const watch_ptr& other)
        {
            unlink();
            link(other.ptr);
            return *this;
        }

        /**
         * Dereference operator.
         *
         * @return Reference to the object being watched.
         */
        T& operator*() const
        {
            return *get();
        }

        /**
         * Arrow operator.
         *
         * @return Pointer to the object being watched.
         */
        T* operator->() const
        {
            return get();
        }

        /**
         * Equality operator.
         *
         * @param other The other watch_ptr to compare with.
         * @return True if the two watch_ptr's are watching the same object, false otherwise.
         */
        bool operator==(const watch_ptr &other) const
        {
            return ptr == other.ptr;
        }

        /**
         * Less-than comparison operator.
         *
         * @param other The other watch_ptr to compare with.
         * @return True if the pointer being watched is addressed in memory before the pointer being watched by `other`,
         * false otherwise.
         */
        bool operator<(const watch_ptr &other) const
        {
            return ptr < other.ptr;
        }

        /**
         * Boolean conversion operator.
         *
         * @return True if the watch_ptr is watching a valid object, false otherwise.
         */
        explicit operator bool() const
        {
            return ptr != nullptr;
        }

        /**
         * Accessor for the object being watched.
         *
         * @return Pointer to the object being watched.
         */
        T* get() const
        {
            return (T*)ptr;
        }
    };

    /**
     * Returns a copy of `t` with its stored pointer cast dynamically from `U` to `T`.
     *
     * If the dynamic cast fails then an empty `watch_ptr` is returned.
     *
     * @param t The watch_ptr to be dynamically cast.
     * @return A `watch_ptr` that watches the same pointer as `t` with potentially different type.
     */
    template<typename T, typename U>
    watch_ptr<T> dynamic_pointer_cast(const watch_ptr<U>& t)
    {
        return watch_ptr<T>(dynamic_cast<T*>(t.get()));
    }

    /**
     * Returns a copy of `t` with its stored pointer cast statically from `U` to `T`.
     *
     * @param t The watch_ptr to be dynamically cast.
     * @return A `watch_ptr` that watches the same pointer as `t` with potentially different type.
     */
    template<typename T, typename U>
    watch_ptr<T> static_pointer_cast(const watch_ptr<U>& t)
    {
        return watch_ptr<T>(static_cast<T*>(t.get()));
    }
}

#endif