#include "diag.hpp"



void active_mission_fsms()
{
	//returns an array of game_values
	intercept::sqf::diag_active_mission_fsms();
}

void active_scripts()
{
	//returns an array of game_values
	intercept::sqf::diag_active_scripts();
}

void active_sqf_scripts()
{
	//returns an array of game_values
	intercept::sqf::diag_active_sqf_scripts();
}

void active_sqs_scripts()
{
	//returns an array of game_values
	intercept::sqf::diag_active_sqs_scripts();
}

void all_mission_eventhandlers()
{
	//returns an array of game_values
	intercept::sqf::diag_all_mission_eventhandlers();
}

void capture_frame(float& number)
{
	intercept::sqf::diag_capture_frame(number);
}

void capture_frame_to_file(float& number)
{
	intercept::sqf::diag_capture_frame_to_file(number);
}

void capture_slow_frame(std::string& section, float& threshold)
{
	intercept::sqf::diag_capture_slow_frame(section, threshold);
}

void code_performance(std::string& code, std::string& arguments, float& cycles)
{
	intercept::types::code rCode = intercept::sqf::compile(code);
	intercept::types::code rArg = intercept::sqf::compile(arguments);

	//returns an array of game_values
	intercept::sqf::diag_code_performance(rCode, rArg, cycles);
}

float delta_time()
{
	//returns an array of game_values
	return intercept::sqf::diag_delta_time();
}

void draw_mode(int& mode)
{
	intercept::sqf::diag_draw_mode(static_cast<intercept::sqf::debug_draw_modes>(mode));
}

void dump_call_trace_to_log()
{
	std::cout << "Not Implemented\n";
}

void dump_script_assembly()
{
	std::cout << "Not Implemented\n";
}

void dump_terrain_synth()
{
	//returns an array of game_values
	intercept::sqf::diag_dump_terrain_synth();
}

void dynamic_simulation_end(std::string& file)
{
	intercept::sqf::diag_dynamic_simulation_end(file);
}

void dynamic_simulation_start()
{
	std::cout << "Not Implemented\n";
}

void enable(int& mode, bool& state)
{
	// really, why? Why did take an enum, rather than a string like the engine expects?
	intercept::sqf::diag_enable(static_cast<intercept::sqf::debug_toggles>(mode), state);
}

bool enabled(std::string& mode)
{
	return intercept::sqf::diag_enabled(mode);
}

void export_config()
{
	std::cout << "Not Implemented\n";
}

void export_terrain_svg()
{
	std::cout << "Not Implemented\n";
}

float fps()
{
	return intercept::sqf::diag_fps();
}

float fpsmin()
{
	return intercept::sqf::diag_fpsmin();
}

float frameno()
{
	return intercept::sqf::diag_frameno();
}

//obsolete function
int get_terrain_grid()
{
	return intercept::sqf::get_terrain_grid();
}

//@TODO vec2
float get_terrain_height(vector2& vec)
{
	return intercept::sqf::get_terrain_height(vec);
}

//@TODO vec2
vector2 get_terrain_segment_offset(vector2& vec)
{
	return intercept::sqf::diag_get_terrain_segment_offset(vec);
}

void light_new_load(std::string &filepath)
{
	intercept::sqf::diag_light_new_load(filepath);
}

//@TODO return array
void list(std::string &mode)
{
	//returns an array of game_values
	intercept::sqf::diag_list(mode);
}

void log(std::string &logLine)
{
	intercept::sqf::diag_log(logLine);
}

void merge_config_file(std::string &filepath, bool &userdir)
{
	// this doesn't exist apparently?
	//intercept::sqf::diag_merge_config_file(filepath, userdir);
}

void record_turret_limits(bool& section)
{
	
	std::cout << "Not Implemented\n";
}

void reset_shapes()
{
	intercept::sqf::diag_reset_shapes();
}

void scope()
{
	std::cout << "Not Implemented\n";
	// and not needed
}

void set_light_new(std::string& config)
{
		
	//intercept::sqf::diag_active_sqs_scripts();
	//don't do anything as I haven't figured out a way to handle configs in the language
	return;
}

//@TODO this function, it will need a vec3 array input
void set_terrain_height()
{
	
}

//@TODO handle returned array
void stack_trace()
{

	//intercept::sqf::diag_stack_trace();
}

float tick_time()
{
	return intercept::sqf::diag_ticktime();
}

void toggle(int& mode)
{
	intercept::sqf::diag_toggle(static_cast<intercept::sqf::debug_toggles>(mode));
}

void export_jip_messages(std::string &fileName)
{

	intercept::sqf::export_jipmessages(fileName);
}

//@TODO handle array return
void get_terrain_info()
{
	intercept::sqf::get_terrain_info();
}

bool is_file_patching_enabled()
{

	return intercept::sqf::is_filepatching_enabled();
}

void log_entities()
{
	intercept::sqf::log_entities();
}



void register_wrapper_functions_diag_native(asIScriptEngine*& engine)
{
	int retCode;
	retCode = engine->SetDefaultNamespace("sqf::diag"); assert(retCode >= 0);
	retCode = engine->RegisterGlobalFunction("void active_mission_fsms()", asFUNCTION(active_mission_fsms), asCALL_CDECL); assert(retCode >= 0);
	retCode = engine->RegisterGlobalFunction("void active_scripts()", asFUNCTION(active_scripts), asCALL_CDECL); assert(retCode >= 0);
	retCode = engine->RegisterGlobalFunction("void active_sqf_scripts()", asFUNCTION(active_sqf_scripts), asCALL_CDECL); assert(retCode >= 0);
	retCode = engine->RegisterGlobalFunction("void active_sqs_scripts()", asFUNCTION(active_sqs_scripts), asCALL_CDECL); assert(retCode >= 0);
	retCode = engine->RegisterGlobalFunction("void all_mission_eventhandlers()", asFUNCTION(all_mission_eventhandlers), asCALL_CDECL); assert(retCode >= 0);

	retCode = engine->RegisterGlobalFunction("void capture_frame(float &in)", asFUNCTION(capture_frame), asCALL_CDECL); assert(retCode >= 0);
	retCode = engine->RegisterGlobalFunction("void capture_frame_to_file(float &in)", asFUNCTION(capture_frame_to_file), asCALL_CDECL); assert(retCode >= 0);
	retCode = engine->RegisterGlobalFunction("void capture_slow_frame(string &in, float &in)", asFUNCTION(capture_slow_frame), asCALL_CDECL); assert(retCode >= 0);
	retCode = engine->RegisterGlobalFunction("void code_performance(string &in, string &in, float &in)", asFUNCTION(code_performance), asCALL_CDECL); assert(retCode >= 0);
	retCode = engine->RegisterGlobalFunction("float delta_time()", asFUNCTION(delta_time), asCALL_CDECL); assert(retCode >= 0);

	retCode = engine->RegisterGlobalFunction("void draw_mode(int &in)", asFUNCTION(draw_mode), asCALL_CDECL); assert(retCode >= 0);
	retCode = engine->RegisterGlobalFunction("void dump_call_trace_to_log()", asFUNCTION(dump_call_trace_to_log), asCALL_CDECL); assert(retCode >= 0);
	retCode = engine->RegisterGlobalFunction("void dump_script_assembly()", asFUNCTION(dump_script_assembly), asCALL_CDECL); assert(retCode >= 0);
	retCode = engine->RegisterGlobalFunction("void dump_terrain_synth()", asFUNCTION(dump_terrain_synth), asCALL_CDECL); assert(retCode >= 0);
	retCode = engine->RegisterGlobalFunction("void dynamic_simulation_end(string& in)", asFUNCTION(dynamic_simulation_end), asCALL_CDECL); assert(retCode >= 0);

	retCode = engine->RegisterGlobalFunction("void dynamic_simulation_start()", asFUNCTION(dynamic_simulation_start), asCALL_CDECL); assert(retCode >= 0);
	retCode = engine->RegisterGlobalFunction("void enable(int &in, bool &in)", asFUNCTION(enable), asCALL_CDECL); assert(retCode >= 0);
	retCode = engine->RegisterGlobalFunction("bool enabled(string &in)", asFUNCTION(enabled), asCALL_CDECL); assert(retCode >= 0);
	retCode = engine->RegisterGlobalFunction("void export_config()", asFUNCTION(export_config), asCALL_CDECL); assert(retCode >= 0);
	retCode = engine->RegisterGlobalFunction("void export_terrain_svg()", asFUNCTION(export_terrain_svg), asCALL_CDECL); assert(retCode >= 0);

	retCode = engine->RegisterGlobalFunction("float fps()", asFUNCTION(fps), asCALL_CDECL); assert(retCode >= 0);
	retCode = engine->RegisterGlobalFunction("float fpsmin()", asFUNCTION(fpsmin), asCALL_CDECL); assert(retCode >= 0);
	retCode = engine->RegisterGlobalFunction("float frameno()", asFUNCTION(frameno), asCALL_CDECL); assert(retCode >= 0);
	retCode = engine->RegisterGlobalFunction("int get_terrain_grid()", asFUNCTION(get_terrain_grid), asCALL_CDECL); assert(retCode >= 0);
	retCode = engine->RegisterGlobalFunction("float get_terrain_height(vector2 &in)", asFUNCTION(get_terrain_height), asCALL_CDECL); assert(retCode >= 0);

	retCode = engine->RegisterGlobalFunction("vector2 get_terrain_segment_offset(vector2 &in)", asFUNCTION(get_terrain_segment_offset), asCALL_CDECL); assert(retCode >= 0);
	retCode = engine->RegisterGlobalFunction("void light_new_load(string &in)", asFUNCTION(light_new_load), asCALL_CDECL); assert(retCode >= 0);
	retCode = engine->RegisterGlobalFunction("void list(string &in)", asFUNCTION(list), asCALL_CDECL); assert(retCode >= 0);
	retCode = engine->RegisterGlobalFunction("void log(string &in)", asFUNCTION(log), asCALL_CDECL); assert(retCode >= 0);
	retCode = engine->RegisterGlobalFunction("void merge_config_file(string &in, bool &in)", asFUNCTION(merge_config_file), asCALL_CDECL); assert(retCode >= 0);

	retCode = engine->RegisterGlobalFunction("void record_turret_limits(bool &in)", asFUNCTION(record_turret_limits), asCALL_CDECL); assert(retCode >= 0);
	retCode = engine->RegisterGlobalFunction("void reset_shapes()", asFUNCTION(reset_shapes), asCALL_CDECL); assert(retCode >= 0);
	retCode = engine->RegisterGlobalFunction("float scope()", asFUNCTION(scope), asCALL_CDECL); assert(retCode >= 0);
	retCode = engine->RegisterGlobalFunction("void set_light_new(string &in)", asFUNCTION(set_light_new), asCALL_CDECL); assert(retCode >= 0);
	retCode = engine->RegisterGlobalFunction("void set_terrain_height()", asFUNCTION(set_terrain_height), asCALL_CDECL); assert(retCode >= 0);

	retCode = engine->RegisterGlobalFunction("void stack_trace()", asFUNCTION(stack_trace), asCALL_CDECL); assert(retCode >= 0);
	retCode = engine->RegisterGlobalFunction("float tick_time()", asFUNCTION(tick_time), asCALL_CDECL); assert(retCode >= 0);
	retCode = engine->RegisterGlobalFunction("void toggle(int &in)", asFUNCTION(toggle), asCALL_CDECL); assert(retCode >= 0);
	retCode = engine->RegisterGlobalFunction("void export_jip_messages(string& in)", asFUNCTION(export_jip_messages), asCALL_CDECL); assert(retCode >= 0);
	retCode = engine->RegisterGlobalFunction("void get_terrain_info()", asFUNCTION(get_terrain_info), asCALL_CDECL); assert(retCode >= 0);

	retCode = engine->RegisterGlobalFunction("bool is_file_patching_enabled()", asFUNCTION(is_file_patching_enabled), asCALL_CDECL); assert(retCode >= 0);
	retCode = engine->RegisterGlobalFunction("void log_entities()", asFUNCTION(log_entities), asCALL_CDECL); assert(retCode >= 0);

	////register 
	// 
	// 
	// 
	// s here!
	//retCode = engine->RegisterObjectType("activeMissionFSMs", sizeof(activeMissionFSMs), asOBJ_VALUE | asGetTypeTraits<activeMissionFSMs>()); assert(retCode >= 0);
	//retCode = engine->RegisterObjectProperty("activeMissionFSMs", "string name", asOFFSET(activeMissionFSMs, _name)); assert(retCode >= 0);
	//retCode = engine->RegisterObjectProperty("activeMissionFSMs", "string state", asOFFSET(activeMissionFSMs, _state)); assert(retCode >= 0);
	//retCode = engine->RegisterObjectProperty("activeMissionFSMs", "float timeOut", asOFFSET(activeMissionFSMs, _timeOut)); assert(retCode >= 0);

	//retCode = engine->RegisterObjectType("activeScripts", sizeof(activeScripts), asOBJ_VALUE | asGetTypeTraits<activeScripts>()); assert(retCode >= 0);
	//retCode = engine->RegisterObjectProperty("activeScripts", "float spawned", asOFFSET(activeScripts, _spawned)); assert(retCode >= 0);
	//retCode = engine->RegisterObjectProperty("activeScripts", "float execVMed", asOFFSET(activeScripts, _execVMed)); assert(retCode >= 0);
	//retCode = engine->RegisterObjectProperty("activeScripts", "float execed", asOFFSET(activeScripts, _execed)); assert(retCode >= 0);
	//retCode = engine->RegisterObjectProperty("activeScripts", "float execFSMed", asOFFSET(activeScripts, _execFSMed)); assert(retCode >= 0);

	//retCode = engine->RegisterObjectType("activeSQFScripts", sizeof(activeSQFScripts), asOBJ_VALUE | asGetTypeTraits<activeSQFScripts>()); assert(retCode >= 0);
	//retCode = engine->RegisterObjectProperty("activeSQFScripts", "string name", asOFFSET(activeSQFScripts, _name)); assert(retCode >= 0);
	//retCode = engine->RegisterObjectProperty("activeSQFScripts", "string filepath", asOFFSET(activeSQFScripts, _filepath)); assert(retCode >= 0);
	//retCode = engine->RegisterObjectProperty("activeSQFScripts", "bool isRunning", asOFFSET(activeSQFScripts, _isRunning)); assert(retCode >= 0);
	//retCode = engine->RegisterObjectProperty("activeSQFScripts", "float currentLine", asOFFSET(activeSQFScripts, _currentLine)); assert(retCode >= 0);

	//retCode = engine->RegisterObjectType("activeSQSScripts", sizeof(activeSQSScripts), asOBJ_VALUE | asGetTypeTraits<activeSQSScripts>()); assert(retCode >= 0);
	//retCode = engine->RegisterObjectProperty("activeSQSScripts", "string name", asOFFSET(activeSQSScripts, _name)); assert(retCode >= 0);
	//retCode = engine->RegisterObjectProperty("activeSQSScripts", "string filepath", asOFFSET(activeSQSScripts, _filepath)); assert(retCode >= 0);
	//retCode = engine->RegisterObjectProperty("activeSQSScripts", "bool isRunning", asOFFSET(activeSQSScripts, _isRunning)); assert(retCode >= 0);
	//retCode = engine->RegisterObjectProperty("activeSQSScripts", "float currentLine", asOFFSET(activeSQSScripts, _currentLine)); assert(retCode >= 0);

	//retCode = engine->RegisterObjectType("allMissionEvent", sizeof(allMissionEvent), asOBJ_VALUE | asGetTypeTraits<allMissionEvent>()); assert(retCode >= 0);
	//retCode = engine->RegisterObjectProperty("allMissionEvent", "string EHName", asOFFSET(allMissionEvent, _EHName)); assert(retCode >= 0);
	//retCode = engine->RegisterObjectProperty("allMissionEvent", "float EHCount", asOFFSET(allMissionEvent, _EHCount)); assert(retCode >= 0);

	//retCode = engine->RegisterObjectType("codePerformance", sizeof(codePerformance), asOBJ_VALUE | asGetTypeTraits<codePerformance>()); assert(retCode >= 0);
	//retCode = engine->RegisterObjectProperty("codePerformance", "float duration", asOFFSET(codePerformance, _duration)); assert(retCode >= 0);
	//retCode = engine->RegisterObjectProperty("codePerformance", "float cycles", asOFFSET(codePerformance, _cycles)); assert(retCode >= 0);

	//retCode = engine->RegisterObjectType("terrainMinMax", sizeof(terrainMinMax), asOBJ_VALUE | asGetTypeTraits<terrainMinMax>()); assert(retCode >= 0);
	//retCode = engine->RegisterObjectProperty("terrainMinMax", "float min", asOFFSET(terrainMinMax, _min)); assert(retCode >= 0);
	//retCode = engine->RegisterObjectProperty("terrainMinMax", "float max", asOFFSET(terrainMinMax, _max)); assert(retCode >= 0);

	//retCode = engine->RegisterObjectType("dumpTerrainSynth", sizeof(dumpTerrainSynth), asOBJ_VALUE | asGetTypeTraits<dumpTerrainSynth>()); assert(retCode >= 0);
	//retCode = engine->RegisterObjectProperty("dumpTerrainSynth", "float aLength", asOFFSET(dumpTerrainSynth, _aLength)); assert(retCode >= 0);
	//retCode = engine->RegisterObjectProperty("dumpTerrainSynth", "array<terrainMinMax> &minMax", asOFFSET(dumpTerrainSynth, _minMax)); assert(retCode >= 0);

	//retCode = engine->RegisterObjectType("terrainSegmentOffset", sizeof(terrainSegmentOffset), asOBJ_VALUE | asGetTypeTraits<terrainSegmentOffset>()); assert(retCode >= 0);
	//retCode = engine->RegisterObjectProperty("terrainSegmentOffset", "float x", asOFFSET(terrainSegmentOffset, _x)); assert(retCode >= 0);
	//retCode = engine->RegisterObjectProperty("terrainSegmentOffset", "float y", asOFFSET(terrainSegmentOffset, _y)); assert(retCode >= 0);
}

void register_wrapper_functions_diag_generic(asIScriptEngine*& engine)
{
	
}


void register_wrapper_functions_diag(asIScriptEngine*& engine)
{
	if (strstr(asGetLibraryOptions(), "AS_MAX_PORTABILITY"))
	{
		register_wrapper_functions_diag_generic(engine);
	}
	else
	{
		register_wrapper_functions_diag_native(engine);
	}
}
