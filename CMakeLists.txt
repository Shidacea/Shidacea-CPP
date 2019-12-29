# Minimum cmake version

cmake_minimum_required(VERSION 3.5)

set(CMAKE_SHARED_LINKER_FLAGS
    "${CMAKE_SHARED_LINKER_FLAGS}")

set(CMAKE_EXE_LINKER_FLAGS
    "${CMAKE_EXE_LINKER_FLAGS}")

# Define platform dependent libraries

if(WIN32)
	
	set(ADDITIONAL_LIBRARIES sfml-main Ws2_32)
	set(MRUBY_LIBRARIES "${CMAKE_BINARY_DIR}/mruby/lib/libmruby.lib" "${CMAKE_BINARY_DIR}/mruby/lib/libmruby_core.lib")

else()

	set(ADDITIONAL_LIBRARIES stdc++fs)
	set(MRUBY_LIBRARIES "${CMAKE_BINARY_DIR}/mruby/lib/libmruby.a" "${CMAKE_BINARY_DIR}/mruby/lib/libmruby_core.a")

endif()

add_definitions(-DMRB_USE_FLOAT)

include(${CMAKE_ROOT}/Modules/ExternalProject.cmake)

# Project name

project(NewProject)
set(EXECUTABLE_NAME "NewProject")

# C++ Standard

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 18)

# Check Ruby and mRuby dependencies

find_program(RUBY_EXECUTABLE ruby) 
find_program(BISON_EXECUTABLE bison)

# Load mRuby

ExternalProject_Add(mruby
  PREFIX "${CMAKE_BINARY_DIR}/mruby"
  DOWNLOAD_COMMAND ""
  UPDATE_COMMAND ""
  BUILD_IN_SOURCE 1
  SOURCE_DIR "${CMAKE_SOURCE_DIR}/mruby" 
  CONFIGURE_COMMAND ""
  BUILD_COMMAND ${RUBY_EXECUTABLE} minirake MRUBY_BUILD_DIR=${CMAKE_BINARY_DIR}/mruby MRUBY_CONFIG=${CMAKE_SOURCE_DIR}/mruby_build_config.rb
  INSTALL_COMMAND ""
  BUILD_BYPRODUCTS "${MRUBY_LIBRARIES}")
include_directories("${CMAKE_SOURCE_DIR}/mruby/include")

# Load SFML libraries

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
add_subdirectory(SFML)

# Load ImGui-SFML, may be a bit hacky, but works

set(IMGUI_DIR "${CMAKE_SOURCE_DIR}/imgui")
set(SFML_DIR "${CMAKE_BINARY_DIR}")
set(IMGUI_SFML_FIND_SFML OFF)
add_subdirectory(imgui-sfml)

# Collect all ruby scripts, sorted into different categories

file(GLOB_RECURSE RUBYSCRIPTS "${CMAKE_SOURCE_DIR}/scripts/*.rb")

set(RUBY_MAIN_SCRIPT "${CMAKE_SOURCE_DIR}/scripts/custom/Main.rb")
set(RUBY_GAME_SCRIPT "${CMAKE_SOURCE_DIR}/scripts/custom/Game.rb")

# Setup directories

include_directories(${CMAKE_BINARY_DIR})

if(CMAKE_BUILD_TYPE STREQUAL "Debug")

	install(DIRECTORY DESTINATION ${CMAKE_BINARY_DIR}/scripts)

endif()

# Macros for configuring the script files
# If this is a debug build, copy the ruby files to the build directory
# Otherwise compile them to bytecode

macro(COMPILE_RUBY_SCRIPTS arg_name arg_file arg_module)

	if(NOT CMAKE_BUILD_TYPE STREQUAL "Debug")

		message("Preparing header file: ${CMAKE_BINARY_DIR}/compiled_scripts/CompiledRuby${arg_module}.h")

		add_custom_target(TargetRuby${arg_module}
			COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/compiled_scripts
			COMMAND ${CMAKE_BINARY_DIR}/mruby/bin/mrbc -g -Bcompiled_ruby_${arg_file} -o ${CMAKE_BINARY_DIR}/compiled_scripts/CompiledRuby${arg_module}.h ${COMPILED_RUBY_${arg_name}_SCRIPTS} 
			|| ${CMAKE_BINARY_DIR}/mruby/bin/mrbc -g -Bcompiled_ruby_${arg_file} -o ${CMAKE_BINARY_DIR}/compiled_scripts/CompiledRuby${arg_module}.h ${CMAKE_SOURCE_DIR}/scripts/Void.rb
			DEPENDS ${COMPILED_RUBY_${arg_name}_SCRIPTS} mruby
			VERBATIM
		)

		set(RUBY_COMPILED_TARGETS TargetRuby${arg_module} ${RUBY_COMPILED_TARGETS})

	endif()

endmacro()

macro(LOAD_AND_COMPILE_RUBY_FOLDER arg_name arg_path arg_file arg_module)

	file(GLOB_RECURSE RUBYSCRIPTS_${arg_name} "${CMAKE_SOURCE_DIR}/scripts/${arg_path}/*.rb")

	if(CMAKE_BUILD_TYPE STREQUAL "Debug")

		install(DIRECTORY DESTINATION ${CMAKE_BINARY_DIR}/${arg_path})

	endif()
	
	foreach(RUBYSCRIPT_${arg_name} ${RUBYSCRIPTS_${arg_name}})

		get_filename_component(${arg_name}_SCRIPT_NAME ${RUBYSCRIPT_${arg_name}} NAME_WE)
		string(REPLACE "${CMAKE_SOURCE_DIR}/scripts/${arg_path}/" "" TRUNCATED_SCRIPT_NAME ${RUBYSCRIPT_${arg_name}})

		if(CMAKE_BUILD_TYPE STREQUAL "Debug")

			configure_file(
				${RUBYSCRIPT_${arg_name}}
				${CMAKE_BINARY_DIR}/scripts/${arg_path}/${TRUNCATED_SCRIPT_NAME}
			)

		else()

			set(COMPILED_RUBY_${arg_name}_SCRIPTS ${RUBYSCRIPT_${arg_name}} ${COMPILED_RUBY_${arg_name}_SCRIPTS})

		endif()

	endforeach(RUBYSCRIPT_${arg_name})

	COMPILE_RUBY_SCRIPTS(${arg_name} ${arg_file} ${arg_module})

endmacro()

macro(LOAD_AND_COMPILE_RUBY_SCRIPT arg_name arg_path arg_file arg_module)

	if(CMAKE_BUILD_TYPE STREQUAL "Debug")

		configure_file(
			${RUBY_${arg_name}_SCRIPT}
			${CMAKE_BINARY_DIR}/scripts/${arg_path}/${arg_module}.rb
		)

	else()

		set(COMPILED_RUBY_${arg_name}_SCRIPTS ${RUBY_${arg_name}_SCRIPT})

	endif()
		
	COMPILE_RUBY_SCRIPTS(${arg_name} ${arg_file} ${arg_module})

endmacro()

# Load and compile all ruby script folders and single scripts

LOAD_AND_COMPILE_RUBY_FOLDER(INCLUDE include include Include)
LOAD_AND_COMPILE_RUBY_FOLDER(CORE core core Core)
LOAD_AND_COMPILE_RUBY_FOLDER(CUSTOM_RESOURCES custom/resources custom_resources CustomResources)
LOAD_AND_COMPILE_RUBY_FOLDER(CUSTOM_SCENES custom/scenes custom_scenes CustomScenes)
LOAD_AND_COMPILE_RUBY_FOLDER(CUSTOM_ENTITIES custom/entities custom_entities CustomEntities)
LOAD_AND_COMPILE_RUBY_FOLDER(CUSTOM_OTHER custom/other custom_other CustomOther)

LOAD_AND_COMPILE_RUBY_SCRIPT(GAME custom custom_game Game)
LOAD_AND_COMPILE_RUBY_SCRIPT(MAIN custom custom_main Main)

# Add external libraries from the SFML source directory

if(WIN32)

	if(CMAKE_SIZEOF_VOID_P EQUAL 8)

		file(COPY ${CMAKE_SOURCE_DIR}/SFML/extlibs/bin/x64/openal32.dll
		DESTINATION ${CMAKE_BINARY_DIR})

	else()

		file(COPY ${CMAKE_SOURCE_DIR}/SFML/extlibs/bin/x86/openal32.dll
		DESTINATION ${CMAKE_BINARY_DIR})

	endif()
	
endif()

# Copy all asset files and preserve their tree structure

file(GLOB_RECURSE ASSET_FILES "${CMAKE_SOURCE_DIR}/assets/*.*")

foreach(ASSET_FILE ${ASSET_FILES})

	string(REPLACE "${CMAKE_SOURCE_DIR}/" "" TRUNCATED_ASSET_FILE ${ASSET_FILE})

	configure_file(
	
		${TRUNCATED_ASSET_FILE}
		${TRUNCATED_ASSET_FILE}

	COPYONLY)

endforeach(ASSET_FILE)

# Source files

set(AUDIO_SOURCES
	Shidacea/audio/Music.cpp
)

set(GRAPHICS_SOURCES
	Shidacea/graphics/ResourceManager.cpp
	Shidacea/graphics/RenderStates.cpp
	Shidacea/graphics/View.cpp
	Shidacea/graphics/Window.cpp
	Shidacea/graphics/Texture.cpp
	Shidacea/graphics/Sprite.cpp
	Shidacea/graphics/ImGuiWrapper.cpp
)

set(NETWORK_SOURCES
	Shidacea/network/Socket.cpp
	Shidacea/network/Listener.cpp
)

set(MAP_SOURCES
	Shidacea/map/Tile.cpp
	Shidacea/map/Tileset.cpp
	Shidacea/map/MapLayer.cpp
)

set(CORE_SOURCES
	Shidacea/core/IntRect.cpp
	Shidacea/core/FloatRect.cpp
	Shidacea/core/Coordinates.cpp
	Shidacea/core/Events.cpp
	Shidacea/core/Shape.cpp
	Shidacea/core/Collisions.cpp
)

set(SCRIPTING_SOURCES
	Shidacea/scripting/Helper.cpp
)

include_directories(
	Shidacea/core 
	Shidacea/audio
	Shidacea/graphics
	Shidacea/network
	Shidacea/map
	Shidacea/scripting
)

# Load source files

set(SOURCES 
	${AUDIO_SOURCES}
	${GRAPHICS_SOURCES}
	${NETWORK_SOURCES}
	${MAP_SOURCES}
	${CORE_SOURCES}
	${SCRIPTING_SOURCES}
	Main.cpp
)

# Create executable and link libraries

add_executable(${EXECUTABLE_NAME} ${SOURCES})
add_dependencies(${EXECUTABLE_NAME} mruby ${RUBY_COMPILED_TARGETS})
target_link_libraries(${EXECUTABLE_NAME} ${MRUBY_LIBRARIES} ImGui-SFML::ImGui-SFML sfml-system sfml-window sfml-graphics sfml-audio sfml-network ${ADDITIONAL_LIBRARIES})

configure_file(
	Changelog.txt
	Changelog.txt
)