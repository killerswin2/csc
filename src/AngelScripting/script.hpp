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
void configureEngine(asIScriptEngine*& engine);
void messageCallback(const asSMessageInfo *msg, void* param);
int  compileScript(asIScriptEngine*& engine);
void printString(std::string& str);
void printString_Generic(asIScriptGeneric* gen);
void lineCallback(asIScriptContext*& ctx, DWORD* timeOut);

namespace AngelScript
{
	void pre_start();

};


