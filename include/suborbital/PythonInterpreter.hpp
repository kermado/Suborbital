#ifndef PYTHONINTERPRETER_HPP
#define PYTHONINTERPRETER_HPP

#include <string>
#include <memory>
#include <set>

#include <suborbital/ScriptInterpreter.hpp>

namespace suborbital
{
    namespace behaviour
    {
        class Behaviour;
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
        * Creates a new behaviour from the script specified by the provided `class_name`.
        *
        * @param class_name Name of the class from which to create the behaviour.
        * @return Unique pointer to the created behaviour.
        */
        std::unique_ptr<behaviour::Behaviour> create(const std::string& class_name) const;

    private:
        /**
        * List of search paths to explore when attempting to find scripts.
        */
        std::set<std::string> m_search_paths;
    };
}

#endif