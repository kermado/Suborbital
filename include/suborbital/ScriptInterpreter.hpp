#ifndef SUBORBITAL_SCRIPT_INTERPRETER_HPP
#define SUBORBITAL_SCRIPT_INTERPRETER_HPP

#include <string>

#include <suborbital/NonCopyable.hpp>

namespace suborbital
{
    // Forward declarations.
    class Behaviour;

    /**
     * The base class for script interpreter managers that manage the startup and shutdown of scripting language
     * interpreters.
     */
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
         * @param path Path to add.
         */
        virtual void add_path(const std::string& path) = 0;
    };
}

#endif