#include "diag.hpp"

void register_wrapper_functions_diag_native(asIScriptEngine*& engine)
{
	int retCode;
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

void register_wrapper_functions_diag_native(asIScriptEngine*& engine)
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
