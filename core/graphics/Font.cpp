#include "Font.h"

mrb_value ruby_font_init(mrb_state* mrb, mrb_value self) {

	auto font = MrbWrap::convert_to_object<sf::Font>(mrb, self);
	font->loadFromFile("assets/fonts/arial.ttf");	//! TODO: Remove this

	return self;

}

void setup_ruby_class_font(mrb_state* mrb, RClass* ruby_module) {

	auto ruby_font_class = MrbWrap::define_data_class_under(mrb, "Font", ruby_module);

	mrb_define_method(mrb, ruby_font_class, "initialize", ruby_font_init, MRB_ARGS_NONE());

}