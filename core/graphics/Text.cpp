#include "Text.h"

void setup_ruby_class_text(mrb_state* mrb, RClass* ruby_module) {

	MrbWrap::wrap_class_under<sf::Text>(mrb, "Text", ruby_module);

	auto ruby_text_class = MrbWrap::define_data_class_under(mrb, "Text", ruby_module);

	MrbWrap::define_mruby_function(mrb, ruby_text_class, "initialize", MRUBY_FUNC{

		auto args = MrbWrap::get_converted_args<std::string, sf::Font, MRBW_OPT<unsigned int, 30>>(mrb);
		auto text_string = std::get<0>(args);
		auto font = std::get<1>(args);
		auto character_size = std::get<2>(args);

		MrbWrap::convert_to_instance_variable<sf::Font>(mrb, self, "@_font");
		auto font_cache = MrbWrap::convert_from_instance_variable<sf::Font>(mrb, self, "@_font");
		*font_cache = font;

		MrbWrap::convert_to_object<sf::Text>(mrb, self, sf::String(text_string), font, static_cast<unsigned int>(character_size));

		return self;

		}, MRB_ARGS_ARG(2, 1));

	MrbWrap::wrap_getter<sf::Text, &sf::Text::getCharacterSize>(mrb, "character_size");
	MrbWrap::wrap_setter<sf::Text, &sf::Text::setCharacterSize, unsigned int>(mrb, "character_size=");

}