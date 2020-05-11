#include <mruby.h>
#include <mruby/dump.h>
#include <mruby/variable.h>
#include <mruby/data.h>
#include <mruby/compile.h>
#include <mruby/class.h>
#include <mruby/array.h>
#include <mruby/string.h>
#include <cstring>
#include <string>
#include <filesystem>
#include <functional>
#include <utility>

//! Preprocessor shenanigans to switch between script file loading and pre-compiled bytecode
//! Possible flags are SHIDACEA_COMPILE_ALL_SCRIPTS and SHIDACEA_COMPILE_CORE_SCRIPTS
//! If the compile flag is off, the macro will directly load the script file "scripts/XXX.rb"
//! If the compile flag is on, the macro will execute the bytecode in the respective array compiled_ruby_XXX
//! In the latter case, don't forget to include "compiled_scripts/XXX.h" (but ONLY then), or else the array will not be defined
//! Sadly, there is no easy way to circumwent the conditioned include directive
#if defined(SHIDACEA_COMPILE_ALL_SCRIPTS)
#define MRB_LOAD_SCRIPT(mrb, name, path) MrbLoad::execute_bytecode(mrb, compiled_ruby_##name)
#else
#define MRB_LOAD_SCRIPT(mrb, name, path) MrbLoad::execute_script_file(mrb, #path ".rb")
#endif

#if defined(SHIDACEA_COMPILE_CORE_SCRIPTS) || defined(SHIDACEA_COMPILE_ALL_SCRIPTS)
#define MRB_LOAD_CORE_SCRIPT(mrb, name, path) MrbLoad::execute_bytecode(mrb, compiled_ruby_##name)
#else
#define MRB_LOAD_CORE_SCRIPT(mrb, name, path) MrbLoad::execute_script_file(mrb, #path ".rb")
#endif

//! If there are any scripts in the scripts folder of the release version, load them if SHIDACEA_DYNAMIC_LOADING is set
//! This way scripts can be loaded at runtime, e.g. for a precompiled engine

#if defined(SHIDACEA_COMPILE_ALL_SCRIPTS)
#ifdef SHIDACEA_DYNAMIC_LOADING
#define MRB_LOAD_SCRIPT_FOLDER(mrb, name, path) MrbLoad::execute_bytecode(mrb, compiled_ruby_##name); \
MrbLoad::load_all_scripts_recursively(mrb, #path)
#else
#define MRB_LOAD_SCRIPT_FOLDER(mrb, name, path) MrbLoad::execute_bytecode(mrb, compiled_ruby_##name)
#endif
#else
#define MRB_LOAD_SCRIPT_FOLDER(mrb, name, path) MrbLoad::load_all_scripts_recursively(mrb, #path)
#endif

#if defined(SHIDACEA_COMPILE_CORE_SCRIPTS) || defined(SHIDACEA_COMPILE_ALL_SCRIPTS)
#ifdef SHIDACEA_DYNAMIC_LOADING
#define MRB_LOAD_CORE_SCRIPT_FOLDER(mrb, name, path) MrbLoad::execute_bytecode(mrb, compiled_ruby_##name); \
MrbLoad::load_all_scripts_recursively(mrb, #path)
#else
#define MRB_LOAD_CORE_SCRIPT_FOLDER(mrb, name, path) MrbLoad::execute_bytecode(mrb, compiled_ruby_##name)
#endif
#else
#define MRB_LOAD_CORE_SCRIPT_FOLDER(mrb, name, path) MrbLoad::load_all_scripts_recursively(mrb, #path)
#endif

namespace MrbLoad {

	//! Some different ways to execute mruby code

	//! Execute a string containing mruby code
	//! Only useful for user-generated input
	//! If C++ code needs to execute ruby commands, don't use this
	void execute_string(mrb_state* mrb, std::string const& code);

	//! Ececute a mruby script file
	//! Easiest way to execute script files, but also the slowest
	void execute_script_file(mrb_state* mrb, std::string const& filename);

	//! TODO: Future option for projects?
	//! Execute a file containing mruby bytecode
	//! WARNING: Does not work correctly for some reason, so this should NEVER be used!
	[[deprecated("May not work in many situations")]] void execute_bytecode_file(mrb_state* mrb, std::string const& filename);

	//! Execute embedded bytecode from a C array
	//! Fastest way to load a script, but needs some setup work
	void execute_bytecode(mrb_state* mrb, const uint8_t* symbol_array);

	//! Load mods
	void load_mods(mrb_state* mrb);

	//! Load all scripts in a given path
	void load_all_scripts_recursively(mrb_state* mrb, std::string path);

}