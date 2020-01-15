#include "Helper.h"

void MrbWrap::execute_string(mrb_state* mrb, std::string const& code) {

	mrb_load_string(mrb, code.c_str());

}

void MrbWrap::execute_bytecode_file(mrb_state* mrb, std::string const& filename) {

	auto f = fopen(filename.c_str(), "r");
	
	if (!f) {

		//! TODO: Error handling

	}

	mrb_load_irep_file(mrb, f);

	if(f) fclose(f);

}

void MrbWrap::execute_bytecode(mrb_state* mrb, const uint8_t* symbol_array) {

	mrb_load_irep(mrb, symbol_array);

}

void MrbWrap::execute_script_file(mrb_state* mrb, std::string const& filename) {

	auto f = fopen(filename.c_str(), "r");

	if (!f) {

		std::cerr << "ERROR loading file: " << filename << std::endl;
		//! TODO: Error handling

	}

	auto new_context = mrbc_context_new(mrb);
	mrbc_filename(mrb, new_context, filename.c_str());
	mrb_load_file_cxt(mrb, f, new_context);

	if (mrb->exc) {
		mrb_print_error(mrb);
	}

	if(f) fclose(f);

}

void MrbWrap::load_mods(mrb_state* mrb) {

	auto current_path = std::filesystem::current_path();
	auto mod_path = current_path / "mods";

	if (!std::filesystem::exists(mod_path)) {

		std::clog << "No mod folder found." << std::endl;

	}
	else {

		std::clog << "Mod folder found. Loading mod files..." << std::endl;

		for (const auto& entry : std::filesystem::recursive_directory_iterator(mod_path)) {

			if (std::filesystem::is_directory(entry)) continue;

			std::cout << "Loading file: " << entry << std::endl;
			const std::string str = entry.path().string();
			MrbWrap::execute_script_file(mrb, str);

		}

	}

}

void MrbWrap::load_all_scripts_recursively(mrb_state* mrb, std::string path) {

	auto current_path = std::filesystem::current_path();
	auto complete_path = current_path / path;

	if (!std::filesystem::exists(complete_path)) {

		//! TODO: Error message

	} else {

		for(const auto& entry : std::filesystem::recursive_directory_iterator(complete_path)) {

			if(std::filesystem::is_directory(entry)) continue;

			const std::string filename = entry.path().string();
			MrbWrap::execute_script_file(mrb, filename);

		}

	}

}

RClass* MrbWrap::define_data_class(mrb_state* mrb, const char* name, RClass* super_class) {

	if (!super_class) super_class = mrb->object_class;

	auto ruby_class = mrb_define_class(mrb, name, super_class);
	MRB_SET_INSTANCE_TT(ruby_class, MRB_TT_DATA);

	return ruby_class;

}

RClass* MrbWrap::define_data_class_under(mrb_state* mrb, const char* name, RClass* ruby_module, RClass* super_class) {

	if (!super_class) super_class = mrb->object_class;

	auto ruby_class = mrb_define_class_under(mrb, ruby_module, name, super_class);
	MRB_SET_INSTANCE_TT(ruby_class, MRB_TT_DATA);

	return ruby_class;

}

void MrbWrap::define_mruby_function(mrb_state* mrb, RClass* ruby_class, const char* name, mrb_value(*func)(mrb_state* mrb, mrb_value self) noexcept, mrb_aspec aspec) {

	mrb_define_method(mrb, ruby_class, name, func, aspec);

}

template <> mrb_value MrbWrap::cast_value_to_ruby(mrb_state* mrb, mrb_float value) { return mrb_float_value(mrb, value); }
template <> mrb_value MrbWrap::cast_value_to_ruby(mrb_state* mrb, mrb_int value) { return mrb_fixnum_value(value); }
template <> mrb_value MrbWrap::cast_value_to_ruby(mrb_state* mrb, mrb_bool value) { return mrb_bool_value(value); }