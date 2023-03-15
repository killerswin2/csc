

#include "script.hpp"

int compile_script(std::string& file)
{
	AngelScript::Engine engine;
	auto sEngine = engine.get_script_engine();
	return sEngine->compile_script(file);
}

int runApplication()
{
	AngelScript::Engine engine;
	auto sEngine = engine.get_script_engine();
	//sEngine->compile_script(std::string("@csc/scripts/test.as"));
	sEngine->prepare_context(sEngine->find_function());
	sEngine->set_timeout();
	return sEngine->execute_context();

}

AngelScript::ScriptEngine::ScriptEngine()
{
	create_engine();
	config_engine();
	// use default here
	set_message_callback(asFUNCTION(messageCallback), 0, asCALL_CDECL);

	// compile scripts
	if (compile_script(std::string("@csc/scripts/test.as")) < 0)
	{
		engine->Release();
	}
	create_context();
	// use default here
	set_line_callback(asFUNCTION(lineCallback), &timeOut, asCALL_CDECL);
	//asIScriptFunction *func= find_function();
	prepare_context(find_function());
	set_timeout();

	std::cout << "ctx address: " << this->ctx << "\n";
	std::cout << "engine address: " << this->engine << "\n";
}

AngelScript::ScriptEngine::~ScriptEngine()
{
	// release context
	ctx->Release();
	// shut down engine
	engine->ShutDownAndRelease();
}

//@TODO this is needs to be done at prestart.
void AngelScript::ScriptEngine::config_engine()
{
	int retCode;

	RegisterStdString(engine);
	RegisterScriptArray(engine, true);
	if (!strstr(asGetLibraryOptions(), "AS_MAX_PORTABILITY"))
	{
		retCode = engine->SetDefaultNamespace("sqf"); assert(retCode >= 0);
		retCode = engine->RegisterGlobalFunction("void system_chat(string &in)", asFUNCTION(system_chat), asCALL_CDECL); assert(retCode >= 0);
	}
	else
	{
		retCode = engine->SetDefaultNamespace("sqf"); assert(retCode >= 0);
		retCode = engine->RegisterGlobalFunction("void system_chat(string &in)", asFUNCTION(system_chat_generic), asCALL_GENERIC); assert(retCode >= 0);
	}
	register_wrapper_functions_diag(engine);
	register_vectors(engine);

}

int AngelScript::ScriptEngine::create_engine()
{
#ifdef DEBUG_CONSOLE
	AllocConsole();
	FILE* fp = new FILE();
	freopen_s(&fp, "CONOUT$", "w", stdout);
#endif // DEBUG_CONSOLE
	//create engine
	this->engine = asCreateScriptEngine();
	if (!engine)
	{
		// engine failed to be created.
#ifdef DEBUG_CONSOLE
		std::cout << "Failed to create script engine\n";
#endif // DEBUG_CONSOLE
		return -1;
	}
	return 0;
}

int AngelScript::ScriptEngine::set_message_callback(const asSFuncPtr& callback, void* obj, asDWORD callConv)
{
	int retCode;
	retCode = engine->SetMessageCallback(callback, obj, callConv);
	assert(retCode >= 0);
	return retCode;
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
int AngelScript::ScriptEngine::compile_script(const std::string& filepath)
{
	int retCode;

	CScriptBuilder builder;

	retCode = builder.StartNewModule(this->engine, 0);
	if (retCode < 0)
	{
		std::cout << "Failed to start new module\n";
		return retCode;
	}

	// file
	retCode = builder.AddSectionFromFile(filepath.c_str());
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


int AngelScript::ScriptEngine::create_context()
{
	// engine context, executes scripts
	ctx = engine->CreateContext();
	if (ctx == nullptr)
	{
		std::cout << "Failed to create the context\n";
		engine->Release();
		return -1;
	}
	return 0;
}

int AngelScript::ScriptEngine::set_line_callback(asSFuncPtr callback, void* obj, int callConv)
{
	int retCode;
	// prevent infinite loops
	retCode = ctx->SetLineCallback(callback, obj, callConv);
	if (retCode < 0)
	{
		std::cout << "Failed to set line callback func\n";
		ctx->Release();
		engine->Release();
		return -1;
	}
	return 0;
}

// find function, get pointer to it
asIScriptFunction* AngelScript::ScriptEngine::find_function()
{
	asIScriptFunction* func = engine->GetModule(0)->GetFunctionByDecl("void main()");
	if (!func)
	{
		std::cout << "The function was not found.\n";
		ctx->Release();
		engine->Release();
		return nullptr;
	}
	return std::move(func);
}

int AngelScript::ScriptEngine::prepare_context(asIScriptFunction* func)
{
	int retCode;
	// prepare the script context with the function that we want to exec
	retCode = ctx->Prepare(func);
	if (retCode < 0)
	{
		std::cout << "failed to prepare context\n";
		ctx->Release();
		engine->Release();
		return -1;
	}
	return 0;
}

int AngelScript::ScriptEngine::set_timeout()
{
	timeOut = timeGetTime() + 1000;
	return 0;
}

int AngelScript::ScriptEngine::execute_context()
{
	int retCode;
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
	return 0;
}


AngelScript::ScriptEngine* AngelScript::Engine::scriptEngine = new AngelScript::ScriptEngine;

void system_chat(std::string& str)
{
	std::cout << str << "\n";
	//intercept::sqf::system_chat(str);
}

void system_chat_generic(asIScriptGeneric* gen)
{
	std::string* str = static_cast<std::string*>(gen->GetArgAddress(0));
	std::cout << *str << "\n";
	intercept::sqf::system_chat(*str);
}

void lineCallback(asIScriptContext *& ctx, DWORD *timeOut)
{
	if (*timeOut < timeGetTime())
	{
		//ctx->Abort();
	}
}


game_value testAngelScript()
{
	game_value retCode = runApplication();
	return retCode;
}

game_value compileAngelScript()
{
	game_value retCode = compile_script(std::string("@csc/scripts/test.as"));
	return retCode;
}

void AngelScript::pre_start()
{
	Commands& commands = Commands::get();
	commands.addCommand("testAngel", "test AngelScripting", userFunctionWrapper<testAngelScript>, game_data_type::SCALAR);
	commands.addCommand("compileAngelScript", "compile AngelScript", userFunctionWrapper<compileAngelScript>, game_data_type::SCALAR);
}