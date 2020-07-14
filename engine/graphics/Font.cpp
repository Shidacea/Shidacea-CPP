#include "Font.h"

void setup_ruby_class_font(mrb_state* mrb, RClass* ruby_module) {

	// @@@ M_CLASS Font
	// Class for text fonts
	MrbWrap::wrap_class_under<sf::Font>(mrb, "Font", ruby_module);
	
	// @@@ M_IM Font initialize
	// @return [Font]
	// Creates an empty font
	MrbWrap::wrap_constructor<sf::Font>(mrb);

	// @@@ M_IM Font load_from_file filename
	// @return [Boolean]
	// @param filename [String]
	// Loads the font from file, returning true if loading was successful, else false.
	MrbWrap::wrap_member_function<sf::Font, &sf::Font::loadFromFile, MRBW_FILE>(mrb, "load_from_file");

}