#ifndef SUBORBITAL_WATCHABLE_HPP
#define SUBORBITAL_WATCHABLE_HPP

#include <suborbital/watch_ptr.hpp>

namespace suborbital
{
    /**
     * The base class for all classes that can be watched by watch_ptr's.
     */
    class Watchable
    {
    public:
        /**
         * Constructor.
         */
        Watchable();

        /**
         * Destructor.
         *
         * Nulls pointers to the watchable object from every watcher.
         */
        virtual ~Watchable();

        /**
         * Linked list of watch_ptr's that are pointing to the watchable object.
         */
        mutable watch_ptr_base m_watchers;
    };
}

#endif