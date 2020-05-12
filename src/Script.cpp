#include "Script.h"

void setup_ruby_script_module(mrb_state* mrb, RClass* ruby_module) {

	auto script_module = mrb_define_module_under(mrb, ruby_module, "Script");

	//! TODO: Change this depending on compilation parameters
	mrb_mod_cv_set(mrb, script_module, mrb_intern_static(mrb, "@@_path", strlen("@@_path")), mrb_str_new_cstr(mrb, FRONTEND_DIRECTORY));

	MrbWrap::define_module_function(mrb, script_module, "load", MRUBY_FUNC {

		auto args = MrbWrap::get_converted_args<MRBW_FILE>(mrb);
		auto filename = std::get<0>(args);

		MrbLoad::execute_script_file(mrb, filename);

		return mrb_true_value();

	}, MRB_ARGS_REQ(1));

	MrbWrap::define_module_function(mrb, script_module, "load_recursively", MRUBY_FUNC {

		auto args = MrbWrap::get_converted_args<MRBW_FILE>(mrb);
		auto path = std::get<0>(args);

		MrbLoad::load_all_scripts_recursively(mrb, path);

		return mrb_true_value();

	}, MRB_ARGS_REQ(1));

	MrbWrap::define_module_function(mrb, script_module, "path", MRUBY_FUNC {

		//! TODO: Remove SDC module reference, maybe via a global function

		auto script_module = mrb_module_get_under(mrb, mrb_module_get(mrb, "SDC"), "Script");
		auto path = mrb_mod_cv_get(mrb, script_module, mrb_intern_static(mrb, "@@_path", strlen("@@_path")));

		return path;

	}, MRB_ARGS_REQ(1));

	MrbWrap::define_module_function(mrb, script_module, "path=", MRUBY_FUNC {

		auto args = MrbWrap::get_raw_args<std::string>(mrb);
		auto path = std::get<0>(args);

		auto converted_path = mrb_str_new_cstr(mrb, path);

		auto script_module = mrb_module_get_under(mrb, mrb_module_get(mrb, "SDC"), "Script");
		mrb_mod_cv_set(mrb, script_module, mrb_intern_static(mrb, "@@_path", strlen("@@_path")), converted_path);

		return converted_path;

	}, MRB_ARGS_REQ(1));

	MrbWrap::define_module_function(mrb, script_module, "version", MRUBY_FUNC{

		auto converted_string = mrb_str_new_cstr(mrb, SHIDACEA_VERSION);

		return converted_string;

	});

}