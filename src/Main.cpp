#include "Main.h"

int main(int argc, char** argv) {

	if (argc > 1) {

		for (int arg = 1; arg < argc; arg++) {

			auto argument = argv[arg];

			if (!strncmp(argument, "-v", 2) || !strncmp(argument, "--version", 9)) {

				std::cout << "Shidacea Version: " << SHIDACEA_VERSION << std::endl;

			}

		}

		return 0;
	}

	//! Load wrapped classes and Ruby scripts
	//! These are the fundament of Shidacea, so you should know what you're doing if you change these

	auto mrb = mrb_open();
	auto sdc_module = mrb_define_module(mrb, "SDC");
	
	setup_ruby_script_module(mrb, sdc_module);

#ifndef SHIDACEA_EXCLUDE_SFML

	setup_ruby_class_intrect(mrb, sdc_module);
	setup_ruby_class_floatrect(mrb, sdc_module);

	setup_ruby_class_render_states(mrb, sdc_module);

	setup_ruby_class_coordinates(mrb, sdc_module);
	
	setup_ruby_collider(mrb, sdc_module);

	setup_ruby_events(mrb, sdc_module);
	setup_ruby_class_event(mrb, sdc_module);

	setup_ruby_class_music(mrb, sdc_module);
	setup_ruby_class_sound_buffer(mrb, sdc_module);
	setup_ruby_class_sound(mrb, sdc_module);

	setup_ruby_class_color(mrb, sdc_module);
	setup_ruby_class_draw_shape(mrb, sdc_module);
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

#ifndef SHIDACEA_EXCLUDE_IMGUI

	setup_ruby_imgui(mrb, sdc_module);

#endif

#endif

#ifndef SHIDACEA_EXCLUDE_SDCLIB

	//! Load SDCLib core scripts

	load_sdclib_scripts(mrb);

#endif

#ifdef SHIDACEA_MOD_LOADING

	//! Load potential mods

	MrbWrap::load_mods(mrb);

#endif

	//! Start main script with the game loop

	load_frontend_scripts(mrb);

	//! Clean up the Ruby interpreter

	mrb_close(mrb);

}
