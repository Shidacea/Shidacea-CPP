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

	//! Load wrapped classes and Ruby scripts
	//! These are the fundament of Shidacea, so you should know what you're doing if you change these
	
	setup_ruby_class_intrect(mrb);

	setup_ruby_class_resource_manager(mrb);
	setup_ruby_class_render_states(mrb);

	setup_ruby_class_coordinates(mrb);
	
	setup_ruby_collider(mrb);

	setup_ruby_events(mrb);
	setup_ruby_class_event(mrb);

	setup_ruby_class_texture(mrb);
	setup_ruby_class_sprite(mrb);
	setup_ruby_class_map_layer(mrb);
	setup_ruby_class_window(mrb);

	setup_ruby_class_socket(mrb);
	setup_ruby_class_listener(mrb);

	setup_ruby_imgui(mrb);

	//! Load Ruby core scripts

	MRB_LOAD_SCRIPT_FOLDER(mrb, core, core);

	//! Load main scripts
	//! If you want to add something, put it here
	//! These are ordered, so don't just put it anywhere if it depends on other scripts
	//! If you want to add compiled Ruby scripts, you also need to include them in the header file

	MRB_LOAD_SCRIPT_FOLDER(mrb, custom_scenes, custom/scenes);
	MRB_LOAD_SCRIPT_FOLDER(mrb, custom_entities, custom/entities);

#ifdef MOD_LOADING

	//! Load potential mods

	MrbWrap::load_mods(mrb);

#endif

	//! Load game class

	MRB_LOAD_SCRIPT(mrb, game, custom/Game);

	//! Start main script with the game loop

	MRB_LOAD_SCRIPT(mrb, main, custom/Main);

	//! Clean up the Ruby interpreter

	mrb_close(mrb);

}
