#ifndef PYTHONINTERPRETER_HPP
#define PYTHONINTERPRETER_HPP

#include <string>
#include <memory>
#include <set>

#include <suborbital/ScriptInterpreter.hpp>

namespace suborbital
{
    namespace component
    {
        class Component;
    }

    class PythonInterpreter : public ScriptInterpreter
    {
    public:
        /**
        * Constructor.
        */
        PythonInterpreter();

        /**
        * Destructor.
        */
        ~PythonInterpreter();

        /**
        * Adds the specified path to the list of script search paths.
        *
        * @param path Path to add
        */
        void add_path(const std::string& path);

        /**
        * Creates a new component from the script specified by the provided `class_name`.
        *
        * @param class_name Name of the class from which to create the component.
        * @return Unique pointer to the created component.
        */
        std::unique_ptr<component::Component> create(const std::string& class_name) const;

    private:
        /**
        * List of search paths to explore when attempting to find scripts.
        */
        std::set<std::string> m_search_paths;
    };
}

#endif