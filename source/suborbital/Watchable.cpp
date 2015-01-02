#include <suborbital/Watchable.hpp>
#include <iostream>

namespace suborbital
{
    Watchable::Watchable()
    : m_watchers()
    {
        // Nothing to do.
    }

    Watchable::~Watchable()
    {
        std::cout << "Watchable::~Watchable()" << std::endl;
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