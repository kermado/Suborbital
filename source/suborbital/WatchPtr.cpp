#include <cassert>

#include <suborbital/WatchPtr.hpp>
#include <suborbital/Watchable.hpp>

namespace suborbital
{
    WatchPtrBase::WatchPtrBase()
    : ptr(nullptr)
    {
        // Nothing to do.
    }

    void WatchPtrBase::watch(const Watchable* watchable_object)
    {
        // Stop watching existing object.
        unwatch();

        // Start watching the provided object.
        if (watchable_object != nullptr)
        {
            watchable_object->m_watchers.insert(this);
            ptr = watchable_object;
        }
    }

    void WatchPtrBase::unwatch()
    {
        if (ptr != nullptr)
        {
            std::size_t removed = ptr->m_watchers.erase(this);
            assert(removed == 1);

            ptr = nullptr;
        }
    }
}