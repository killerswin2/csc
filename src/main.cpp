#include <intercept.hpp>
#include "commands.hpp"
#include "Geometry/rotator.hpp"
#include "Json/json.hpp"
#include "AngelScripting/script.hpp"

// keep this global, so commands can't go out of scope.
Commands& commands = Commands::get();


int intercept::api_version() { //This is required for the plugin to work.
    return INTERCEPT_SDK_API_VERSION;
}

void intercept::register_interfaces() {
    
}

void intercept::pre_start() {
    Rotation::Rotator::pre_start();
    json_game_data::json::pre_start();
    json_game_data::jsonArray::pre_start();
    AngelScript::pre_start();
}

void intercept::pre_init() {
    
}
