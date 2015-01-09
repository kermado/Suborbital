#include <suborbital/scene/SceneStack.hpp>

namespace suborbital
{
    SceneStack::SceneStack()
    : m_stack()
    , m_factories()
    {
        // Nothing to do.
    }

    SceneStack::~SceneStack()
    {
        // Nothing to do.
    }

    bool SceneStack::empty() const
    {
        return m_stack.empty();
    }

    void SceneStack::push(const std::string& name)
    {
        auto iter = m_factories.find(name);
        assert(iter != m_factories.end());

        std::unique_ptr<Scene> scene = iter->second->create();
        m_stack.push(std::move(scene));
    }

    void SceneStack::pop()
    {
        m_stack.pop();
    }

    void SceneStack::clear()
    {
        while (!m_stack.empty())
        {
            m_stack.pop();
        }
    }

    void SceneStack::process(double dt)
    {
        m_stack.top()->process(dt);
    }
}