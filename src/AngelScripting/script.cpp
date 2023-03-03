

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

//@TODO this is needs to be done at prestart.
void configureEngine(asIScriptEngine*& engine)
{
	int retCode;

	RegisterStdString(engine);
	if (!strstr(asGetLibraryOptions(), "AS_MAX_PORTABILITY"))
	{
		retCode = engine->SetDefaultNamespace("sqf"); assert(retCode >= 0);
		retCode = engine->RegisterGlobalFunction("void system_chat(string &in)", asFUNCTION(system_chat), asCALL_CDECL); assert(retCode >= 0);
		
		retCode = engine->SetDefaultNamespace("sqf::diag"); assert(retCode >= 0);
		retCode = engine->RegisterGlobalFunction("void active_mission_fsms(string &in)", asFUNCTION(system_chat), asCALL_CDECL); assert(retCode >= 0);
		retCode = engine->RegisterGlobalFunction("void active_scripts(string &in)", asFUNCTION(system_chat), asCALL_CDECL); assert(retCode >= 0);
		retCode = engine->RegisterGlobalFunction("void active_sqf_scripts(string &in)", asFUNCTION(system_chat), asCALL_CDECL); assert(retCode >= 0);
		retCode = engine->RegisterGlobalFunction("void active_sqs_scripts(string &in)", asFUNCTION(system_chat), asCALL_CDECL); assert(retCode >= 0);
		retCode = engine->RegisterGlobalFunction("void all_mission_eventhandlers(string &in)", asFUNCTION(system_chat), asCALL_CDECL); assert(retCode >= 0);
		retCode = engine->RegisterGlobalFunction("void capture_frame(string &in)", asFUNCTION(system_chat), asCALL_CDECL); assert(retCode >= 0);
		retCode = engine->RegisterGlobalFunction("void capture_frame_to_file(string &in)", asFUNCTION(system_chat), asCALL_CDECL); assert(retCode >= 0);
		retCode = engine->RegisterGlobalFunction("void captures_lowframe(string &in)", asFUNCTION(system_chat), asCALL_CDECL); assert(retCode >= 0);
		retCode = engine->RegisterGlobalFunction("void code_performance(string &in)", asFUNCTION(system_chat), asCALL_CDECL); assert(retCode >= 0);
		retCode = engine->RegisterGlobalFunction("void delta_time(string &in)", asFUNCTION(system_chat), asCALL_CDECL); assert(retCode >= 0);
		retCode = engine->RegisterGlobalFunction("void draw_mode(string &in)", asFUNCTION(system_chat), asCALL_CDECL); assert(retCode >= 0);
		retCode = engine->RegisterGlobalFunction("void dump_call_trace_to_log(string &in)", asFUNCTION(system_chat), asCALL_CDECL); assert(retCode >= 0);
		retCode = engine->RegisterGlobalFunction("void dump_script_assembly(string &in)", asFUNCTION(system_chat), asCALL_CDECL); assert(retCode >= 0);
		retCode = engine->RegisterGlobalFunction("void dump_terrain_synth(string &in)", asFUNCTION(system_chat), asCALL_CDECL); assert(retCode >= 0);
		retCode = engine->RegisterGlobalFunction("void dynamic_simulation_end(string &in)", asFUNCTION(system_chat), asCALL_CDECL); assert(retCode >= 0);
		retCode = engine->RegisterGlobalFunction("void dynamic_simulation_start(string &in)", asFUNCTION(system_chat), asCALL_CDECL); assert(retCode >= 0);
		retCode = engine->RegisterGlobalFunction("void enable(string &in)", asFUNCTION(system_chat), asCALL_CDECL); assert(retCode >= 0);
		retCode = engine->RegisterGlobalFunction("void enabled(string &in)", asFUNCTION(system_chat), asCALL_CDECL); assert(retCode >= 0);
		retCode = engine->RegisterGlobalFunction("void export_config(string &in)", asFUNCTION(system_chat), asCALL_CDECL); assert(retCode >= 0);
		retCode = engine->RegisterGlobalFunction("void export_terrain_svg(string &in)", asFUNCTION(system_chat), asCALL_CDECL); assert(retCode >= 0);
		retCode = engine->RegisterGlobalFunction("void fps(string &in)", asFUNCTION(system_chat), asCALL_CDECL); assert(retCode >= 0);
		retCode = engine->RegisterGlobalFunction("void fpsmin(string &in)", asFUNCTION(system_chat), asCALL_CDECL); assert(retCode >= 0);
		retCode = engine->RegisterGlobalFunction("void frameno(string &in)", asFUNCTION(system_chat), asCALL_CDECL); assert(retCode >= 0);
		retCode = engine->RegisterGlobalFunction("void get_terrain_grid(string &in)", asFUNCTION(system_chat), asCALL_CDECL); assert(retCode >= 0);
		retCode = engine->RegisterGlobalFunction("void get_terrain_height(string &in)", asFUNCTION(system_chat), asCALL_CDECL); assert(retCode >= 0);
		retCode = engine->RegisterGlobalFunction("void get_terrain_segment_offset(string &in)", asFUNCTION(system_chat), asCALL_CDECL); assert(retCode >= 0);
		retCode = engine->RegisterGlobalFunction("void light_new_load(string &in)", asFUNCTION(system_chat), asCALL_CDECL); assert(retCode >= 0);
		retCode = engine->RegisterGlobalFunction("void list(string &in)", asFUNCTION(system_chat), asCALL_CDECL); assert(retCode >= 0);
		retCode = engine->RegisterGlobalFunction("void log(string &in)", asFUNCTION(system_chat), asCALL_CDECL); assert(retCode >= 0);
		retCode = engine->RegisterGlobalFunction("void log_slow_frame(string &in)", asFUNCTION(system_chat), asCALL_CDECL); assert(retCode >= 0);
		retCode = engine->RegisterGlobalFunction("void merge_config_file(string &in)", asFUNCTION(system_chat), asCALL_CDECL); assert(retCode >= 0);
		retCode = engine->RegisterGlobalFunction("void record_turret_limits(string &in)", asFUNCTION(system_chat), asCALL_CDECL); assert(retCode >= 0);
		retCode = engine->RegisterGlobalFunction("void reset_shapes(string &in)", asFUNCTION(system_chat), asCALL_CDECL); assert(retCode >= 0);
		retCode = engine->RegisterGlobalFunction("void scope(string &in)", asFUNCTION(system_chat), asCALL_CDECL); assert(retCode >= 0);
		retCode = engine->RegisterGlobalFunction("void set_light_new(string &in)", asFUNCTION(system_chat), asCALL_CDECL); assert(retCode >= 0);
		retCode = engine->RegisterGlobalFunction("void set_terrain_height(string &in)", asFUNCTION(system_chat), asCALL_CDECL); assert(retCode >= 0);
		retCode = engine->RegisterGlobalFunction("void stack_trace(string &in)", asFUNCTION(system_chat), asCALL_CDECL); assert(retCode >= 0);
		retCode = engine->RegisterGlobalFunction("void tick_time(string &in)", asFUNCTION(system_chat), asCALL_CDECL); assert(retCode >= 0);
		retCode = engine->RegisterGlobalFunction("void toggle(string &in)", asFUNCTION(system_chat), asCALL_CDECL); assert(retCode >= 0);
		retCode = engine->RegisterGlobalFunction("void echo(string &in)", asFUNCTION(system_chat), asCALL_CDECL); assert(retCode >= 0);
		retCode = engine->RegisterGlobalFunction("void enable_diag_legend(string &in)", asFUNCTION(system_chat), asCALL_CDECL); assert(retCode >= 0);
		retCode = engine->RegisterGlobalFunction("void export_jip_messages(string &in)", asFUNCTION(system_chat), asCALL_CDECL); assert(retCode >= 0);
		retCode = engine->RegisterGlobalFunction("void get_terrain_info(string &in)", asFUNCTION(system_chat), asCALL_CDECL); assert(retCode >= 0);
		retCode = engine->RegisterGlobalFunction("void is_file_patching_enabled(string &in)", asFUNCTION(system_chat), asCALL_CDECL); assert(retCode >= 0);
		retCode = engine->RegisterGlobalFunction("void log_entities(string &in)", asFUNCTION(system_chat), asCALL_CDECL); assert(retCode >= 0);
		retCode = engine->RegisterGlobalFunction("void log_network(string &in)", asFUNCTION(system_chat), asCALL_CDECL); assert(retCode >= 0);
		retCode = engine->RegisterGlobalFunction("void log_network_terminate(string &in)", asFUNCTION(system_chat), asCALL_CDECL); assert(retCode >= 0);
		retCode = engine->RegisterGlobalFunction("void set_custom_mission_data(string &in)", asFUNCTION(system_chat), asCALL_CDECL); assert(retCode >= 0);


	}
	else
	{
		retCode = engine->SetDefaultNamespace("sqf"); assert(retCode >= 0);
		retCode = engine->RegisterGlobalFunction("void system_chat(string &in)", asFUNCTION(system_chat_generic), asCALL_GENERIC); assert(retCode >= 0);
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
		std::cout << "Failed to start new module\n";
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


void system_chat(std::string& str)
{
	std::cout << str << "\n";
	intercept::sqf::system_chat(str);
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