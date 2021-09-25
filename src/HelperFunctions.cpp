#include "HelperFunctions.h"

#include <iostream>
#include <cassert>

#include <scriptstdstring/scriptstdstring.h>
#include <scriptbuilder/scriptbuilder.h>

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
		}

		return engine;
	}
		
} // namespace scrpt
