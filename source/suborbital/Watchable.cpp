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
        for (WatchPtrBase* watcher : m_watchers)
        {
            watcher->ptr = nullptr;
        }
    }

    std::size_t Watchable::use_count() const
    {
        return m_watchers.size();
    }
}