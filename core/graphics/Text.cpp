#include "Text.h"

sf::String convert_byte_to_utf8(const char* str) {

	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
	auto wide_str = converter.from_bytes(str);

	return sf::String(wide_str);

}

std::string convert_utf8_to_byte(std::wstring str) {

	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
	auto byte_str = converter.to_bytes(str);

	return byte_str;

}

//! Since the text class refers to a font pointer, another reference to it needs to be stored in an IV
void link_font(mrb_state* mrb, mrb_value self, sf::Font* font) {

	MrbWrap::convert_to_instance_variable<sf::Font>(mrb, self, "@_font");
	auto font_cache = MrbWrap::convert_from_instance_variable<sf::Font>(mrb, self, "@_font");
	*font_cache = *font;

}

void setup_ruby_class_text(mrb_state* mrb, RClass* ruby_module) {

	MrbWrap::wrap_class_under<sf::Text>(mrb, "Text", ruby_module);

	MrbWrap::define_member_function(mrb, MrbWrap::get_class_info_ptr<sf::Text>(), "initialize", MRUBY_FUNC {

		auto args = MrbWrap::get_raw_args<std::string, sf::Font, MRBW_OPT<unsigned int, 30>>(mrb);
		auto text_string = std::get<0>(args);
		auto font = std::get<1>(args);
		auto character_size = static_cast<int>(std::get<2>(args));

		auto converted_font = MrbWrap::convert_from_object<sf::Font>(mrb, font);

		link_font(mrb, self, converted_font);

		MrbWrap::convert_to_object<sf::Text>(mrb, self, sf::String(convert_byte_to_utf8(text_string)), *converted_font, static_cast<unsigned int>(character_size));

		return self;

	}, MRB_ARGS_ARG(2, 1));

	MrbWrap::wrap_getter<sf::Text, &sf::Text::getCharacterSize>(mrb, "character_size");
	MrbWrap::wrap_setter<sf::Text, &sf::Text::setCharacterSize, unsigned int>(mrb, "character_size=");

	MrbWrap::wrap_getter<sf::Text, &sf::Text::getFillColor>(mrb, "fill_color");
	MrbWrap::wrap_setter<sf::Text, &sf::Text::setFillColor, sf::Color>(mrb, "fill_color=");

	MrbWrap::wrap_getter<sf::Text, &sf::Text::getOutlineColor>(mrb, "outline_color");
	MrbWrap::wrap_setter<sf::Text, &sf::Text::setOutlineColor, sf::Color>(mrb, "outline_color=");

	//! TODO: Simplify these, if possible
	//! The problem is that sf::String is a separate class which would count as a new Ruby object
	//! However, the Ruby string class is perfectly sufficient for these tasks
	//! Replacing it with an SFML class would be overkill

	MrbWrap::define_member_function(mrb, MrbWrap::get_class_info_ptr<sf::Text>(), "string", MRUBY_FUNC {

		auto text = MrbWrap::convert_from_object<sf::Text>(mrb, self);

		auto str = convert_utf8_to_byte(text->getString().toWideString()).c_str();

		return mrb_str_new_cstr(mrb, str);

	}, MRB_ARGS_NONE());

	MrbWrap::define_member_function(mrb, MrbWrap::get_class_info_ptr<sf::Text>(), "string=", MRUBY_FUNC {

		auto args = MrbWrap::get_raw_args<sf::String>(mrb);
		auto str = std::get<0>(args);

		//! NOTE: This is an unrecommended way, which converts the string to ANSI and then loads it to SFML
		//auto sfml_str = sf::String(mrb_locale_from_utf8(str, strlen(str)));

		//! The recommended way is by converting it to wide chars and then loading it
		//! However, this way is marked as deprecated since C++17, so it might need replacement at some time

		auto text = MrbWrap::convert_from_object<sf::Text>(mrb, self);
		text->setString(convert_byte_to_utf8(str));

		return mrb_str_new_cstr(mrb, str);

	}, MRB_ARGS_REQ(1));

}