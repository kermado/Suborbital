#ifndef SUBORBITAL_PYTHON_INTERPRETER_HPP
#define SUBORBITAL_PYTHON_INTERPRETER_HPP

#include <string>
#include <set>

#include <suborbital/ScriptInterpreter.hpp>

namespace suborbital
{
    class Behaviour;

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

    private:
        /**
         * List of search paths to explore when attempting to find scripts.
         */
        std::set<std::string> m_search_paths;
    };
}

#endif