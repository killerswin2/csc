cmake_minimum_required (VERSION 3.0)
set(ADDITION_LINK_LIBRARIES)

file(GLOB_RECURSE INTERCEPT_PLUGIN_SOURCES *.h *.hpp *.c *.cpp)
SOURCE_GROUP("src" FILES ${INTERCEPT_PLUGIN_SOURCES})


file(GLOB INTERCEPT_PLUGIN_GEOMERTY_SOURCES "Geometry/*.cpp" "Geometry/*.hpp" "Geometry/*.h")
SOURCE_GROUP("src/Geometry" FILES ${INTERCEPT_PLUGIN_GEOMERTY_SOURCES})

file(GLOB INTERCEPT_PLUGIN_GEOMERTY_SOURCES "Json/*.cpp" "Json/*.hpp" "Json/*.h")
SOURCE_GROUP("src/Json" FILES ${INTERCEPT_PLUGIN_GEOMERTY_SOURCES})


set(AS_ADDON_PATH "${CMAKE_SOURCE_DIR}/lib/angelscript/sdk/add_on")

#file(GLOB_RECURSE AS_ADDON_SOURCE
#	"${AS_ADDON_PATH}/contextmgr/*.cpp"	"${AS_ADDON_PATH}/contextmgr/*.h"
#	"${AS_ADDON_PATH}/datetime/*.cpp"	"${AS_ADDON_PATH}/datetime/*.h"
#	"${AS_ADDON_PATH}/debugger/*.cpp"	"${AS_ADDON_PATH}/debugger/*.h"
#	"${AS_ADDON_PATH}/scriptany/*.cpp"	"${AS_ADDON_PATH}/scriptany/*.h"
#	"${AS_ADDON_PATH}/scriptarray/*.cpp"	"${AS_ADDON_PATH}/scriptarray/*.h"
#	"${AS_ADDON_PATH}/scriptbuilder/*.cpp"	"${AS_ADDON_PATH}/scriptbuilder/*.h"
#	"${AS_ADDON_PATH}/scriptdictionary/*.cpp"	"${AS_ADDON_PATH}/scriptdictionary/*.h"
#	"${AS_ADDON_PATH}/scriptfile/*.cpp"	"${AS_ADDON_PATH}/scriptfile/*.h"
#	"${AS_ADDON_PATH}/scriptgrid/*.cpp"	"${AS_ADDON_PATH}/scriptgrid/*.h"
#	"${AS_ADDON_PATH}/scripthandle/*.cpp"	"${AS_ADDON_PATH}/scripthandle/*.h"
#	"${AS_ADDON_PATH}/scripthelper/*.cpp"	"${AS_ADDON_PATH}/scripthelper/*.h"
#	"${AS_ADDON_PATH}/scriptmath/*.cpp"	"${AS_ADDON_PATH}/scriptmath/*.h"
#	"${AS_ADDON_PATH}/scriptstdstring/*.cpp"	"${AS_ADDON_PATH}/scriptstdstring/*.h"
#	"${AS_ADDON_PATH}/serializer/*.cpp"	"${AS_ADDON_PATH}/serializer/*.h"
#	"${AS_ADDON_PATH}/weakref/*.cpp"	"${AS_ADDON_PATH}/weakref/*.h"
#)

file(GLOB_RECURSE AS_ADDON_SOURCE
	"${AS_ADDON_PATH}/contextmgr/*.cpp"	
	"${AS_ADDON_PATH}/datetime/*.cpp"	
	"${AS_ADDON_PATH}/debugger/*.cpp"	
	"${AS_ADDON_PATH}/scriptany/*.cpp"	
	"${AS_ADDON_PATH}/scriptarray/*.cpp"	
	"${AS_ADDON_PATH}/scriptbuilder/*.cpp"	
	"${AS_ADDON_PATH}/scriptdictionary/*.cpp"	
	"${AS_ADDON_PATH}/scriptfile/*.cpp"	
	"${AS_ADDON_PATH}/scriptgrid/*.cpp"	
	"${AS_ADDON_PATH}/scripthandle/*.cpp"	
	"${AS_ADDON_PATH}/scripthelper/*.cpp"	
	"${AS_ADDON_PATH}/scriptmath/*.cpp"	
	"${AS_ADDON_PATH}/scriptstdstring/*.cpp"
	"${AS_ADDON_PATH}/serializer/*.cpp"	
	"${AS_ADDON_PATH}/weakref/*.cpp"
)

# angelScripting here

if(MSVC)
    #option(MSVC_COMPILE_FLAGS "Compiler flags to use with MSVC" "/MP")
	set(ADDITION_LINK_LIBRARIES ${ADDITION_LINK_LIBRARIES} winmm)
endif()

find_package(Threads)
file(GLOB ANGELSCRIPT_SOURCE "${CMAKE_SOURCE_DIR}/lib/angelscript/sdk/source/*.c" "${CMAKE_SOURCE_DIR}/lib/angelscript/sdk/source/*.cpp")


if(MSVC AND CMAKE_CL_64)
    enable_language(ASM_MASM)
    if(CMAKE_ASM_MASM_COMPILER_WORKS)
        set(ANGELSCRIPT_SOURCE ${ANGELSCRIPT_SOURCE} "${CMAKE_SOURCE_DIR}/lib/angelscript/sdk/source/as_callfunc_x64_msvc_asm.asm")
    else()
        message(FATAL ERROR "MSVC x86_64 target requires a working assembler")
    endif()
endif()

#If you want to split your source files into different directories you can do so here

#The SOURCE_GROUP string is the directory it will display as inside your visual studio.
#Here is a example of a "utilities" subdirectory.

#file(GLOB INTERCEPT_plugin_utilities_SOURCES "utilities/*.cpp" "utilities/*.hpp" "utilities/*.h")
#SOURCE_GROUP("src/utilities" FILES ${INTERCEPT_plugin_utilities_SOURCES})

#----Don't change anything below this line


#include the Intercept headers from the submodule
set(INTERCEPT_CLIENT_PATH "${CMAKE_SOURCE_DIR}/intercept/src/client")

set(INTERCEPT_INCLUDE_PATH "${INTERCEPT_CLIENT_PATH}/headers" "${INTERCEPT_CLIENT_PATH}/headers/shared" "${INTERCEPT_CLIENT_PATH}/headers/client/" "${INTERCEPT_CLIENT_PATH}/headers/client/sqf")

set(ANGELSCRIPT_PATH "${CMAKE_SOURCE_DIR}/lib/angelscript/sdk/source")

set(ANGELSCRIPT_INCLUDE_PATH "${CMAKE_SOURCE_DIR}/lib/angelscript/sdk/include")

if(USE_64BIT_BUILD)
    set(INTERCEPT_PLUGIN_NAME "${CMAKE_PROJECT_NAME}_x64")
else()
    set(INTERCEPT_PLUGIN_NAME "${CMAKE_PROJECT_NAME}")
endif()

add_definitions(/DINTERCEPT_NO_THREAD_SAFETY)

if(USE_ENGINE_TYPES)
    add_definitions(/DINTERCEPT_SQF_STRTYPE_RSTRING)
endif()

file(GLOB INTERCEPT_HOST_SOURCES "${INTERCEPT_CLIENT_PATH}/intercept/client/*.cpp"  "${INTERCEPT_CLIENT_PATH}/intercept/client/sqf/*.cpp" "${INTERCEPT_CLIENT_PATH}/intercept/shared/*.cpp")
SOURCE_GROUP("intercept" FILES ${INTERCEPT_HOST_SOURCES})

add_library( ${INTERCEPT_PLUGIN_NAME} SHARED  ${INTERCEPT_HOST_SOURCES} ${INTERCEPT_PLUGIN_GEOMERTY_SOURCES} ${ANGELSCRIPT_SOURCE} ${AS_ADDON_SOURCE} ${INTERCEPT_PLUGIN_SOURCES})

include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${INTERCEPT_INCLUDE_PATH} ${ANGELSCRIPT_INCLUDE_PATH} ${AS_ADDON_PATH})
target_include_directories(${INTERCEPT_PLUGIN_NAME} PUBLIC ../lib/json/single_include )
target_link_libraries(${INTERCEPT_PLUGIN_NAME} Threads::Threads ${ADDITION_LINK_LIBRARIES})

set_target_properties(${INTERCEPT_PLUGIN_NAME} PROPERTIES PREFIX "")
set_target_properties(${INTERCEPT_PLUGIN_NAME} PROPERTIES FOLDER "${CMAKE_PROJECT_NAME}")


if(CMAKE_COMPILER_IS_GNUCXX)
	set(CMAKE_CXX_FLAGS "-std=c++1z -O2 -s -fPIC -fpermissive -static-libgcc -static-libstdc++")#-march=i686 -m32
	set(CMAKE_FIND_LIBRARY_SUFFIXES ".a")
	set(CMAKE_SHARED_LINKER_FLAGS "-shared -static-libgcc -static-libstdc++")
else()
	set(CMAKE_CXX_FLAGS_DEBUG "/D_DEBUG /MTd /Zi /Ob0 /Od /RTC1 /MP /EHsc")
	set(CMAKE_CXX_FLAGS_RELEASE "/MT /Zi /O2 /Ob1 /EHsc /MP") #with debug info
	set(CMAKE_SHARED_LINKER_FLAGS_RELEASE "/OPT:REF /DEBUG:FULL" "/VERBOSE") 
endif()

option(FILE_PATH "non default install path" off)
message(STATUS "FILE PATH: " ${FILE_PATH})

find_program(POWERSHELL NAMES powershell)
find_program(POWERSHELL_EXEC NAMES "install.ps1" PATHS "..")
message(STATUS ${POWERSHELL_EXEC})

if(NOT FILE_PATH)
	message("no path passed")
	add_custom_command(TARGET ${INTERCEPT_PLUGIN_NAME} 
					POST_BUILD
					COMMAND ${POWERSHELL} ${POWERSHELL_EXEC} -installPath "E:/SteamLibrary/steamapps/common")
else()
	add_custom_command(TARGET ${INTERCEPT_PLUGIN_NAME} 
					POST_BUILD
					COMMAND ${POWERSHELL} ${POWERSHELL_EXEC} -installPath ${STEAM_PATH})
endif()