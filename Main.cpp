#include "Main.h"

int main() {

	auto mrb = mrb_open();

	//! Load wrapped classes and Ruby scripts
	//! These are the core of Shidacea, so you should know what you're doing if you change these
	
	setup_ruby_class_intrect(mrb);
	setup_ruby_class_resource_manager(mrb);

	setup_ruby_class_coordinates(mrb);
	setup_ruby_collider(mrb);

	MRB_LOAD_SCRIPT(mrb, GlobalContainer);

	setup_ruby_events(mrb);
	setup_ruby_class_event(mrb);

	setup_ruby_class_texture(mrb);
	setup_ruby_class_core_entity(mrb);

	MRB_LOAD_SCRIPT(mrb, Entity);

	setup_ruby_class_window(mrb);
	setup_ruby_imgui(mrb);

	MRB_LOAD_SCRIPT(mrb, Scene);

	//! Load main scripts
	//! If you want to add something, put it here
	//! These are ordered, so don't just put it anywhere if it depends on other scripts
	//! If you want to add compiled Ruby scripts, you also need to include them in the header file

	MRB_LOAD_SCRIPT(mrb, Entities);
	MRB_LOAD_SCRIPT(mrb, Scenes);

	MRB_LOAD_SCRIPT(mrb, MainLoop);

	//! Load potential mods

	MrbWrap::load_mods(mrb);

	//! Start main script with the game loop

	MRB_LOAD_SCRIPT(mrb, Main);

	//! Clean up the Ruby interpreter

	mrb_close(mrb);

}
