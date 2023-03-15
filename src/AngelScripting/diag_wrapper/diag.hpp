#pragma once

#include <intercept.hpp>

#include <angelscript.h>
#include <string>
#include <iostream>
#include "../script.hpp"

void register_wrapper_functions_diag(asIScriptEngine*& engine);
void register_wrapper_functions_diag_native(asIScriptEngine*& engine);
void register_wrapper_functions_diag_generic(asIScriptEngine*& engine);







//diag objects

struct activeMissionFSMs
{
	std::string _name;
	std::string _state;
	float _timeOut;
};

struct activeScripts
{
	float _spawned;
	float _execVMed;
	float _execed;
	float _execFSMed;
};

struct activeSQFScripts
{
	std::string _name;
	std::string _filepath;
	bool _isRunning;
	float _currentLine;
};

struct activeSQSScripts
{
	std::string _name;
	std::string _filepath;
	bool _isRunning;
	float _currentLine;
};

struct allMissionEvent
{
	std::string _EHName;
	float _EHCount;
};

struct codePerformance
{
	float _duration;
	float _cycles;
};

struct terrainMinMax
{
	float _min;
	float _max;
};

struct dumpTerrainSynth
{
	float _aLength;
	CScriptArray *_minMax;
};

struct terrainSegmentOffset
{
	float _x;
	float _y;
};