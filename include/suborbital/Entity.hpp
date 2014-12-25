#ifndef SUBORBITAL_ENTITY_HPP
#define SUBORBITAL_ENTITY_HPP

#include <cassert>
#include <string>
#include <memory>
#include <unordered_map>
#include <vector>
#include <iostream>

#include <suborbital/watch_ptr.hpp>
#include <suborbital/NonCopyable.hpp>
#include <suborbital/Watchable.hpp>
#include <suborbital/component/Attribute.hpp>
#include <suborbital/component/Behaviour.hpp>
#include <suborbital/component/ComponentRegistry.hpp>

namespace suborbital
{
    /**
     * Represents an object within a scene.
     */
    class Entity : public Watchable, private NonCopyable
    {
    public:
        /**
         * Constructor.
         *
         * Sets the entity's name to the empty string.
         */
        Entity();

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
         * Checks whether the entity has an attribute with the type attached.
         *
         * @return True if a attribute with the specified type is owned by the entity, false otherwise.
         */
        template<typename AttributeType>
        bool has_attribute() const
        {
            const std::string attribute_name = component_registry().component_name<AttributeType>();
            auto iter = m_attributes.find(attribute_name);
            if (iter != m_attributes.end())
            {
                auto& attributes = iter->second;
                if (!attributes.empty())
                {
                    AttributeType* attribute_ptr = dynamic_cast<AttributeType*>(attributes.front().get());
                    return attribute_ptr != nullptr;
                }
            }

            return false;
        }

        /**
         * Checks whether the entity has an attribute with the specified class name attached.
         *
         * This function is intended to be called from within scripts. Users of the c++ API should use the templated
         * function provided.
         *
         * @param Class name for the behaviour.
         * @return True if a behaviour with the specified class name is owned by the entity, false otherwise.
         */
        bool has_attribute(const std::string& class_name) const;

        /**
         * Creates and attaches an attribute of the specified type to the entity and returns a pointer to the created
         * attribute.
         *
         * @return Pointer to the attribute that was created and attached.
         */
        template<typename AttributeType>
        watch_ptr<AttributeType> create_attribute()
        {
            AttributeType* attribute_ptr = new AttributeType();
            const std::string attribute_name = component_registry().component_name<AttributeType>();
            m_attributes[attribute_name].push_back(std::unique_ptr<AttributeType>(attribute_ptr));

            attribute_ptr->m_entity = this;
            attribute_ptr->create();
            return watch_ptr<AttributeType>(attribute_ptr);
        }

        /**
         * Creates and attaches an attribute of the type specified by `class_name` to the entity and returns a pointer
         * to the created attribute.
         *
         * This function is intended to be called from within scripts. Users of the c++ API should use the templated
         * function provided.
         *
         * @param class_name Class name for the attribute to be created and attached.
         * @return Pointer to the attribute that was created and attached.
         */
        suborbital::watch_ptr<suborbital::Attribute> create_attribute(const std::string& class_name);

        /**
         * Returns a pointer to the attached attribute with the specified type. If multiple attributes of the specified
         * type are attached then the first such attribute is returned.
         *
         * @note The caller is NOT responsible for managing the lifetime of the returned behaviour.
         *
         * @return Pointer to the first attached attribute with the specified type.
         */
        template<typename AttributeType>
        watch_ptr<AttributeType> attribute()
        {
            const std::string attribute_name = component_registry().component_name<AttributeType>();
            auto iter = m_behaviours.find(attribute_name);
            assert(iter != m_behaviours.end());
            assert(!iter->second.empty());

            AttributeType* attribute_ptr = dynamic_cast<AttributeType*>(iter->second.front().get());
            assert(attribute_ptr != nullptr);
            return watch_ptr<AttributeType>(attribute_ptr);
        }

        /**
         * Returns a pointer the attached attribute with the specified class name. If multiple attributes of type
         * specified by `class_name` are attached then the first such attribute is returned.
         *
         * This function is intended to be called from within scripts. Users of the c++ API should use the templated
         * function provided, which attempts to safely cast the requested attribute to the specified type.
         *
         * @param class_name Class name for the attribute to be returned.
         * @return Pointer to the first attached attribute with the specified class name.
         */
        watch_ptr<Attribute> attribute(const std::string& class_name) const;

        /**
         * Attaches a behaviour of the specified type to the entity.
         *
         * @note The caller is NOT responsible for managing the lifetime of the returned behaviour.
         */
        template<typename BehaviourType>
        void create_behaviour()
        {
            BehaviourType* specific_behaviour_ptr = new BehaviourType();
            std::unique_ptr<BehaviourType> specific_behaviour(specific_behaviour_ptr);

            const std::string name = component_registry().component_name<BehaviourType>();
            m_behaviours[name].push_back(std::move(specific_behaviour));

            specific_behaviour_ptr->m_entity = this;
            specific_behaviour_ptr->create();
        }

        /**
         * Attaches a behaviour of type specified by `class_name` to the entity.
         *
         * This function is intended to be called from within scripts. Users of the c++ API should use the templated
         * function provided.
         *
         * @note The caller is NOT responsible for managing the lifetime of the returned behaviour.
         *
         * @param class_name Class name for the behaviour to be created and attached.
         */
        void create_behaviour(const std::string& class_name);

    public: // TODO: Make this private and friend the Scene class.
        /**
         * Updates all the behaviours belonging to the entity.
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
         * Attributes attached to the entity, indexed by class name.
         *
         * We store unique_ptr's here so that the attributes attached to an entity are automatically deleted when the
         * entity is deleted.
         */
        std::unordered_map<std::string, std::vector<std::unique_ptr<Attribute>>> m_attributes;

        /**
         * Behaviours attached to the entity, indexed by class name.
         *
         * We store unique_ptr's here so that the behaviours attached to an entity are automatically deleted when the
         * entity is deleted.
         */
        std::unordered_map<std::string, std::vector<std::unique_ptr<Behaviour>>> m_behaviours;
    };
}

#endif