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

file(GLOB_RECURSE RUBYSCRIPTS_INCLUDE "${CMAKE_SOURCE_DIR}/scripts/include/*.rb")
file(GLOB_RECURSE RUBYSCRIPTS_CORE "${CMAKE_SOURCE_DIR}/scripts/core/*.rb")
file(GLOB_RECURSE RUBYSCRIPTS_CUSTOM_RESOURCES "${CMAKE_SOURCE_DIR}/scripts/custom/resources/*.rb")
file(GLOB_RECURSE RUBYSCRIPTS_CUSTOM_SCENES "${CMAKE_SOURCE_DIR}/scripts/custom/scenes/*.rb")
file(GLOB_RECURSE RUBYSCRIPTS_CUSTOM_ENTITIES "${CMAKE_SOURCE_DIR}/scripts/custom/entities/*.rb")
file(GLOB_RECURSE RUBYSCRIPTS_CUSTOM_OTHER "${CMAKE_SOURCE_DIR}/scripts/custom/other/*.rb")

set(RUBY_MAIN_SCRIPT "${CMAKE_SOURCE_DIR}/scripts/custom/Main.rb")
set(RUBY_GAME_SCRIPT "${CMAKE_SOURCE_DIR}/scripts/custom/Game.rb")

# If this is a debug build, copy the ruby files to the build directory
# Otherwise compile them to bytecode

include_directories(${CMAKE_BINARY_DIR})

set(RUBY_COMPILED_TARGETS "")

if(CMAKE_BUILD_TYPE STREQUAL "Debug")

	install(DIRECTORY DESTINATION ${CMAKE_BINARY_DIR}/scripts)
	install(DIRECTORY DESTINATION ${CMAKE_BINARY_DIR}/scripts/include)
	install(DIRECTORY DESTINATION ${CMAKE_BINARY_DIR}/scripts/core)
	install(DIRECTORY DESTINATION ${CMAKE_BINARY_DIR}/scripts/custom/resources)
	install(DIRECTORY DESTINATION ${CMAKE_BINARY_DIR}/scripts/custom/scenes)
	install(DIRECTORY DESTINATION ${CMAKE_BINARY_DIR}/scripts/custom/entities)
	install(DIRECTORY DESTINATION ${CMAKE_BINARY_DIR}/scripts/custom/other)

endif()

foreach(RUBYSCRIPT_INCLUDE ${RUBYSCRIPTS_INCLUDE})

	get_filename_component(INCLUDE_SCRIPT_NAME ${RUBYSCRIPT_INCLUDE} NAME_WE)
	string(REPLACE "${CMAKE_SOURCE_DIR}/scripts/include/" "" TRUNCATED_SCRIPT_NAME ${RUBYSCRIPT_INCLUDE})

	if(CMAKE_BUILD_TYPE STREQUAL "Debug")

		configure_file(
			${RUBYSCRIPT_INCLUDE}
			${CMAKE_BINARY_DIR}/scripts/include/${TRUNCATED_SCRIPT_NAME}
		)

	else()

		set(COMPILED_RUBY_INCLUDE_SCRIPTS ${RUBYSCRIPT_INCLUDE} ${COMPILED_RUBY_INCLUDE_SCRIPTS})

	endif()

endforeach(RUBYSCRIPT_INCLUDE)

foreach(RUBYSCRIPT_CORE ${RUBYSCRIPTS_CORE})

	get_filename_component(CORE_SCRIPT_NAME ${RUBYSCRIPT_CORE} NAME_WE)
	string(REPLACE "${CMAKE_SOURCE_DIR}/scripts/core/" "" TRUNCATED_SCRIPT_NAME ${RUBYSCRIPT_CORE})

	if(CMAKE_BUILD_TYPE STREQUAL "Debug")

		configure_file(
			${RUBYSCRIPT_CORE}
			${CMAKE_BINARY_DIR}/scripts/core/${TRUNCATED_SCRIPT_NAME}
		)

	else()

		set(COMPILED_RUBY_CORE_SCRIPTS ${RUBYSCRIPT_CORE} ${COMPILED_RUBY_CORE_SCRIPTS})

	endif()

endforeach(RUBYSCRIPT_CORE)

foreach(RUBYSCRIPT_RESOURCE ${RUBYSCRIPTS_CUSTOM_RESOURCES})

	get_filename_component(CORE_SCRIPT_NAME ${RUBYSCRIPT_RESOURCE} NAME_WE)
	string(REPLACE "${CMAKE_SOURCE_DIR}/scripts/custom/resources/" "" TRUNCATED_SCRIPT_NAME ${RUBYSCRIPT_RESOURCE})

	if(CMAKE_BUILD_TYPE STREQUAL "Debug")

		configure_file(
			${RUBYSCRIPT_RESOURCE}
			${CMAKE_BINARY_DIR}/scripts/custom/resources/${TRUNCATED_SCRIPT_NAME}
		)

	else()

		set(COMPILED_RUBY_CUSTOM_RESOURCES_SCRIPTS ${RUBYSCRIPT_RESOURCE} ${COMPILED_RUBY_CUSTOM_RESOURCES_SCRIPT})

	endif()

endforeach(RUBYSCRIPT_RESOURCE)

foreach(RUBYSCRIPT_SCENE ${RUBYSCRIPTS_CUSTOM_SCENES})

	get_filename_component(CORE_SCRIPT_NAME ${RUBYSCRIPT_SCENE} NAME_WE)
	string(REPLACE "${CMAKE_SOURCE_DIR}/scripts/custom/scenes/" "" TRUNCATED_SCRIPT_NAME ${RUBYSCRIPT_SCENE})

	if(CMAKE_BUILD_TYPE STREQUAL "Debug")

		configure_file(
			${RUBYSCRIPT_SCENE}
			${CMAKE_BINARY_DIR}/scripts/custom/scenes/${TRUNCATED_SCRIPT_NAME}
		)

	else()

		set(COMPILED_RUBY_CUSTOM_SCENES_SCRIPTS ${RUBYSCRIPT_SCENE} ${COMPILED_RUBY_CUSTOM_SCENES_SCRIPTS})

	endif()

endforeach(RUBYSCRIPT_SCENE)

foreach(RUBYSCRIPT_ENTITY ${RUBYSCRIPTS_CUSTOM_ENTITIES})

	get_filename_component(CORE_SCRIPT_NAME ${RUBYSCRIPT_ENTITY} NAME_WE)
	string(REPLACE "${CMAKE_SOURCE_DIR}/scripts/custom/entities/" "" TRUNCATED_SCRIPT_NAME ${RUBYSCRIPT_ENTITY})

	if(CMAKE_BUILD_TYPE STREQUAL "Debug")

		configure_file(
			${RUBYSCRIPT_ENTITY}
			${CMAKE_BINARY_DIR}/scripts/custom/entities/${TRUNCATED_SCRIPT_NAME}
		)

	else()

		set(COMPILED_RUBY_CUSTOM_ENTITIES_SCRIPTS ${RUBYSCRIPT_ENTITY} ${COMPILED_RUBY_CUSTOM_ENTITIES_SCRIPTS})

	endif()

endforeach(RUBYSCRIPT_ENTITY)

foreach(RUBYSCRIPT_OTHER ${RUBYSCRIPTS_CUSTOM_OTHER})

	get_filename_component(CORE_SCRIPT_NAME ${RUBYSCRIPT_OTHER} NAME_WE)
	string(REPLACE "${CMAKE_SOURCE_DIR}/scripts/custom/other/" "" TRUNCATED_SCRIPT_NAME ${RUBYSCRIPT_OTHER})

	if(CMAKE_BUILD_TYPE STREQUAL "Debug")

		configure_file(
			${RUBYSCRIPT_OTHER}
			${CMAKE_BINARY_DIR}/scripts/custom/other/${TRUNCATED_SCRIPT_NAME}
		)

	else()

		set(COMPILED_RUBY_CUSTOM_OTHER_SCRIPTS ${RUBYSCRIPT_OTHER} ${COMPILED_RUBY_CUSTOM_OTHER_SCRIPT})

	endif()

endforeach(RUBYSCRIPT_OTHER)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")

		configure_file(
			${RUBY_MAIN_SCRIPT}
			${CMAKE_BINARY_DIR}/scripts/custom/Main.rb
		)

		configure_file(
			${RUBY_GAME_SCRIPT}
			${CMAKE_BINARY_DIR}/scripts/custom/Game.rb
		)

endif()

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

# Compile ruby scripts if necessary

if(NOT CMAKE_BUILD_TYPE STREQUAL "Debug")

	add_custom_target(TargetRubyInclude
		COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/compiled_scripts
		COMMAND ${CMAKE_BINARY_DIR}/mruby/bin/mrbc -g -Bcompiled_ruby_include -o ${CMAKE_BINARY_DIR}/compiled_scripts/CompiledRubyInclude.h ${COMPILED_RUBY_INCLUDE_SCRIPTS}
		DEPENDS ${COMPILED_RUBY_INCLUDE_SCRIPTS} mruby
		VERBATIM
	)

	add_custom_target(TargetRubyCore
		COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/compiled_scripts
		COMMAND ${CMAKE_BINARY_DIR}/mruby/bin/mrbc -g -Bcompiled_ruby_core -o ${CMAKE_BINARY_DIR}/compiled_scripts/CompiledRubyCore.h ${COMPILED_RUBY_CORE_SCRIPTS}
		DEPENDS ${COMPILED_RUBY_CORE_SCRIPTS} mruby
		VERBATIM
	)

	add_custom_target(TargetRubyCustomResources
		COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/compiled_scripts
		COMMAND ${CMAKE_BINARY_DIR}/mruby/bin/mrbc -g -Bcompiled_ruby_custom_resources -o ${CMAKE_BINARY_DIR}/compiled_scripts/CompiledRubyCustomResources.h ${COMPILED_RUBY_CUSTOM_RESOURCES_SCRIPTS}
		DEPENDS ${COMPILED_RUBY_CUSTOM_RESOURCES_SCRIPTS} mruby
		VERBATIM
	)

	add_custom_target(TargetRubyCustomScenes
		COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/compiled_scripts
		COMMAND ${CMAKE_BINARY_DIR}/mruby/bin/mrbc -g -Bcompiled_ruby_custom_scenes -o ${CMAKE_BINARY_DIR}/compiled_scripts/CompiledRubyCustomScenes.h ${COMPILED_RUBY_CUSTOM_SCENES_SCRIPTS}
		DEPENDS ${COMPILED_RUBY_CUSTOM_SCENES_SCRIPTS} mruby
		VERBATIM
	)

	add_custom_target(TargetRubyCustomEntities
		COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/compiled_scripts
		COMMAND ${CMAKE_BINARY_DIR}/mruby/bin/mrbc -g -Bcompiled_ruby_custom_entities -o ${CMAKE_BINARY_DIR}/compiled_scripts/CompiledRubyCustomEntities.h ${COMPILED_RUBY_CUSTOM_ENTITIES_SCRIPTS}
		DEPENDS ${COMPILED_RUBY_CUSTOM_ENTITIES_SCRIPTS} mruby
		VERBATIM
	)

	add_custom_target(TargetRubyCustomOther
		COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/compiled_scripts
		COMMAND ${CMAKE_BINARY_DIR}/mruby/bin/mrbc -g -Bcompiled_ruby_custom_other -o ${CMAKE_BINARY_DIR}/compiled_scripts/CompiledRubyCustomOther.h ${COMPILED_RUBY_CUSTOM_OTHER_SCRIPTS}
		DEPENDS ${COMPILED_RUBY_CUSTOM_OTHER_SCRIPTS} mruby
		VERBATIM
	)

	add_custom_target(TargetRubyMain
		COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/compiled_scripts
		COMMAND ${CMAKE_BINARY_DIR}/mruby/bin/mrbc -g -Bcompiled_ruby_main -o ${CMAKE_BINARY_DIR}/compiled_scripts/CompiledRubyMain.h ${RUBY_MAIN_SCRIPT}
		DEPENDS ${RUBY_MAIN_SCRIPT} mruby
		VERBATIM
	)

	add_custom_target(TargetRubyGame
		COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/compiled_scripts
		COMMAND ${CMAKE_BINARY_DIR}/mruby/bin/mrbc -g -Bcompiled_ruby_game -o ${CMAKE_BINARY_DIR}/compiled_scripts/CompiledRubyGame.h ${RUBY_GAME_SCRIPT}
		DEPENDS ${RUBY_GAME_SCRIPT} mruby
		VERBATIM
	)

	set(RUBY_COMPILED_TARGETS TTargetRubyInclude argetRubyCore TargetRubyCustomResources TargetRubyCustomScenes TargetRubyCustomEntities TargetRubyCustomOther TargetRubyMain TargetRubyGame ${RUBY_COMPILED_TARGETS})

endif()

# Copy all asset files and preserve their tree structure

file(GLOB_RECURSE ASSET_FILES "${CMAKE_SOURCE_DIR}/assets/*.*")

message(${ASSET_FILES})

set(TRUNCATED_ASSET_NAMES "")

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