#pragma once

#include <string>
#include <map>
#include <vector>
#include <memory>
#include <functional>

namespace IsometricMUD {

class ScriptEngine;

/**
 * @brief Base class for script objects
 */
class ScriptObject {
public:
    virtual ~ScriptObject() = default;
    
    std::string getName() const { return name; }
    void setName(const std::string& n) { name = n; }

protected:
    std::string name;
};

/**
 * @brief Script variable
 */
struct ScriptVariable {
    enum class Type { INT, FLOAT, STRING, BOOL };
    
    Type type;
    union {
        int intValue;
        float floatValue;
        bool boolValue;
    };
    std::string stringValue;
    
    ScriptVariable() : type(Type::INT), intValue(0) {}
};

/**
 * @brief Script function
 */
using ScriptFunction = std::function<void(ScriptEngine&, const std::vector<ScriptVariable>&)>;

/**
 * @brief Papyrus-like scripting engine
 */
class ScriptEngine {
public:
    ScriptEngine();
    ~ScriptEngine();

    /**
     * @brief Load and parse a script file
     */
    bool loadScript(const std::string& filename);

    /**
     * @brief Execute a script function
     */
    bool executeFunction(const std::string& functionName, const std::vector<ScriptVariable>& args = {});

    /**
     * @brief Register a native function
     */
    void registerFunction(const std::string& name, ScriptFunction func);

    /**
     * @brief Set a script variable
     */
    void setVariable(const std::string& name, const ScriptVariable& value);

    /**
     * @brief Get a script variable
     */
    ScriptVariable getVariable(const std::string& name) const;

    /**
     * @brief Parse script source code
     */
    bool parseScript(const std::string& source);

private:
    struct ScriptFunctionDef {
        std::string name;
        std::vector<std::string> parameters;
        std::vector<std::string> body;
    };

    std::map<std::string, ScriptVariable> variables;
    std::map<std::string, ScriptFunction> nativeFunctions;
    std::map<std::string, ScriptFunctionDef> scriptFunctions;
    
    void executeLine(const std::string& line);
};

} // namespace IsometricMUD
