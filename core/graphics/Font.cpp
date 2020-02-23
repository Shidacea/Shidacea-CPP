#include "Font.h"

void setup_ruby_class_font(mrb_state* mrb, RClass* ruby_module) {

	MrbWrap::wrap_class_under<sf::Font>(mrb, "Font", ruby_module);
	
	MrbWrap::wrap_constructor<sf::Font>(mrb);

	MrbWrap::wrap_member_function<sf::Font, &sf::Font::loadFromFile, std::string>(mrb, "load_from_file");

}