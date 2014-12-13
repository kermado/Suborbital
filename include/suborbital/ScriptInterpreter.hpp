#ifndef SCRIPTINTERPRETER_HPP
#define SCRIPTINTERPRETER_HPP

#include <string>
#include <memory>

#include <suborbital/NonCopyable.hpp>

namespace suborbital
{
    namespace component
    {
        class Component;
    }

    class ScriptInterpreter : private NonCopyable
    {
    public:
        /**
         * Constructor.
         */
        ScriptInterpreter();

        /**
         * Destructor.
         */
        virtual ~ScriptInterpreter();

        /**
         * Adds the specified path to the list of script search paths.
         *
         * @param path Path to add
         */
        virtual void add_path(const std::string& path) = 0;

        /**
         * Creates a new component from the script specified by the provided `class_name`.
         *
         * @param class_name Name of the class from which to create the component.
         * @return Unique pointer to the created component.
         */
        virtual std::unique_ptr<component::Component> create(const std::string& class_name) const = 0;
    };
}

#endif