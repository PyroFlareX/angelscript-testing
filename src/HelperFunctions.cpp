#include "HelperFunctions.h"

#include <iostream>
#include <cassert>

#include <scriptstdstring/scriptstdstring.h>
#include <scriptbuilder/scriptbuilder.h>

///Some global helper functions for angel script use inside the scripts
//Prints to standard output
void print(const std::string& in)
{
	std::cout << in;
}



//Message Callback Function for Scripting
void MessageCallback(const asSMessageInfo *msg, void *param)
{
	const char *type = "ERR ";
	if( msg->type == asMSGTYPE_WARNING ) 
		type = "WARN";
	else if( msg->type == asMSGTYPE_INFORMATION ) 
		type = "INFO";

	printf("%s (%d, %d) : %s : %s\n", msg->section, msg->row, msg->col, type, msg->message);
}

namespace scrpt
{
	void function()
	{
		std::cout << "Test Function!\n";
	}
	
	asIScriptEngine* getScriptEngine()
	{
		static asIScriptEngine* engine = nullptr;
		static bool firstRun = true;

		if(firstRun)
		{
			firstRun = false;

			engine = asCreateScriptEngine();

			int r = engine->SetMessageCallback(asFUNCTION(MessageCallback), 0, asCALL_CDECL); 
			assert( r >= 0 );

			RegisterStdString(engine);

			r = engine->RegisterGlobalFunction("void print(const string &in)", asFUNCTION(print), asCALL_CDECL);
			assert( r >= 0 );

			std::cout << "Created script engine\n";
		}

		return engine;
	}

	void createModule(const std::string& moduleName, const std::string& moduleFile)
	{
		auto* engine = getScriptEngine();

		CScriptBuilder builder;

		int result = builder.StartNewModule(engine, moduleName.c_str());
		if(result < 0)
		{
			std::cout << "Failed to start new module!\n";
			return;
		}

		result = builder.AddSectionFromFile(moduleFile.c_str());
		if(result < 0)
		{
			std::cout << "There was an error in the script while adding file to module\n";
			return;
		}

		result = builder.BuildModule();
		if(result < 0)
		{
			std::cout << "There was an error in the script while building the module\n";
			return;
		}

		std::cout << "Successfully Built Module " << moduleName << "\n";
	}

		
} // namespace scrpt
