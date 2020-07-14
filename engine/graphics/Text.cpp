#include "Text.h"

void setup_ruby_class_text(mrb_state* mrb, RClass* ruby_module) {

	// @@@ MRBWRAPDOC_CLASS Text
	// Drawable text class
	MrbWrap::wrap_class_under<sf::Text>(mrb, "Text", ruby_module);

	// @@@ MRBWRAPDOC_IM Text initialize content font character_size=30
	// @return [Text]
	// @param content [String]
	// @param font [Font]
	// @param character_size [Integer]
	// Creates a text object with the given content, font and character size
	MrbWrap::define_member_function(mrb, MrbWrap::get_class_info_ptr<sf::Text>(), "initialize", MRUBY_FUNC {

		auto args = MrbWrap::get_raw_args<const char*, sf::Font, MRBW_OPT<unsigned int, 30>>(mrb);
		auto text_string = std::get<0>(args);
		auto font = std::get<1>(args);
		auto character_size = static_cast<int>(std::get<2>(args));

		auto converted_font = MrbWrap::convert_from_object<sf::Font>(mrb, font);

		auto new_text = MrbWrap::convert_to_object<sf::Text>(mrb, self);

		new_text->setString(sf::String::fromUtf8(text_string, text_string + strlen(text_string)));

		new_text->setFont(*converted_font);
		new_text->setCharacterSize(static_cast<unsigned int>(character_size));

		return self;

	}, MRB_ARGS_ARG(2, 1));

	// @@@ MRBWRAPDOC_ATTR Text character_size Integer rw
	// Character size of the text in pixels
	MrbWrap::wrap_getter<sf::Text, &sf::Text::getCharacterSize>(mrb, "character_size");
	MrbWrap::wrap_setter<sf::Text, &sf::Text::setCharacterSize, unsigned int>(mrb, "character_size=");

	// @@@ MRBWRAPDOC_ATTR Text fill_color Color rw
	// Fill color of the text
	MrbWrap::wrap_getter<sf::Text, &sf::Text::getFillColor>(mrb, "fill_color");
	MrbWrap::wrap_setter<sf::Text, &sf::Text::setFillColor, sf::Color>(mrb, "fill_color=");

	// @@@ MRBWRAPDOC_ATTR Text outline_color Color rw
	// Outline color of the text
	MrbWrap::wrap_getter<sf::Text, &sf::Text::getOutlineColor>(mrb, "outline_color");
	MrbWrap::wrap_setter<sf::Text, &sf::Text::setOutlineColor, sf::Color>(mrb, "outline_color=");

	//! TODO: Simplify these, if possible
	//! The problem is that sf::String is a separate class which would count as a new Ruby object
	//! However, the Ruby string class is perfectly sufficient for these tasks
	//! Replacing it with an SFML class would be overkill

	// @@@ MRBWRAPDOC_ATTR Text string String rw
	// Content of the text
	MrbWrap::define_member_function(mrb, MrbWrap::get_class_info_ptr<sf::Text>(), "string", MRUBY_FUNC {

		auto text = MrbWrap::convert_from_object<sf::Text>(mrb, self);
		auto str = text->getString().toUtf8();

		return mrb_str_new_cstr(mrb, reinterpret_cast<const char*>(str.c_str()));

	}, MRB_ARGS_NONE());

	MrbWrap::define_member_function(mrb, MrbWrap::get_class_info_ptr<sf::Text>(), "string=", MRUBY_FUNC {

		auto args = MrbWrap::get_converted_args<const char*>(mrb);
		auto str = std::get<0>(args);

		auto text = MrbWrap::convert_from_object<sf::Text>(mrb, self);
		text->setString(sf::String::fromUtf8(str, str + strlen(str)));

		return mrb_str_new_cstr(mrb, str);

	}, MRB_ARGS_REQ(1));

}