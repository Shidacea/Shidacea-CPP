# Minimum cmake version

cmake_minimum_required(VERSION 3.5)

# Compilation options

option(SHIDACEA_COMPILE_CORE_SCRIPTS "Compiles the Shidacea core scripts" OFF)
option(SHIDACEA_COMPILE_ALL_SCRIPTS "Compiles the Shidacea core and custom scripts" OFF)
option(SHIDACEA_EXCLUDE_IMGUI "Excludes ImGui from Shidacea" OFF)
option(SHIDACEA_EXCLUDE_SFML "Excludes SFML from Shidacea" OFF)	# For future use

# Compile flags

set(CMAKE_SHARED_LINKER_FLAGS
    "${CMAKE_SHARED_LINKER_FLAGS}")

set(CMAKE_EXE_LINKER_FLAGS
    "${CMAKE_EXE_LINKER_FLAGS}")

# Define platform dependent libraries

if(WIN32)
	
	set(ADDITIONAL_LIBRARIES sfml-main Ws2_32)
	set(MRUBY_LIBRARIES "${CMAKE_BINARY_DIR}/third_party/mruby/lib/libmruby.lib" "${CMAKE_BINARY_DIR}/third_party/mruby/lib/libmruby_core.lib")

else()

	set(ADDITIONAL_LIBRARIES stdc++fs)
	set(MRUBY_LIBRARIES "${CMAKE_BINARY_DIR}/third_party/mruby/lib/libmruby.a" "${CMAKE_BINARY_DIR}/third_party/mruby/lib/libmruby_core.a")

endif()

add_definitions(-DMRB_USE_FLOAT)

if(SHIDACEA_COMPILE_CORE_SCRIPTS)

	add_definitions(-DSHIDACEA_COMPILE_CORE_SCRIPTS)

endif()

if(SHIDACEA_COMPILE_ALL_SCRIPTS)

	add_definitions(-DSHIDACEA_COMPILE_CORE_SCRIPTS)
	add_definitions(-DSHIDACEA_COMPILE_ALL_SCRIPTS)

endif()

if(SHIDACEA_EXCLUDE_IMGUI)

	add_definitions(-DSHIDACEA_EXCLUDE_IMGUI)

endif()

include(${CMAKE_ROOT}/Modules/ExternalProject.cmake)

# Project name

project(NewProject)
set(EXECUTABLE_NAME "Launshi")

# C++ Standard

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 18)

# Check Ruby and mRuby dependencies

find_program(RUBY_EXECUTABLE ruby) 
find_program(BISON_EXECUTABLE bison)

# Load mRuby

ExternalProject_Add(mruby
  PREFIX "${CMAKE_BINARY_DIR}/third_party/mruby"
  DOWNLOAD_COMMAND ""
  UPDATE_COMMAND ""
  BUILD_IN_SOURCE 1
  SOURCE_DIR "${CMAKE_SOURCE_DIR}/third_party/mruby" 
  CONFIGURE_COMMAND ""
  BUILD_COMMAND ${RUBY_EXECUTABLE} minirake MRUBY_BUILD_DIR=${CMAKE_BINARY_DIR}/third_party/mruby MRUBY_CONFIG=${CMAKE_SOURCE_DIR}/mruby_build_config.rb
  INSTALL_COMMAND ""
  BUILD_BYPRODUCTS "${MRUBY_LIBRARIES}")
include_directories("${CMAKE_SOURCE_DIR}/third_party/mruby/include")

# Load SFML libraries

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
add_subdirectory(third_party/SFML)

# Load ImGui-SFML, may be a bit hacky, but works

if(NOT SHIDACEA_EXCLUDE_IMGUI)

	set(IMGUI_DIR "${CMAKE_SOURCE_DIR}/third_party/imgui")
	set(SFML_DIR "${CMAKE_BINARY_DIR}")
	set(IMGUI_SFML_FIND_SFML OFF)
	add_subdirectory(third_party/imgui-sfml)

endif()

# Setup directories

include_directories(${CMAKE_BINARY_DIR})

if(NOT SHIDACEA_COMPILE_ALL_SCRIPTS)

	if(SHIDACEA_COMPILE_CORE_SCRIPTS)

		install(DIRECTORY DESTINATION ${CMAKE_BINARY_DIR}/scripts_include)
		install(DIRECTORY DESTINATION ${CMAKE_BINARY_DIR}/scripts_core)

	else()

		install(DIRECTORY DESTINATION ${CMAKE_BINARY_DIR}/scripts_custom)

	endif()

endif()

# Macros for configuring the script files
# If this is a debug build, copy the ruby files to the build directory
# Otherwise compile them to bytecode

macro(COMPILE_RUBY_SCRIPTS arg_name arg_file arg_module flag)

	if(${flag})

		message("Preparing header file: ${CMAKE_BINARY_DIR}/compiled_scripts/CompiledRuby${arg_module}.h")

		add_custom_target(TargetRuby${arg_module}
			COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/compiled_scripts
			COMMAND ${CMAKE_BINARY_DIR}/third_party/mruby/bin/mrbc -g -Bcompiled_ruby_${arg_file} -o ${CMAKE_BINARY_DIR}/compiled_scripts/CompiledRuby${arg_module}.h ${COMPILED_RUBY_${arg_name}_SCRIPTS} 
			|| ${CMAKE_BINARY_DIR}/third_party/mruby/bin/mrbc -g -Bcompiled_ruby_${arg_file} -o ${CMAKE_BINARY_DIR}/compiled_scripts/CompiledRuby${arg_module}.h ${CMAKE_SOURCE_DIR}/core/Void.rb
			DEPENDS ${COMPILED_RUBY_${arg_name}_SCRIPTS} mruby
			VERBATIM
		)

		set(RUBY_COMPILED_TARGETS TargetRuby${arg_module} ${RUBY_COMPILED_TARGETS})

	endif()

endmacro()

macro(LOAD_AND_COMPILE_RUBY_FOLDER arg_name arg_path arg_file arg_module flag)

	file(GLOB_RECURSE RUBYSCRIPTS_${arg_name} "${CMAKE_SOURCE_DIR}/${arg_path}/*.rb")

	if(NOT ${flag})

		install(DIRECTORY DESTINATION ${CMAKE_BINARY_DIR}/${arg_path})

	endif()
	
	foreach(RUBYSCRIPT_${arg_name} ${RUBYSCRIPTS_${arg_name}})

		get_filename_component(${arg_name}_SCRIPT_NAME ${RUBYSCRIPT_${arg_name}} NAME_WE)
		string(REPLACE "${CMAKE_SOURCE_DIR}/${arg_path}/" "" TRUNCATED_SCRIPT_NAME ${RUBYSCRIPT_${arg_name}})

		if(NOT ${flag})

			configure_file(
				${RUBYSCRIPT_${arg_name}}
				${CMAKE_BINARY_DIR}/${arg_path}/${TRUNCATED_SCRIPT_NAME}
			)

		else()

			set(COMPILED_RUBY_${arg_name}_SCRIPTS ${RUBYSCRIPT_${arg_name}} ${COMPILED_RUBY_${arg_name}_SCRIPTS})

		endif()

	endforeach(RUBYSCRIPT_${arg_name})

	COMPILE_RUBY_SCRIPTS(${arg_name} ${arg_file} ${arg_module} ${flag})

endmacro()

macro(LOAD_AND_COMPILE_RUBY_SCRIPT arg_name arg_path arg_file arg_module flag)

	if(NOT ${flag})

		configure_file(
			${CMAKE_SOURCE_DIR}/${arg_path}/${arg_module}.rb
			${CMAKE_BINARY_DIR}/${arg_path}/${arg_module}.rb
		)

	else()

		set(COMPILED_RUBY_${arg_name}_SCRIPTS ${CMAKE_SOURCE_DIR}/${arg_path}/${arg_module}.rb)

	endif()
		
	COMPILE_RUBY_SCRIPTS(${arg_name} ${arg_file} ${arg_module} ${flag})

endmacro()

# Load and compile all ruby script folders and single scripts

if(SHIDACEA_COMPILE_CORE_SCRIPTS OR SHIDACEA_COMPILE_ALL_SCRIPTS)

	set(SHIDACEA_COMPILE_CORE ON)

else()

	set(SHIDACEA_COMPILE_CORE OFF)

endif()

LOAD_AND_COMPILE_RUBY_FOLDER(INCLUDE kernel/scripts/include include Include ${SHIDACEA_COMPILE_CORE})
LOAD_AND_COMPILE_RUBY_FOLDER(CORE kernel/scripts/core core Core ${SHIDACEA_COMPILE_CORE})
LOAD_AND_COMPILE_RUBY_FOLDER(CUSTOM_RESOURCES kernel/scripts/custom/resources custom_resources CustomResources ${SHIDACEA_COMPILE_ALL_SCRIPTS})
LOAD_AND_COMPILE_RUBY_FOLDER(CUSTOM_SCENES kernel/scripts/custom/scenes custom_scenes CustomScenes ${SHIDACEA_COMPILE_ALL_SCRIPTS})
LOAD_AND_COMPILE_RUBY_FOLDER(CUSTOM_ENTITIES kernel/scripts/custom/entities custom_entities CustomEntities ${SHIDACEA_COMPILE_ALL_SCRIPTS})
LOAD_AND_COMPILE_RUBY_FOLDER(CUSTOM_OTHER kernel/scripts/custom/other custom_other CustomOther ${SHIDACEA_COMPILE_ALL_SCRIPTS})

LOAD_AND_COMPILE_RUBY_SCRIPT(GAME kernel/scripts/custom custom_game Game ${SHIDACEA_COMPILE_ALL_SCRIPTS})
LOAD_AND_COMPILE_RUBY_SCRIPT(MAIN kernel/scripts/custom custom_main Main ${SHIDACEA_COMPILE_ALL_SCRIPTS})

# Add external libraries from the SFML source directory

if(WIN32)

	if(CMAKE_SIZEOF_VOID_P EQUAL 8)

		file(COPY ${CMAKE_SOURCE_DIR}/third_party/SFML/extlibs/bin/x64/openal32.dll
		DESTINATION ${CMAKE_BINARY_DIR})

	else()

		file(COPY ${CMAKE_SOURCE_DIR}/third_party/SFML/extlibs/bin/x86/openal32.dll
		DESTINATION ${CMAKE_BINARY_DIR})

	endif()
	
endif()

# Copy all asset files and preserve their tree structure

file(GLOB_RECURSE ASSET_FILES "${CMAKE_SOURCE_DIR}/kernel/assets/*.*")

foreach(ASSET_FILE ${ASSET_FILES})

	string(REPLACE "${CMAKE_SOURCE_DIR}/" "" TRUNCATED_ASSET_FILE ${ASSET_FILE})

	configure_file(
	
		${TRUNCATED_ASSET_FILE}
		${TRUNCATED_ASSET_FILE}

	COPYONLY)

endforeach(ASSET_FILE)

# Copy the demo projects

file(GLOB_RECURSE DEMO_FILES "${CMAKE_SOURCE_DIR}/demo_projects/*.*")

foreach(DEMO_FILE ${DEMO_FILES})

	string(REPLACE "${CMAKE_SOURCE_DIR}/" "" TRUNCATED_DEMO_FILE ${DEMO_FILE})

	configure_file(
	
		${TRUNCATED_DEMO_FILE}
		${TRUNCATED_DEMO_FILE}

	COPYONLY)

endforeach(DEMO_FILE)

file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/projects)

# Source files

set(AUDIO_SOURCES
	core/audio/Music.cpp
)

set(GRAPHICS_SOURCES
	core/graphics/RenderStates.cpp
	core/graphics/Color.cpp
	core/graphics/View.cpp
	core/graphics/Window.cpp
	core/graphics/Texture.cpp
	core/graphics/Sprite.cpp
	core/graphics/Font.cpp
	core/graphics/Text.cpp
)

set(IMGUI_SOURCES
	core/graphics/ImGuiWrapper.cpp
)

set(NETWORK_SOURCES
	core/network/Socket.cpp
	core/network/Listener.cpp
)

set(MAP_SOURCES
	core/map/Tile.cpp
	core/map/Tileset.cpp
	core/map/MapLayer.cpp
)

set(INTERNAL_SOURCES
	core/internal/IntRect.cpp
	core/internal/FloatRect.cpp
	core/internal/Coordinates.cpp
	core/internal/Events.cpp
	core/internal/Shape.cpp
	core/internal/Collisions.cpp
)

set(SCRIPTING_SOURCES
	core/scripting/Helper.cpp
	core/scripting/Script.cpp
)

include_directories(
	core/internal 
	core/audio
	core/graphics
	core/network
	core/map
	core/scripting
)

# Load source files

if(NOT SHIDACEA_EXCLUDE_IMGUI)
	
	set(GRAPHICS_SOURCES ${GRAPHICS_SOURCES} ${IMGUI_SOURCES})

endif()

set(SOURCE_FILES 
	${AUDIO_SOURCES}
	${GRAPHICS_SOURCES}
	${NETWORK_SOURCES}
	${MAP_SOURCES}
	${INTERNAL_SOURCES}
	${SCRIPTING_SOURCES}
	Main.cpp
)

#set_source_files_properties(
#
#	${SOURCE_FILES}
#	COMPILE_FLAGS /Wall
#
#)

# Set libraries

if(NOT SHIDACEA_EXCLUDE_IMGUI)

	set(IMGUI_LIBRARIES ImGui-SFML::ImGui-SFML)

endif()

set(SFML_LIBRARIES sfml-system sfml-window sfml-graphics sfml-audio sfml-network)

# Create executable and link libraries

add_executable(${EXECUTABLE_NAME} ${SOURCE_FILES})
add_dependencies(${EXECUTABLE_NAME} mruby ${RUBY_COMPILED_TARGETS})
target_link_libraries(${EXECUTABLE_NAME} ${MRUBY_LIBRARIES} ${IMGUI_LIBRARIES} ${SFML_LIBRARIES} ${ADDITIONAL_LIBRARIES})

configure_file(
	Changelog.txt
	Changelog.txt
)