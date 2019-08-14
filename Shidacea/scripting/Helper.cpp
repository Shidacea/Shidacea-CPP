#include "Helper.h"

void MrbWrap::execute_string(mrb_state* mrb, std::string const& code) {

	mrb_load_string(mrb, code.c_str());

}

void MrbWrap::execute_bytecode_file(mrb_state* mrb, std::string const& filename) {

	FILE* f;
	auto error_code = fopen_s(&f, filename.c_str(), "r");
	
	if (error_code != 0) {

		//! TODO: Error handling

	}

	mrb_load_irep_file(mrb, f);

	if(f) fclose(f);

}

void MrbWrap::execute_bytecode(mrb_state* mrb, const uint8_t* symbol_array) {

	mrb_load_irep(mrb, symbol_array);

}

void MrbWrap::execute_script_file(mrb_state* mrb, std::string const& filename) {

	FILE* f;
	auto error_code = fopen_s(&f, filename.c_str(), "r");

	if (error_code != 0) {

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
	auto mod_path = current_path / "scripts" / "mods";

	if (!std::filesystem::exists(mod_path)) {

		std::clog << "No mod folder found." << std::endl;

	}
	else {

		std::clog << "Mod folder found. Loading mod files..." << std::endl;

		for (const auto& entry : std::filesystem::recursive_directory_iterator(mod_path)) {

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