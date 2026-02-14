#include "ScriptEngine.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>

namespace IsometricMUD {

ScriptEngine::ScriptEngine() {
    // Register built-in functions
    registerFunction("Print", [](ScriptEngine& engine, const std::vector<ScriptVariable>& args) {
        for (const auto& arg : args) {
            if (arg.type == ScriptVariable::Type::STRING) {
                std::cout << arg.stringValue;
            } else if (arg.type == ScriptVariable::Type::INT) {
                std::cout << arg.intValue;
            } else if (arg.type == ScriptVariable::Type::FLOAT) {
                std::cout << arg.floatValue;
            } else if (arg.type == ScriptVariable::Type::BOOL) {
                std::cout << (arg.boolValue ? "true" : "false");
            }
        }
        std::cout << std::endl;
    });
}

ScriptEngine::~ScriptEngine() {
}

bool ScriptEngine::loadScript(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open script file: " << filename << std::endl;
        return false;
    }
    
    std::stringstream buffer;
    buffer << file.rdbuf();
    return parseScript(buffer.str());
}

bool ScriptEngine::parseScript(const std::string& source) {
    std::istringstream stream(source);
    std::string line;
    
    ScriptFunctionDef* currentFunction = nullptr;
    
    while (std::getline(stream, line)) {
        // Remove leading/trailing whitespace
        line.erase(0, line.find_first_not_of(" \t\r\n"));
        line.erase(line.find_last_not_of(" \t\r\n") + 1);
        
        // Skip empty lines and comments
        if (line.empty() || line[0] == ';') {
            continue;
        }
        
        // Check for function definition (Event or Function keyword)
        if (line.find("Event ") == 0 || line.find("Function ") == 0) {
            size_t nameStart = line.find(' ') + 1;
            size_t nameEnd = line.find('(');
            
            if (nameEnd != std::string::npos) {
                ScriptFunctionDef func;
                func.name = line.substr(nameStart, nameEnd - nameStart);
                
                scriptFunctions[func.name] = func;
                currentFunction = &scriptFunctions[func.name];
            }
        } else if (line == "EndEvent" || line == "EndFunction") {
            currentFunction = nullptr;
        } else if (currentFunction) {
            currentFunction->body.push_back(line);
        }
    }
    
    return true;
}

bool ScriptEngine::executeFunction(const std::string& functionName, const std::vector<ScriptVariable>& args) {
    // Check native functions first
    auto nativeIt = nativeFunctions.find(functionName);
    if (nativeIt != nativeFunctions.end()) {
        nativeIt->second(*this, args);
        return true;
    }
    
    // Check script functions
    auto scriptIt = scriptFunctions.find(functionName);
    if (scriptIt != scriptFunctions.end()) {
        for (const auto& line : scriptIt->second.body) {
            executeLine(line);
        }
        return true;
    }
    
    std::cerr << "Function not found: " << functionName << std::endl;
    return false;
}

void ScriptEngine::registerFunction(const std::string& name, ScriptFunction func) {
    nativeFunctions[name] = func;
}

void ScriptEngine::setVariable(const std::string& name, const ScriptVariable& value) {
    variables[name] = value;
}

ScriptVariable ScriptEngine::getVariable(const std::string& name) const {
    auto it = variables.find(name);
    if (it != variables.end()) {
        return it->second;
    }
    return ScriptVariable();
}

void ScriptEngine::executeLine(const std::string& line) {
    // Simple command parsing
    if (line.find("Print(") == 0) {
        size_t start = line.find('"');
        size_t end = line.rfind('"');
        if (start != std::string::npos && end != std::string::npos && start < end) {
            std::string text = line.substr(start + 1, end - start - 1);
            ScriptVariable arg;
            arg.type = ScriptVariable::Type::STRING;
            arg.stringValue = text;
            executeFunction("Print", {arg});
        }
    }
    // Add more command parsing as needed
}

} // namespace IsometricMUD
