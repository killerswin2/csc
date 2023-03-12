#pragma once

#include <intercept.hpp>
#include "../commands.hpp"


#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cassert>
#include <angelscript.h>
#include <scriptbuilder/scriptbuilder.h>
#include <scriptstdstring/scriptstdstring.h>
#include <scriptarray/scriptarray.h>

#include "diag_wrapper/diag.hpp"


#ifdef __linux__
#include <sys/time.h>
#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#else
#include <conio.h>   // kbhit(), getch()
#include <windows.h> // timeGetTime()
#endif

#define DEBUG_CONSOLE

#ifdef __linux__
// yes, we use DWORD
typedef unsigned int DWORD;

#endif
int  runApplication();
void messageCallback(const asSMessageInfo *msg, void* param);
void system_chat(std::string& str);
void system_chat_generic(asIScriptGeneric* gen);
void lineCallback(asIScriptContext*& ctx, DWORD* timeOut);

namespace AngelScript
{
	void pre_start();

	class ScriptEngine
	{
	private:
		asIScriptEngine* engine;
		asIScriptContext* ctx;
		DWORD timeOut;
	public:
		ScriptEngine();
		~ScriptEngine();
		void config_engine();
		void run_engine();
		int create_engine();
		int set_message_callback(const asSFuncPtr& callback, void* obj, asDWORD callConv);
		int compile_script();
		int create_context();
		int set_line_callback(asSFuncPtr callback, void* obj, int callConv);
		asIScriptFunction* find_function();
		int prepare_context(asIScriptFunction* func);
		int set_timeout();
		int execute_context();
	};

	class Engine
	{
	private:
		static AngelScript::ScriptEngine * scriptEngine;
	public:
		Engine() {};
		AngelScript::ScriptEngine* get_script_engine() { return scriptEngine; }
	};
};




