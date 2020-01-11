#include "Text.h"

mrb_value ruby_text_init(mrb_state* mrb, mrb_value self) {

	char* text_string;
	mrb_value ruby_font;
	mrb_int character_size = 30;

	mrb_get_args(mrb, "zo|i", &text_string, &ruby_font, &character_size);

	auto font = MrbWrap::convert_from_object<sf::Font>(mrb, ruby_font);

	MrbWrap::convert_to_instance_variable<sf::Font>(mrb, self, "@_font");
	auto font_cache = MrbWrap::convert_from_instance_variable<sf::Font>(mrb, self, "@_font");
	*font_cache = *font;

	MrbWrap::convert_to_object<sf::Text>(mrb, self, sf::String(text_string), *font, static_cast<unsigned int>(character_size));

	return self;

}

void setup_ruby_class_text(mrb_state* mrb, RClass* ruby_module) {

	auto ruby_text_class = MrbWrap::define_data_class_under(mrb, "Text", ruby_module);

	mrb_define_method(mrb, ruby_text_class, "initialize", ruby_text_init, MRB_ARGS_ARG(2, 1));

}