#pragma once

#include <string>
#include <angelscript.h>

namespace scrpt
{
	void function();

	asIScriptEngine* getScriptEngine();

	void createModule(const std::string& moduleName, const std::string& moduleFile);


} // namespace scrpt

