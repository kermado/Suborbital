#ifndef SUBORBITAL_ENTITY_HPP
#define SUBORBITAL_ENTITY_HPP

#include <cassert>
#include <string>
#include <memory>
#include <unordered_map>
#include <vector>
#include <iostream>

#include <suborbital/NonCopyable.hpp>
#include <suborbital/Watchable.hpp>
#include <suborbital/WatchPtr.hpp>

#include <suborbital/event/EventDispatcher.hpp>

#include <suborbital/component/Attribute.hpp>
#include <suborbital/component/Behaviour.hpp>
#include <suborbital/component/ComponentRegistry.hpp>

namespace suborbital
{
    // Forward declarations.
    class Scene;
    class System;

    /**
     * Represents an object within a scene.
     */
    class Entity : public Watchable, private NonCopyable
    {
    friend Scene;
    public:
        /**
         * Constructor.
         *
         * Sets the entity's name to the empty string.
         *
         * @param scene Scene that the entity is in.
         */
        Entity(Scene& scene);

        /**
         * Constructor.
         *
         * @param scene Scene that the entity is in.
         * @param name Name to assign to the entity.
         */
        Entity(Scene& scene, const std::string& name);

        /**
         * Destructor.
         */
        ~Entity();

        /**
         * Accessor for the scene that the entity is in.
         *
         * @return Reference to the scene that the entity is in.
         */
        Scene& scene() const;

        /**
         * Accessor for the name assigned to the entity.
         *
         * @return Name assigned to the entity.
         */
        const std::string& name() const;

        /**
         * Checks whether the entity has been marked for destruction.
         *
         * @return True if the entity has been marked for destruction, false otherwise.
         */
        bool dead() const;

        /**
         * Checks whether the entity has NOT been marked for destruction.
         *
         * @return True if the entity has NOT been marked for destruction, false otherwise.
         */
        bool alive() const;

        /**
         * Marks the entity for destruction.
         *
         * @note Destruction is delayed until after all of the entities in the scene have been updated.
         */
        void destroy();

        /**
         * Adds the entity to the group specified by the provided `group_name`.
         *
         * @param group_name Name of the group that the entity should be added to.
         */
        void add_to_group(const std::string& group_name);

        /**
         * Removes the entity from the group specified by the provided `group_name`.
         *
         * @param group_name Name of the group that the entity should be removed from.
         */
        void remove_from_group(const std::string& group_name);

        /**
         * Checks whether the entity has any children.
         *
         * @return True if the entity has one or more children, false otherwise.
         */
        bool has_children() const;

        /**
         * Checks whether the entity is the child of another entity.
         *
         * @return True if the entity is the child of another entity, false otherwise.
         */
        bool has_parent() const;

        /**
         * Creates and attaches an entity as the child of this entity.
         *
         * Sets the child entity's name to the empty string.
         *
         * @return Pointer to the entity that was created and attached as a child.
         */
        WatchPtr<Entity> create_child();

        /**
         * Creates and attaches an entity as the child of this entity.
         *
         * @param name Name to assign to the child entity.
         * @return Pointer to the entity that was created and attached as a child.
         */
        WatchPtr<Entity> create_child(const std::string& name);

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
        WatchPtr<AttributeType> create_attribute()
        {
            AttributeType* attribute_ptr = new AttributeType();
            const std::string attribute_name = component_registry().component_name<AttributeType>();
            m_attributes[attribute_name].push_back(std::unique_ptr<AttributeType>(attribute_ptr));

            attribute_ptr->m_entity = this;
            attribute_ptr->create();
            return WatchPtr<AttributeType>(attribute_ptr);
        }

        /**
         * Creates and attaches an attribute of the type specified by `class_name` to the entity and returns a pointer
         * to the created attribute.
         *
         * @param class_name Class name for the attribute to be created and attached.
         * @return Pointer to the attribute that was created and attached.
         */
        suborbital::WatchPtr<suborbital::Attribute> create_attribute(const std::string& class_name);

        /**
         * Returns a pointer to the attached attribute with the specified type. If multiple attributes of the specified
         * type are attached then the first such attribute is returned.
         *
         * @note The caller is NOT responsible for managing the lifetime of the returned behaviour.
         *
         * @return Pointer to the first attached attribute with the specified type.
         */
        template<typename AttributeType>
        WatchPtr<AttributeType> attribute()
        {
            const std::string attribute_name = component_registry().component_name<AttributeType>();
            auto iter = m_behaviours.find(attribute_name);
            assert(iter != m_behaviours.end());
            assert(!iter->second.empty());

            AttributeType* attribute_ptr = dynamic_cast<AttributeType*>(iter->second.front().get());
            assert(attribute_ptr != nullptr);
            return WatchPtr<AttributeType>(attribute_ptr);
        }

        /**
         * Returns a pointer the attached attribute with the specified class name. If multiple attributes of type
         * specified by `class_name` are attached then the first such attribute is returned.
         *
         * @param class_name Class name for the attribute to be returned.
         * @return Pointer to the first attached attribute with the specified class name.
         */
        suborbital::WatchPtr<suborbital::Attribute> attribute(const std::string& class_name) const;

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
         * @note The caller is NOT responsible for managing the lifetime of the returned behaviour.
         *
         * @param class_name Class name for the behaviour to be created and attached.
         */
        void create_behaviour(const std::string& class_name);

        /**
         * Publishes an event to be dispatched to all subscribers of the specified `event_name` on this entity.
         *
         * The event must be passed as a shared pointer to the event. This is because we make no assumption about how
         * subscribers may choose to use the event. For instance, we cannot guarantee that subscribers will not make
         * use of the event beyond the lifetime of their callback function.
         *
         * @param event_name Name of the event to publish.
         * @param Shared pointer to the event to be published.
         */
        void publish(const std::string& event_name, std::shared_ptr<suborbital::Event> event);

        /**
         * Broadcasts an event to all descendant entities (not including this entity).
         *
         * The event must be passed as a shared pointer to the event. This is because we make no assumption about how
         * subscribers may choose to use the event. For instance, we cannot guarantee that subscribers will not make
         * use of the event beyond the lifetime of their callback function.
         *
         * @param event_name Name of the event to broadcast.
         * @param Shared pointer to the event to be broadcast.
         */
        void broadcast_descendents(const std::string& event_name, std::shared_ptr<suborbital::Event> event);

        /**
         * Broadcasts an event to this entity and all descendant entities.
         *
         * The event must be passed as a shared pointer to the event. This is because we make no assumption about how
         * subscribers may choose to use the event. For instance, we cannot guarantee that subscribers will not make
         * use of the event beyond the lifetime of their callback function.
         *
         * @param event_name Name of the event to broadcast.
         * @param Shared pointer to the event to be broadcast.
         */
        void broadcast(const std::string& event_name, std::shared_ptr<suborbital::Event> event);

        /**
         * Subscribes to receive events of the specified `event_name`.
         *
         * The `EventSubscription` object returned manages the lifetime of the subscription. The subscription is
         * cancelled automatically once the object goes out of scope. Alternatively, it is possible to manually cancel
         * the subscription using the function provided by the `EventSubscription` class.
         *
         * @param event_name Name of the event to subscribe for.
         * @param callback Callback function that should receive the events.
         * @return Subscription object that controls the lifetime of the subscription.
         */
        std::unique_ptr<suborbital::EventSubscription> subscribe(const std::string& event_name,
                std::unique_ptr<suborbital::EventCallbackBase> callback);

    private:
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
         * Scene that the entity is in.
         */
        Scene& m_scene;

        /**
         * Name assigned to the entity.
         */
        const std::string m_name;

        /**
         * Whether the entity has been marked for destruction.
         */
        bool m_dead;

        /**
         * Parent entity (will be a nullptr if the entity has no parent).
         */
        WatchPtr<Entity> m_parent;

        /**
         * Child entities.
         */
        std::vector<std::unique_ptr<Entity>> m_children;

        /**
         * Event dispatcher for the entity.
         */
        std::shared_ptr<EventDispatcher> m_event_dispatcher;

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