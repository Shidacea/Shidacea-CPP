#include "Text.h"

void setup_ruby_class_text(mrb_state* mrb, RClass* ruby_module) {

	MrbWrap::wrap_class_under<sf::Text>(mrb, "Text", ruby_module);

	MrbWrap::define_member_function(mrb, MrbWrap::get_class_info_ptr<sf::Text>(), "initialize", MRUBY_FUNC {

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

		return mrb_str_new_cstr(mrb, text->getString().toAnsiString().c_str());

	}, MRB_ARGS_NONE());

	MrbWrap::define_member_function(mrb, MrbWrap::get_class_info_ptr<sf::Text>(), "string=", MRUBY_FUNC {

		auto args = MrbWrap::get_raw_args<sf::String>(mrb);
		auto str = std::get<0>(args);

		auto text = MrbWrap::convert_from_object<sf::Text>(mrb, self);
		text->setString(sf::String(str));

		return mrb_str_new_cstr(mrb, str);

	}, MRB_ARGS_REQ(1));

}