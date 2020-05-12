#include "MrbLoad.h"

#include <iostream>

//! TODO: Add consistent log messages

void MrbLoad::execute_string(mrb_state* mrb, std::string const& code) {

	mrb_load_string(mrb, code.c_str());

}

void MrbLoad::execute_bytecode_file(mrb_state* mrb, std::string const& filename) {

	auto f = fopen(filename.c_str(), "r");

	if (!f) {

	}

	mrb_load_irep_file(mrb, f);

	if (f) fclose(f);

}

void MrbLoad::execute_bytecode(mrb_state* mrb, const uint8_t* symbol_array) {

	mrb_load_irep(mrb, symbol_array);

}

void MrbLoad::execute_script_file(mrb_state* mrb, std::string const& filename) {

	auto f = fopen(filename.c_str(), "r");

	if (!f) {

	}

	auto new_context = mrbc_context_new(mrb);
	mrbc_filename(mrb, new_context, filename.c_str());
	mrb_load_file_cxt(mrb, f, new_context);

	if (mrb->exc) {
		mrb_print_error(mrb);
	}

	if (f) fclose(f);

}

void MrbLoad::load_mods(mrb_state* mrb) {

	auto current_path = std::filesystem::current_path();
	auto mod_path = current_path / "mods";

	if (!std::filesystem::exists(mod_path)) {

	}
	else {

		for (const auto& entry : std::filesystem::recursive_directory_iterator(mod_path)) {

			if (std::filesystem::is_directory(entry)) continue;

			const std::string str = entry.path().string();
			MrbLoad::execute_script_file(mrb, str);

		}

	}

}

void MrbLoad::load_all_scripts_recursively(mrb_state* mrb, std::string path) {

	auto current_path = std::filesystem::current_path();
	auto complete_path = current_path / path;

	if (!std::filesystem::exists(complete_path)) {

	}
	else {

		for (const auto& entry : std::filesystem::recursive_directory_iterator(complete_path)) {

			if (std::filesystem::is_directory(entry)) continue;

			const std::string filename = entry.path().string();
			MrbLoad::execute_script_file(mrb, filename);

		}

	}

}
