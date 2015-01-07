#include <cassert>

#include <suborbital/WatchPtr.hpp>
#include <suborbital/Watchable.hpp>

namespace suborbital
{
    void WatchPtrBase::link(const Watchable* watchable_object)
    {
        assert(previous == nullptr);
        assert(next == nullptr);

        ptr = watchable_object;

        if (watchable_object != nullptr)
        {
            previous = &(watchable_object->m_watchers);
            next = watchable_object->m_watchers.next;

            if (watchable_object->m_watchers.next != nullptr)
            {
                watchable_object->m_watchers.next->previous = this;
            }

            watchable_object->m_watchers.next = this;
        }
    }

    void WatchPtrBase::unlink()
    {
        if (next != nullptr)
        {
            next->previous = previous;
        }

        if (previous != nullptr)
        {
            previous->next = next;
        }

        next = nullptr;
        previous = nullptr;
    }
}