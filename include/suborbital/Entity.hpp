#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <cassert>
#include <string>
#include <memory>
#include <unordered_map>
#include <vector>
#include <iostream>

#include <suborbital/NonCopyable.hpp>
#include <suborbital/component/Component.hpp>

namespace suborbital
{
    /**
     * Represents an object within a scene.
     */
    class Entity : private NonCopyable
    {
    public:
        /**
         * Constructor.
         *
         * @param name Name to assign to the entity.
         */
        Entity(const std::string& name);

        /**
         * Destructor.
         */
        ~Entity();

        /**
         * Accessor for the name assigned to the entity.
         *
         * @return Name assigned to the entity.
         */
        const std::string& name() const;

        /**
         * Checks whether the entity has a component with the type attached.
         *
         * @return True if a component with the specified type is owned by the entity, false otherwise.
         */
        template<typename ComponentType>
        bool has_component() const
        {
            const std::string component_name = component::name<ComponentType>();
            auto iter = m_components.find(component_name);
            if (iter != m_components.end())
            {
                auto& components = iter->second;
                if (!components.empty())
                {
                    ComponentType*component_ptr = dynamic_cast<ComponentType*>( components.front().get());
                    return component_ptr != nullptr;
                }
            }

            return false;
        }

        /**
         * Checks whether the entity has a component with the specified class name attached.
         *
         * This function is intended to be called from within scripts. Users of the c++ API should use the templated
         * function provided.
         *
         * @param Class name for the component.
         * @return True if a component with the specified class name is owned by the entity, false otherwise.
         */
        bool has_component(const std::string& class_name) const;

        /**
         * Attaches a component of the specified type to the entity and returns a pointer to the created component.
         *
         * @note The caller is NOT responsible for managing the lifetime of the returned component.
         *
         * @return Pointer to the component that was created and attached.
         */
        template<typename ComponentType>
        ComponentType* create_component()
        {
            ComponentType*specific_component_ptr = new ComponentType();
            const std::string component_name = component::name<ComponentType>();
            m_components[component_name].push_back(std::unique_ptr<ComponentType>(specific_component_ptr));
            specific_component_ptr->m_entity = this;
            specific_component_ptr->create();
            return specific_component_ptr;
        }

        /**
         * Attaches a component of type specified by `class_name` to the entity and returns a pointer to the created
         * component.
         *
         * This function is intended to be called from within scripts. Users of the c++ API should use the templated
         * function provided.
         *
         * @note The caller is NOT responsible for managing the lifetime of the returned component.
         *
         * @param class_name Class name for the component to be created and attached.
         * @return Pointer to the component that was created and attached.
         */
        suborbital::component::Component* create_component(const std::string& class_name);

        /**
         * Returns a pointer to the attached component with the specified type. If multiple components of the specified
         * type are attached then the first such component is returned.
         *
         * @note The caller is NOT responsible for managing the lifetime of the returned component.
         *
         * @return Pointer to the first attached component with the specified type.
         */
        template<typename ComponentType>
        ComponentType* component()
        {
            const std::string component_name = component::name<ComponentType>();
            auto iter = m_components.find(component_name);
            assert(iter != m_components.end());
            assert(!iter->second.empty());

            ComponentType*component_ptr = dynamic_cast<ComponentType*>(iter->second.front().get());
            assert(component_ptr != nullptr);
            return component_ptr;
        }

        /**
         * Returns a pointer to the attached component with the specified class name. If multiple components of type
         * specified by `class_name` are attached then the first such component is returned.
         *
         * This function is intended to be called from within scripts. Users of the c++ API should use the templated
         * function provided, which attempts to safely cast the requested component to the specified type.
         *
         * @note The caller is NOT responsible for managing the lifetime of the returned component.
         *
         * @param class_name Class name for the component to be returned.
         * @return Pointer to the first attached component with the specified class name.
         */
        suborbital::component::Component* component(const std::string& class_name) const;

    protected:
        /**
         * Updates all the components belonging to the entity.
         *
         * This function is called once per state update by the scene that the entity belongs to.
         *
         * @param dt Time elapsed (in seconds) since the previous call to update.
         */
        void update(double dt);

    private:
        /**
         * Name assigned to the entity.
         */
        const std::string m_name;

        /**
         * Components attached to the entity, indexed by class name.
         *
         * We store unique_ptr's here so that the components attached to an entity are automatically deleted when the entity
         * is deleted.
         */
        std::unordered_map<std::string, std::vector<std::unique_ptr<component::Component>>> m_components;
    };
}

#endif