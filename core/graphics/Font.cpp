#include "Font.h"

void setup_ruby_class_font(mrb_state* mrb, RClass* ruby_module) {

	auto ruby_font_class = MrbWrap::define_data_class_under(mrb, "Font", ruby_module);

	MrbWrap::wrap_constructor<sf::Font>(mrb, ruby_font_class);

	MrbWrap::wrap_function<MRBW_FUNC(sf::Font, sf::Font::loadFromFile), std::string>(mrb, ruby_font_class, "load_from_file");

}