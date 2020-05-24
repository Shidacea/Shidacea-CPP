# Minimum cmake version

cmake_minimum_required(VERSION 3.5)

# Project name

project(NewProject)
set(EXECUTABLE_NAME "Launshi")
set(FRONTEND_DIRECTORY "third_party/Launshi")
set(SDCLIB_DIRECTORY "lib")

# Compilation options

option(SHIDACEA_EXCLUDE_SDCLIB "Excludes extended SDC module under lib from Shidacea" OFF)
option(SHIDACEA_COMPILE_SDCLIB "Compiles the SDC module scripts under lib" OFF)
option(SHIDACEA_COMPILE_FRONTEND "Compiles the Shidacea frontend core and custom scripts" OFF)
option(SHIDACEA_EXCLUDE_IMGUI "Excludes ImGui from Shidacea" OFF)
option(SHIDACEA_IGNORE_STATIC_ASSERTIONS "Ignores static assertions" OFF)
option(SHIDACEA_EXCLUDE_SFML "Excludes SFML from Shidacea" OFF)

# Compile flags

set(CMAKE_SHARED_LINKER_FLAGS
    "${CMAKE_SHARED_LINKER_FLAGS}")

set(CMAKE_EXE_LINKER_FLAGS
    "${CMAKE_EXE_LINKER_FLAGS}")

# Define platform dependent libraries

if(WIN32)

	add_definitions(-Dssize_t=int)

	if(NOT SHIDACEA_EXCLUDE_SFML)

		set(ADDITIONAL_LIBRARIES sfml-main Ws2_32)

	else()

		set(ADDITIONAL_LIBRARIES Ws2_32)

	endif()
	
	set(MRUBY_LIBRARIES "${CMAKE_BINARY_DIR}/third_party/mruby/lib/libmruby.lib" "${CMAKE_BINARY_DIR}/third_party/mruby/lib/libmruby_core.lib")

else()

	set(ADDITIONAL_LIBRARIES stdc++fs)
	set(MRUBY_LIBRARIES "${CMAKE_BINARY_DIR}/third_party/mruby/lib/libmruby.a" "${CMAKE_BINARY_DIR}/third_party/mruby/lib/libmruby_core.a")

endif()

add_definitions(-DMRB_USE_FLOAT)
add_definitions(-DMRB_UTF8_STRING)

add_definitions(-DFRONTEND_DIRECTORY="${FRONTEND_DIRECTORY}")
add_definitions(-DSDCLIB_DIRECTORY="${SDCLIB_DIRECTORY}")

if(SHIDACEA_COMPILE_SDCLIB)

	add_definitions(-DSHIDACEA_COMPILE_SDCLIB)

endif()

if(SHIDACEA_COMPILE_FRONTEND)

	add_definitions(-DSHIDACEA_COMPILE_FRONTEND)

endif()

if(SHIDACEA_EXCLUDE_SDCLIB)

	add_definitions(-DSHIDACEA_EXCLUDE_SDCLIB)

endif()

if(SHIDACEA_EXCLUDE_SFML)

	add_definitions(-DSHIDACEA_EXCLUDE_SFML)

endif()

if(SHIDACEA_EXCLUDE_IMGUI)

	add_definitions(-DSHIDACEA_EXCLUDE_IMGUI)

endif()

if(SHIDACEA_IGNORE_STATIC_ASSERTIONS)

	# Assertions for Collishi
	add_definitions(-DIGNORE_STATIC_ASSERTIONS)

endif()

include(${CMAKE_ROOT}/Modules/ExternalProject.cmake)

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

if(NOT SHIDACEA_EXCLUDE_SFML)

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

endif()

# Setup directories

include_directories(${CMAKE_BINARY_DIR})

if(NOT SHIDACEA_COMPILE_FRONTEND)

	install(DIRECTORY DESTINATION ${CMAKE_BINARY_DIR}/scripts_include)
	install(DIRECTORY DESTINATION ${CMAKE_BINARY_DIR}/scripts_core)
	install(DIRECTORY DESTINATION ${CMAKE_BINARY_DIR}/scripts_custom)

endif()

if(NOT SHIDACEA_COMPILE_SDCLIB)

	install(DIRECTORY DESTINATION ${CMAKE_BINARY_DIR}/sdclib)

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
			|| ${CMAKE_BINARY_DIR}/third_party/mruby/bin/mrbc -g -Bcompiled_ruby_${arg_file} -o ${CMAKE_BINARY_DIR}/compiled_scripts/CompiledRuby${arg_module}.h ${CMAKE_SOURCE_DIR}/src/Void.rb
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

add_custom_target(FrontendInclude
	COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/compiled_scripts
	COMMAND ${CMAKE_BINARY_DIR}/third_party/mruby/bin/mruby ${CMAKE_SOURCE_DIR}/utility/script_collector.rb 
		${FRONTEND_DIRECTORY}
		${CMAKE_BINARY_DIR}/compiled_scripts/ 
		scripts_include_frontend.h 
		scripts_frontend.txt
		${CMAKE_SOURCE_DIR}/${FRONTEND_DIRECTORY}/project.json
		frontend
		SHIDACEA_COMPILE_FRONTEND
	DEPENDS mruby
	VERBATIM
)

add_custom_target(SDCLibInclude
	COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/compiled_scripts
	COMMAND ${CMAKE_BINARY_DIR}/third_party/mruby/bin/mruby ${CMAKE_SOURCE_DIR}/utility/script_collector.rb 
		${FRONTEND_DIRECTORY}
		${CMAKE_BINARY_DIR}/compiled_scripts/ 
		scripts_include_sdclib.h 
		scripts_sdclib.txt
		${CMAKE_SOURCE_DIR}/${SDCLIB_DIRECTORY}/project.json
		sdclib
		SHIDACEA_COMPILE_SDCLIB
	DEPENDS mruby
	VERBATIM
)

add_custom_target(Frontend
    COMMAND cmake -D LOAD_DIR=${FRONTEND_DIRECTORY} 
		-D SCRIPT_FILE=${CMAKE_BINARY_DIR}/compiled_scripts/scripts_frontend.txt 
		-D COMPILE_THIS=${SHIDACEA_COMPILE_FRONTEND}
		-D REGULAR_SOURCE_DIR=${CMAKE_SOURCE_DIR}
		-D REGULAR_BINARY_DIR=${CMAKE_BINARY_DIR}
		-D COMPILATION_NAME=frontend
		-P ${CMAKE_SOURCE_DIR}/utility/GenerateScripts.cmake
	DEPENDS mruby FrontendInclude
	VERBATIM
)

add_custom_target(SDCLib
    COMMAND cmake -D LOAD_DIR=${SDCLIB_DIRECTORY} 
		-D SCRIPT_FILE=${CMAKE_BINARY_DIR}/compiled_scripts/scripts_sdclib.txt 
		-D COMPILE_THIS=${SHIDACEA_COMPILE_SDCLIB}
		-D REGULAR_SOURCE_DIR=${CMAKE_SOURCE_DIR}
		-D REGULAR_BINARY_DIR=${CMAKE_BINARY_DIR}
		-D COMPILATION_NAME=sdclib
		-P ${CMAKE_SOURCE_DIR}/utility/GenerateScripts.cmake
	DEPENDS mruby SDCLibInclude
	VERBATIM
)

# Add external libraries from the SFML source directory

if(NOT SHIDACEA_EXCLUDE_SFML)

	if(WIN32)

		if(CMAKE_SIZEOF_VOID_P EQUAL 8)

			file(COPY ${CMAKE_SOURCE_DIR}/third_party/SFML/extlibs/bin/x64/openal32.dll
			DESTINATION ${CMAKE_BINARY_DIR})

		else()

			file(COPY ${CMAKE_SOURCE_DIR}/third_party/SFML/extlibs/bin/x86/openal32.dll
			DESTINATION ${CMAKE_BINARY_DIR})

		endif()
	
	endif()

endif()

# Copy all asset files and preserve their tree structure

file(GLOB_RECURSE ASSET_FILES "${CMAKE_SOURCE_DIR}/${FRONTEND_DIRECTORY}/assets/*.*")

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
	engine/audio/Music.cpp
	engine/audio/SoundBuffer.cpp
	engine/audio/Sound.cpp
)

set(GRAPHICS_SOURCES
	engine/graphics/RenderQueue.cpp
	engine/graphics/RenderQueueWindow.cpp
	engine/graphics/RenderStates.cpp
	engine/graphics/Color.cpp
	engine/graphics/View.cpp
	engine/graphics/Window.cpp
	engine/graphics/Texture.cpp
	engine/graphics/Sprite.cpp
	engine/graphics/Font.cpp
	engine/graphics/Text.cpp
	engine/graphics/DrawShape.cpp
)

set(IMGUI_SOURCES
	engine/graphics/ImGuiWrapper.cpp
)

set(NETWORK_SOURCES
	engine/network/Socket.cpp
	engine/network/Listener.cpp
)

set(MAP_SOURCES
	engine/map/Tile.cpp
	engine/map/Tileset.cpp
	engine/map/MapLayer.cpp
)

set(INTERNAL_SOURCES
	engine/internal/IntRect.cpp
	engine/internal/FloatRect.cpp
	engine/internal/Coordinates.cpp
	engine/internal/Events.cpp
	engine/internal/Shape.cpp
)

set(SCRIPTING_SOURCES
	src/MrbLoad.cpp
	src/Script.cpp
)

if(NOT SHIDACEA_EXCLUDE_SFML)

	include_directories(
		third_party/Collishi
		engine/internal 
		engine/audio
		engine/graphics
		engine/network
		engine/map
	)

endif()

include_directories(
	third_party/MrbWrap
	src
)

# Load source files

if(NOT SHIDACEA_EXCLUDE_IMGUI)
	
	set(GRAPHICS_SOURCES ${GRAPHICS_SOURCES} ${IMGUI_SOURCES})

endif()

if(SHIDACEA_EXCLUDE_SFML)

	set(SOURCE_FILES
		${SCRIPTING_SOURCES}
		src/Main.cpp
	)

else()

	set(SOURCE_FILES 
		${AUDIO_SOURCES}
		${GRAPHICS_SOURCES}
		${NETWORK_SOURCES}
		${MAP_SOURCES}
		${INTERNAL_SOURCES}
		${SCRIPTING_SOURCES}
		src/Main.cpp
	)

endif()

#set_source_files_properties(
#
#	${SOURCE_FILES}
#	COMPILE_FLAGS /Wall
#
#)

# Set libraries

if(NOT SHIDACEA_EXCLUDE_SFML)

	if(NOT SHIDACEA_EXCLUDE_IMGUI)

		set(IMGUI_LIBRARIES ImGui-SFML::ImGui-SFML)

	endif()

	set(SFML_LIBRARIES sfml-system sfml-window sfml-graphics sfml-audio sfml-network)

endif()

# Create executable and link libraries

add_executable(${EXECUTABLE_NAME} ${SOURCE_FILES})
add_dependencies(${EXECUTABLE_NAME} mruby ${RUBY_COMPILED_TARGETS} SDCLib Frontend)
target_link_libraries(${EXECUTABLE_NAME} ${MRUBY_LIBRARIES} ${IMGUI_LIBRARIES} ${SFML_LIBRARIES} ${ADDITIONAL_LIBRARIES})
