cmake_minimum_required(VERSION 3.5)

macro(COMPILE_RUBY_SCRIPTS arg_name arg_file arg_module flag)

	if(${flag})

		message("Preparing header file: ${REGULAR_BINARY_DIR}/compiled_scripts/${arg_module}.h")
		execute_process(COMMAND ${REGULAR_BINARY_DIR}/third_party/mruby/bin/mrbc -g -Bcompiled_ruby_${arg_module} -o ${REGULAR_BINARY_DIR}/compiled_scripts/${arg_module}.h ${COMPILED_RUBY_${arg_name}_SCRIPTS})

	endif()

endmacro()

macro(LOAD_AND_COMPILE_RUBY_FOLDER arg_name arg_path arg_file arg_module flag)

	message("Checking folder: ${REGULAR_SOURCE_DIR}/${arg_path}/${arg_file}")

	file(GLOB_RECURSE RUBYSCRIPTS_${arg_name} "${REGULAR_SOURCE_DIR}/${arg_path}/${arg_file}*.rb")

	if(NOT ${flag})

		file(MAKE_DIRECTORY ${REGULAR_BINARY_DIR}/${arg_path})

	endif()
	
	foreach(RUBYSCRIPT_${arg_name} ${RUBYSCRIPTS_${arg_name}})

		get_filename_component(${arg_name}_SCRIPT_NAME ${RUBYSCRIPT_${arg_name}} NAME_WE)
		string(REPLACE "${REGULAR_SOURCE_DIR}/${arg_path}/" "" TRUNCATED_SCRIPT_NAME ${RUBYSCRIPT_${arg_name}})

		if(NOT ${flag})

			message("Copying file: ${RUBYSCRIPT_${arg_name}}")

			configure_file(
				${RUBYSCRIPT_${arg_name}}
				${REGULAR_BINARY_DIR}/${arg_path}/${TRUNCATED_SCRIPT_NAME}
			)

		else()

			message("Adding ${RUBYSCRIPT_${arg_name}} to list")
			set(COMPILED_RUBY_${arg_name}_SCRIPTS ${RUBYSCRIPT_${arg_name}} ${COMPILED_RUBY_${arg_name}_SCRIPTS})

		endif()

	endforeach(RUBYSCRIPT_${arg_name})

	COMPILE_RUBY_SCRIPTS(${arg_name} ${arg_file} ${arg_module} ${flag})

endmacro()

macro(LOAD_AND_COMPILE_RUBY_SCRIPT arg_name arg_path arg_file arg_module flag)

	if(NOT ${flag})

		message("Copying file: ${REGULAR_SOURCE_DIR}/${arg_path}/${arg_file}.rb")

		configure_file(
			${REGULAR_SOURCE_DIR}/${arg_path}/${arg_file}
			${REGULAR_BINARY_DIR}/${arg_path}/${arg_file}
		)

	else()

		set(COMPILED_RUBY_${arg_name}_SCRIPTS ${REGULAR_SOURCE_DIR}/${arg_path}/${arg_file})

	endif()
		
	COMPILE_RUBY_SCRIPTS(${arg_name} ${arg_file} ${arg_module} ${flag})

endmacro()

file(STRINGS ${SCRIPT_FILE} SCRIPTS_TO_LOAD)

set(SCRIPT_COUNTER 0)
foreach(SCRIPT_TO_LOAD ${SCRIPTS_TO_LOAD})

	message("${SCRIPT_TO_LOAD} is ${SCRIPT_COUNTER}")
	
	if(IS_DIRECTORY "${REGULAR_SOURCE_DIR}/${LOAD_DIR}/${SCRIPT_TO_LOAD}")

		LOAD_AND_COMPILE_RUBY_FOLDER(script_frontend_${SCRIPT_COUNTER} ${LOAD_DIR} ${SCRIPT_TO_LOAD} script_${COMPILATION_NAME}_${SCRIPT_COUNTER} ${COMPILE_THIS})

	else()

		LOAD_AND_COMPILE_RUBY_SCRIPT(script_frontend_${SCRIPT_COUNTER} ${LOAD_DIR} ${SCRIPT_TO_LOAD} script_${COMPILATION_NAME}_${SCRIPT_COUNTER} ${COMPILE_THIS})

	endif()

	math(EXPR SCRIPT_COUNTER "${SCRIPT_COUNTER}+1")

endforeach(SCRIPT_TO_LOAD)
