#include <iostream>

#include "HelperFunctions.h"

#include <scriptbuilder/scriptbuilder.h>

void print(const std::string& in)
{
	std::cout << in;
}

int main()
{
	std::cout << "Output\n";

	scrpt::function();

	std::cout << "Doing angelscript stuff now:\n";

	auto* engine = scrpt::getScriptEngine();

	int result = engine->RegisterGlobalFunction("void print(const string &in)", asFUNCTION(print), asCALL_CDECL);
	//assert(result >= 0);

	CScriptBuilder builder;
	result = builder.StartNewModule(engine, "TestingModule");
	if(result < 0)
	{
		std::cout << "Failed to start new module\n";
		return 0;
	}

	result = builder.AddSectionFromFile("TestScripts/test.as");
	if(result < 0)
	{
		std::cout << "There was an error in the script\n";
		return 0;
	}

	result = builder.BuildModule();
	if(result < 0)
	{
		std::cout << "There was an error in the script\n";
		return 0;
	}

	asIScriptModule* testingModule = engine->GetModule("TestingModule");

	asIScriptFunction* scriptFunction = testingModule->GetFunctionByDecl("void main()");

	if(scriptFunction == 0) // == 0 or nullptr or whatever
	{
		std::cout << "Script function 'void main()' could not be loaded/found\n";
	}

	//Prepare Script context
	asIScriptContext* context = engine->CreateContext();
	context->Prepare(scriptFunction);

	result = context->Execute();

	if(result != asEXECUTION_FINISHED)
	{
		//The execution didn't complete as expected
		if(result == asEXECUTION_EXCEPTION)
		{
			std::cout << "An exception " << std::string(context->GetExceptionString()) << " occurred. "
				<< "Please correct the code and try again" << std::endl;
		}
	}

	//Clean up
	context->Release();
	engine->ShutDownAndRelease();

	
	return 0;
}
