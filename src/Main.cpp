#include <iostream>

#include "HelperFunctions.h"

int main()
{
	std::cout << "Output\n";

	scrpt::function();

	std::cout << "Doing angelscript stuff now:\n";

	auto* engine = scrpt::getScriptEngine();


	scrpt::createModule("TestingModule", "TestScripts/test.as");

	asIScriptModule* testingModule = engine->GetModule("TestingModule");

	asIScriptFunction* scriptFunction = testingModule->GetFunctionByDecl("void main()");

	if(scriptFunction == 0) // == 0 or nullptr or whatever
	{
		std::cout << "Script function 'void main()' could not be loaded/found\n";
	}

	//Prepare Script context
	asIScriptContext* context = engine->CreateContext();
	context->Prepare(scriptFunction);

	int result = context->Execute();

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
