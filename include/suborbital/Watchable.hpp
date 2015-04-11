#ifndef SUBORBITAL_WATCHABLE_HPP
#define SUBORBITAL_WATCHABLE_HPP

#include <unordered_set>

#include <suborbital/WatchPtr.hpp>

namespace suborbital
{
    /**
     * The base class for all classes that can be watched by watch_ptr's.
     */
    class Watchable
    {
    friend WatchPtrBase;
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
         * Returns the number of WatchPtr objects that point to this object.
         *
         * @return Number of WatchPtr objects pointing to this object.
         */
        std::size_t use_count() const;

    private:
        /**
         * List of watch_ptr's that are pointing to the watchable object.
         */
        mutable std::unordered_set<WatchPtrBase*> m_watchers;
    };
}

#endif