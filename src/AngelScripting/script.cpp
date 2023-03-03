

#include "script.hpp"


int runApplication()
{
	int retCode;
#ifdef DEBUG_CONSOLE
	AllocConsole();
	FILE* fp = new FILE();
	freopen_s(&fp, "CONOUT$", "w", stdout);
#endif // DEBUG_CONSOLE
	//create engine
	asIScriptEngine* engine = asCreateScriptEngine();
	if (!engine)
	{
		// engine failed to be created.
#ifdef DEBUG_CONSOLE
		std::cout << "Failed to create script engine\n";
#endif // DEBUG_CONSOLE
		return -1;
	}

	retCode = engine->SetMessageCallback(asFUNCTION(messageCallback), 0, asCALL_CDECL);
	assert(retCode >= 0);

	configureEngine(engine);

	// compile scripts
	retCode = compileScript(engine);
	if(retCode < 0) 
	{
		engine->Release();
		return -1;
	}

	// engine context, executes scripts
	asIScriptContext* ctx = engine->CreateContext();
	if (ctx == 0)
	{
		std::cout << "Failed to create the context\n";
		engine->Release();
		return -1;
	}

	// prevent infinite loops
	DWORD timeOut;
	retCode = ctx->SetLineCallback(asFUNCTION(lineCallback), &timeOut, asCALL_CDECL);
	if (retCode < 0)
	{
		std::cout << "Failed to set line callback func\n";
		ctx->Release();
		engine->Release();
		return -1;
	}

	// find function, get pointer to it
	asIScriptFunction* func = engine->GetModule(0)->GetFunctionByDecl("void main()");
	if (!func)
	{
		std::cout << "The function was not found.\n";
		ctx->Release();
		engine->Release();
		return -1;
	}

	// prepare the script context with the function that we want to exec
	retCode = ctx->Prepare(func);
	if (retCode < 0)
	{
		std::cout << "failed to prepare context\n";
		ctx->Release();
		engine->Release();
		return -1;
	}

	//set timeout for script execution
	timeOut = timeGetTime() + 1000;

	// now the fun part. Execute the function
	retCode = ctx->Execute();

	// error checking
	if (retCode != asEXECUTION_FINISHED)
	{
		if (retCode == asEXECUTION_ABORTED)
		{
			std::cout << "script was aborted\n";
		}
		else if (retCode == asEXECUTION_EXCEPTION)
		{
			std::cout << "The script ended with an exception\n";
		
			// write out info to find the exception
			asIScriptFunction* funcEx = ctx->GetExceptionFunction();
			std::cout << "func: " << funcEx->GetDeclaration() << "\n";
			std::cout << "modl: " << funcEx->GetModuleName() << "\n";
			std::cout << "sect: " << funcEx->GetScriptSectionName() << "\n";
			std::cout << "line: " << ctx->GetExceptionLineNumber() << "\n";
			std::cout << "desc: " << ctx->GetExceptionString() << "\n";
		}
		else
		{
			std::cout << "Script ended for some unknown reason(" << retCode << ").\n";
		}
	}
	else
	{
		std::cout << "Script finished\n";
	}
	
	// release context
	ctx->Release();
	// shut down engine
	engine->ShutDownAndRelease();

	return 0;
}

void configureEngine(asIScriptEngine*& engine)
{
	int retCode;

	RegisterStdString(engine);
	if (!strstr(asGetLibraryOptions(), "AS_MAX_PORTABILITY"))
	{
		retCode = engine->RegisterGlobalFunction("void print(string &in)", asFUNCTION(printString), asCALL_CDECL);
		assert(retCode >= 0);
	}
	else
	{
		retCode = engine->RegisterGlobalFunction("void print(string &in)", asFUNCTION(printString_Generic), asCALL_GENERIC); assert(retCode >= 0);
	}
}

void messageCallback(const asSMessageInfo* msg, void* param)
{
	const char* type = "ERR";
	if (msg->type == asMSGTYPE_WARNING)
	{
		type = "warning";
	}
	else if (msg->type == asMSGTYPE_INFORMATION)
	{
		type = "INFO";
	}
#ifdef DEBUG_CONSOLE
	printf("%s (%d, %d) : %s : %s\n", msg->section, msg->row, msg->col, type, msg->message);
#endif // DEBUG_CONSOLE
}

//compiles scripts
int compileScript(asIScriptEngine*& engine)
{
	int retCode;

	CScriptBuilder builder;

	retCode = builder.StartNewModule(engine, 0);
	if (retCode < 0)
	{
		// std::cout << "Failed to start new module\n";
		return retCode;
	}

	// file
	retCode = builder.AddSectionFromFile("@csc/scripts/test.as");
	if (retCode < 0)
	{
		return retCode;
	}

	// build mod
	retCode = builder.BuildModule();
	if (retCode < 0)
	{
		return retCode;
	}

	return 0;
}


void printString(std::string& str)
{
	//std::cout << str << "\n";
	intercept::sqf::system_chat(str);
}

void printString_Generic(asIScriptGeneric* gen)
{
	std::string* str = static_cast<std::string*>(gen->GetArgAddress(0));
	//std::cout << *str << "\n";
	intercept::sqf::system_chat(*str);
}

void lineCallback(asIScriptContext *& ctx, DWORD *timeOut)
{
	if (*timeOut < timeGetTime())
	{
		ctx->Abort();
	}
}


game_value testAngelScript()
{
	game_value retCode = runApplication();
	return retCode;
}

void AngelScript::pre_start()
{
	Commands& commands = Commands::get();
	commands.addCommand("testAngel", "test AngelScripting", userFunctionWrapper<testAngelScript>, game_data_type::SCALAR);
}