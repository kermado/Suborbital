#include <suborbital/Watchable.hpp>
#include <iostream>

namespace suborbital
{
    Watchable::Watchable()
    : m_watchers()
    {
        std::cout << "Watchable::Watchable()" << std::endl;
    }

    Watchable::~Watchable()
    {
        std::cout << "Watchable::~Watchable()" << std::endl;

        for (WatchPtrBase* watcher : m_watchers)
        {
            watcher->ptr = nullptr;
        }
    }
}