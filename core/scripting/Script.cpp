#include "Script.h"

void setup_ruby_script_module(mrb_state* mrb, RClass* ruby_module) {

	auto script_module = mrb_define_module_under(mrb, ruby_module, "Script");

	mrb_define_module_function(mrb, script_module, "load", MRUBY_FUNC {

		auto args = MrbWrap::get_converted_args<std::string>(mrb);
		auto filename = std::get<0>(args);

		MrbWrap::execute_script_file(mrb, filename);

		return mrb_true_value();

	}, MRB_ARGS_REQ(1));

	mrb_define_module_function(mrb, script_module, "load_recursively", MRUBY_FUNC {

		auto args = MrbWrap::get_converted_args<std::string>(mrb);
		auto path = std::get<0>(args);

		MrbWrap::load_all_scripts_recursively(mrb, path);

		return mrb_true_value();

	}, MRB_ARGS_REQ(1));

	mrb_define_module_function(mrb, script_module, "path=", MRUBY_FUNC{

		//! TODO

		return mrb_nil_value();

	}, MRB_ARGS_REQ(1));

}