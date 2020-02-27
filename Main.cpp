#include "Main.h"

int main(int argc, char** argv) {

	if (argc > 1) {

		for (int arg = 1; arg < argc; arg++) {

			auto argument = argv[arg];

			if (!strncmp(argument, "-v", 2) || !strncmp(argument, "--version", 9)) {

				std::cout << "Shidacea Version: " << VERSION << std::endl;

			}

		}

		return 0;
	}

	auto mrb = mrb_open();
	auto sdc_module = mrb_define_module(mrb, "SDC");

	//! Load wrapped classes and Ruby scripts
	//! These are the fundament of Shidacea, so you should know what you're doing if you change these
	
	setup_ruby_class_intrect(mrb, sdc_module);
	setup_ruby_class_floatrect(mrb, sdc_module);

	setup_ruby_class_render_states(mrb, sdc_module);

	setup_ruby_class_coordinates(mrb, sdc_module);
	
	setup_ruby_collider(mrb, sdc_module);

	setup_ruby_events(mrb, sdc_module);
	setup_ruby_class_event(mrb, sdc_module);

	setup_ruby_class_music(mrb, sdc_module);

	setup_ruby_class_color(mrb, sdc_module);
	setup_ruby_class_texture(mrb, sdc_module);
	setup_ruby_class_sprite(mrb, sdc_module);
	setup_ruby_class_map_layer(mrb, sdc_module);
	setup_ruby_class_tile(mrb, sdc_module);
	setup_ruby_class_tileset(mrb, sdc_module);
	setup_ruby_class_font(mrb, sdc_module);
	setup_ruby_class_text(mrb, sdc_module);
	
	setup_ruby_class_view(mrb, sdc_module);
	setup_ruby_class_window(mrb, sdc_module);

	setup_ruby_class_socket(mrb, sdc_module);
	setup_ruby_class_listener(mrb, sdc_module);

	setup_ruby_imgui(mrb, sdc_module);

	//! Load Ruby core scripts

	MRB_LOAD_SCRIPT_FOLDER(mrb, include, scripts_include);
	MRB_LOAD_SCRIPT_FOLDER(mrb, core, scripts_core);

	//! Load main scripts
	//! If you want to add something, put it here
	//! These are ordered, so don't just put it anywhere if it depends on other scripts
	//! If you want to add compiled Ruby scripts, you also need to include them in the header file

	MRB_LOAD_SCRIPT_FOLDER(mrb, custom_resources, scripts_custom/resources);
	MRB_LOAD_SCRIPT_FOLDER(mrb, custom_scenes, scripts_custom/scenes);
	MRB_LOAD_SCRIPT_FOLDER(mrb, custom_entities, scripts_custom/entities);
	MRB_LOAD_SCRIPT_FOLDER(mrb, custom_other, scripts_custom/other);

#ifdef MOD_LOADING

	//! Load potential mods

	MrbWrap::load_mods(mrb);

#endif

	//! Load game class

	MRB_LOAD_SCRIPT(mrb, custom_game, scripts_custom/Game);

	//! Start main script with the game loop

	MRB_LOAD_SCRIPT(mrb, custom_main, scripts_custom/Main);

	//! Clean up the Ruby interpreter

	mrb_close(mrb);

}
