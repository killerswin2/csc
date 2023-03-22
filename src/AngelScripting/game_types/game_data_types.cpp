#include "game_data_types.hpp"

void register_game_data_types_generic(asIScriptEngine*& engine)
{

}

void register_game_data_types_native(asIScriptEngine*& engine)
{
    int retCode;
    retCode = engine->SetDefaultNamespace(""); assert(retCode >= 0);

    retCode = engine->RegisterObjectType("game_value", sizeof(game_value), asOBJ_REF); assert(retCode >= 0);
    retCode = engine->RegisterObjectType("object", sizeof(intercept::types::object), asOBJ_REF); assert(retCode >= 0);
    retCode = engine->RegisterObjectType("code", sizeof(intercept::types::code), asOBJ_REF); assert(retCode >= 0);
    retCode = engine->RegisterObjectType("config", sizeof(intercept::types::config), asOBJ_REF); assert(retCode >= 0);
    retCode = engine->RegisterObjectType("control", sizeof(intercept::types::control), asOBJ_REF); assert(retCode >= 0);
    retCode = engine->RegisterObjectType("display", sizeof(intercept::types::display), asOBJ_REF); assert(retCode >= 0);
    retCode = engine->RegisterObjectType("location", sizeof(intercept::types::location), asOBJ_REF); assert(retCode >= 0);
    retCode = engine->RegisterObjectType("script", sizeof(intercept::types::script), asOBJ_REF); assert(retCode >= 0);
    retCode = engine->RegisterObjectType("side", sizeof(intercept::types::side), asOBJ_REF); assert(retCode >= 0);
    retCode = engine->RegisterObjectType("rv_text", sizeof(intercept::types::rv_text), asOBJ_REF); assert(retCode >= 0);
    retCode = engine->RegisterObjectType("team_member", sizeof(intercept::types::team_member), asOBJ_REF); assert(retCode >= 0);
    retCode = engine->RegisterObjectType("rv_namespace", sizeof(intercept::types::rv_namespace), asOBJ_REF); assert(retCode >= 0);
    retCode = engine->RegisterObjectType("task", sizeof(intercept::types::task), asOBJ_REF); assert(retCode >= 0);
    retCode = engine->RegisterObjectType("rv_array", sizeof(auto_array<game_value>), asOBJ_REF); assert(retCode >= 0);
    //retCode = engine->RegisterObjectType("rv_string", sizeof(intercept::types::task), asOBJ_REF); assert(retCode >= 0);


}


void register_game_data_types(asIScriptEngine*& engine)
{
    if (strstr(asGetLibraryOptions(), "AS_MAX_PORTABILITY"))
        register_game_data_types_generic(engine);
    else
        register_game_data_types_native(engine);
}