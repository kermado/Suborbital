#include <suborbital/Watchable.hpp>

namespace suborbital
{
    Watchable::Watchable()
    : m_watchers()
    {
        // Nothing to do.
    }

    Watchable::~Watchable()
    {
        for (watch_ptr_base* watcher = m_watchers.next; watcher != nullptr; watcher = watcher->next)
        {
            watcher->ptr = nullptr;

            if (watcher->previous)
            {
                watcher->previous->next = nullptr;
            }

            watcher->previous = nullptr;
        }
    }
}