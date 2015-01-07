#ifndef SUBORBITAL_WatchPtr_HPP
#define SUBORBITAL_WatchPtr_HPP

#include <cstddef>
#include <cassert>

namespace suborbital
{
    // Forward declarations.
    class Watchable;

    /**
     * Base class for the template `WatchPtr` class.
     */
    class WatchPtrBase
    {
    friend Watchable;
    protected:
        /**
         * Pointer to the object that the WatchPtr is watching.
         *
         * This pointer will be null when the object being watched is deleted.
         */
        const Watchable* ptr = nullptr; // Payload.

        /**
         * Pointer to the previous WatchPtr node in the linked list.
         */
        WatchPtrBase* previous = nullptr; // Pointer to the previous node.

        /**
         * Pointer to the next WatchPtr node in the linked list.
         */
        WatchPtrBase* next = nullptr; // Pointer to the next node.

    protected:
        /**
         * Links the WatchPtr to the supplied watchable object.
         */
        void link(const Watchable* watchable_object);

        /**
         * Unlinks the WatchPtr from the object that it is currently watching.
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
    class WatchPtr : public WatchPtrBase
    {
    public:
        /**
         * Constructor.
         */
        WatchPtr() = default;

        /**
         * Constructor.
         */
        WatchPtr(std::nullptr_t) {};

        /**
         * Constructor.
         */
        explicit WatchPtr(T* t)
        {
            link(t);
        }

        /**
         * Copy constructor.
         */
        WatchPtr(const WatchPtr& t)
        {
            link(t.ptr);
        }

        /**
         * Copy constructor.
         */
        template<typename U>
        WatchPtr(const WatchPtr<U>& t)
        {
            link(t.ptr);
        }

        /**
         * Destructor.
         */
        ~WatchPtr()
        {
            unlink();
        }

        /**
         * Copy assignment operator.
         *
         * @param t Pointer to the object to watch.
         * @return Reference to this WatchPtr.
         */
        WatchPtr& operator=(T* t)
        {
            unlink();
            link(t);
            return *this;
        }

        /**
         * Copy assignment operator.
         *
         * @param other Other WatchPtr to copy from.
         * @return Reference to this WatchPtr.
         */
        WatchPtr& operator=(const WatchPtr& other)
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
         * @param other The other WatchPtr to compare with.
         * @return True if the two WatchPtr's are watching the same object, false otherwise.
         */
        bool operator==(const WatchPtr &other) const
        {
            return ptr == other.ptr;
        }

        /**
         * Less-than comparison operator.
         *
         * @param other The other WatchPtr to compare with.
         * @return True if the pointer being watched is addressed in memory before the pointer being watched by `other`,
         * false otherwise.
         */
        bool operator<(const WatchPtr &other) const
        {
            return ptr < other.ptr;
        }

        /**
         * Boolean conversion operator.
         *
         * @return True if the WatchPtr is watching a valid object, false otherwise.
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
     * If the dynamic cast fails then an empty `WatchPtr` is returned.
     *
     * @param t The WatchPtr to be dynamically cast.
     * @return A `WatchPtr` that watches the same pointer as `t` with potentially different type.
     */
    template<typename T, typename U>
    WatchPtr<T> dynamic_pointer_cast(const WatchPtr<U>& t)
    {
        return WatchPtr<T>(dynamic_cast<T*>(t.get()));
    }

    /**
     * Returns a copy of `t` with its stored pointer cast statically from `U` to `T`.
     *
     * @param t The WatchPtr to be dynamically cast.
     * @return A `WatchPtr` that watches the same pointer as `t` with potentially different type.
     */
    template<typename T, typename U>
    WatchPtr<T> static_pointer_cast(const WatchPtr<U>& t)
    {
        return WatchPtr<T>(static_cast<T*>(t.get()));
    }
}

#endif