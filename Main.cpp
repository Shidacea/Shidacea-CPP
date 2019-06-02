#include "Main.h"

int main() {

	auto mrb = mrb_open();

	//! Load wrapped classes and Ruby scripts
	
	setup_ruby_class_resource_manager(mrb);

	setup_ruby_class_coordinates(mrb);

	MRB_LOAD_SCRIPT(mrb, GlobalContainer);

	setup_ruby_class_texture(mrb);
	setup_ruby_class_core_entity(mrb);

	MRB_LOAD_SCRIPT(mrb, Entity);

	setup_ruby_class_window(mrb);

	MRB_LOAD_SCRIPT(mrb, Scene);

	//! Load main scripts

	MRB_LOAD_SCRIPT(mrb, Entities);
	MRB_LOAD_SCRIPT(mrb, Scenes);

	MRB_LOAD_SCRIPT(mrb, MainLoop);

	//! Load potential mods

	MrbWrap::load_mods(mrb);

	//! Start main script with the game loop

	MRB_LOAD_SCRIPT(mrb, Main);

	mrb_close(mrb);

}
