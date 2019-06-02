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

		//! TODO: Error handling

	}

	mrb_load_file(mrb, f);

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

		for (const auto& entry : std::filesystem::directory_iterator(mod_path)) {

			std::cout << "Loading file: " << entry << std::endl;
			const std::string str = entry.path().string();
			MrbWrap::execute_script_file(mrb, str);

		}

	}

}