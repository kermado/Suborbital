#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <cassert>
#include <string>
#include <memory>
#include <unordered_map>
#include <vector>
#include <iostream>

#include <suborbital/NonCopyable.hpp>
#include <suborbital/behaviour/Behaviour.hpp>

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
         * Checks whether the entity has a behaviour with the type attached.
         *
         * @return True if a behaviour with the specified type is owned by the entity, false otherwise.
         */
        template<typename BehaviourType>
        bool has_behaviour() const
        {
            const std::string behaviour_name = behaviour::name<BehaviourType>();
            auto iter = m_behaviours.find(behaviour_name);
            if (iter != m_behaviours.end())
            {
                auto& behaviours = iter->second;
                if (!behaviours.empty())
                {
                    BehaviourType*behaviour_ptr = dynamic_cast<BehaviourType*>( behaviours.front().get());
                    return behaviour_ptr != nullptr;
                }
            }

            return false;
        }

        /**
         * Checks whether the entity has a behaviour with the specified class name attached.
         *
         * This function is intended to be called from within scripts. Users of the c++ API should use the templated
         * function provided.
         *
         * @param Class name for the behaviour.
         * @return True if a behaviour with the specified class name is owned by the entity, false otherwise.
         */
        bool has_behaviour(const std::string& class_name) const;

        /**
         * Attaches a behaviour of the specified type to the entity and returns a pointer to the created behaviour.
         *
         * @note The caller is NOT responsible for managing the lifetime of the returned behaviour.
         *
         * @return Pointer to the behaviour that was created and attached.
         */
        template<typename BehaviourType>
        BehaviourType* create_behaviour()
        {
            BehaviourType*specific_behaviour_ptr = new BehaviourType();
            const std::string behaviour_name = behaviour::name<BehaviourType>();
            m_behaviours[behaviour_name].push_back(std::unique_ptr<BehaviourType>(specific_behaviour_ptr));
            specific_behaviour_ptr->m_entity = this;
            specific_behaviour_ptr->create();
            return specific_behaviour_ptr;
        }

        /**
         * Attaches a behaviour of type specified by `class_name` to the entity and returns a pointer to the created
         * behaviour.
         *
         * This function is intended to be called from within scripts. Users of the c++ API should use the templated
         * function provided.
         *
         * @note The caller is NOT responsible for managing the lifetime of the returned behaviour.
         *
         * @param class_name Class name for the behaviour to be created and attached.
         * @return Pointer to the behaviour that was created and attached.
         */
        suborbital::behaviour::Behaviour* create_behaviour(const std::string& class_name);

        /**
         * Returns a pointer to the attached behaviour with the specified type. If multiple behaviours of the specified
         * type are attached then the first such behaviour is returned.
         *
         * @note The caller is NOT responsible for managing the lifetime of the returned behaviour.
         *
         * @return Pointer to the first attached behaviour with the specified type.
         */
        template<typename BehaviourType>
        BehaviourType* behaviour()
        {
            const std::string behaviour_name = behaviour::name<BehaviourType>();
            auto iter = m_behaviours.find(behaviour_name);
            assert(iter != m_behaviours.end());
            assert(!iter->second.empty());

            BehaviourType*behaviour_ptr = dynamic_cast<BehaviourType*>(iter->second.front().get());
            assert(behaviour_ptr != nullptr);
            return behaviour_ptr;
        }

        /**
         * Returns a pointer to the attached behaviour with the specified class name. If multiple behaviours of type
         * specified by `class_name` are attached then the first such behaviour is returned.
         *
         * This function is intended to be called from within scripts. Users of the c++ API should use the templated
         * function provided, which attempts to safely cast the requested behaviour to the specified type.
         *
         * @note The caller is NOT responsible for managing the lifetime of the returned behaviour.
         *
         * @param class_name Class name for the behaviour to be returned.
         * @return Pointer to the first attached behaviour with the specified class name.
         */
        suborbital::behaviour::Behaviour* behaviour(const std::string& class_name) const;

    protected:
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
         * Behaviours attached to the entity, indexed by class name.
         *
         * We store unique_ptr's here so that the behaviours attached to an entity are automatically deleted when the
         * entity is deleted.
         */
        std::unordered_map<std::string, std::vector<std::unique_ptr<behaviour::Behaviour>>> m_behaviours;
    };
}

#endif