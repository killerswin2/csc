#pragma once

#include <intercept.hpp>

#include <angelscript.h>
#include "../script.hpp"

void register_wrapper_functions_diag(asIScriptEngine*& engine);
void register_wrapper_functions_diag_native(asIScriptEngine*& engine);
void register_wrapper_functions_diag_generic(asIScriptEngine*& engine)