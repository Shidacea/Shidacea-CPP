#include "Color.h"

void setup_ruby_class_color(mrb_state* mrb, RClass* ruby_module) {

	// @@@ M_CLASS Color
	// RGBA color class
	MrbWrap::wrap_class_under<sf::Color>(mrb, "Color", ruby_module);
	auto ruby_class_color = MrbWrap::get_class_info_ptr<sf::Color>();

	// @@@ M_IM Color initialize r=0 g=0 b=0 a=255
	// @return [Color]
	// @param r [Integer]
	// @param g [Integer]
	// @param b [Integer]
	// @param a [Integer]
	// Creates a color with RGBA values ranging from 0 to 255
	MrbWrap::wrap_constructor<sf::Color, MRBW_OPT<sf::Uint8, 0>, MRBW_OPT<sf::Uint8, 0>, MRBW_OPT<sf::Uint8, 0>, MRBW_OPT<sf::Uint8, 255>>(mrb);

	// @@@ M_IM Color to_i
	// @return [Integer]
	// Converts the color RGBA value to a 32 bit integer value
	MrbWrap::wrap_member_function<sf::Color, &sf::Color::toInteger>(mrb, "to_i");

	// @@@ M_ATTR Color r Integer rw
	// The red value of the color, ranging from 0 to 255
	MrbWrap::wrap_getter<sf::Color, &sf::Color::r>(mrb, "r");
	MrbWrap::wrap_setter<sf::Color, &sf::Color::r, sf::Uint8>(mrb, "r=");

	// @@@ M_ATTR Color g Integer rw
	// The green value of the color, ranging from 0 to 255
	MrbWrap::wrap_getter<sf::Color, &sf::Color::g>(mrb, "g");
	MrbWrap::wrap_setter<sf::Color, &sf::Color::g, sf::Uint8>(mrb, "g=");

	// @@@ M_ATTR Color b Integer rw
	// The blue value of the color, ranging from 0 to 255
	MrbWrap::wrap_getter<sf::Color, &sf::Color::b>(mrb, "b");
	MrbWrap::wrap_setter<sf::Color, &sf::Color::b, sf::Uint8>(mrb, "b=");

	// @@@ M_ATTR Color a Integer rw
	// The alpha value of the color, ranging from 0 to 255
	MrbWrap::wrap_getter<sf::Color, &sf::Color::a>(mrb, "a");
	MrbWrap::wrap_setter<sf::Color, &sf::Color::a, sf::Uint8>(mrb, "a=");

	//! TODO: Simplfy friend methods

	// @@@ M_IM Color + other
	// @return [Color]
	// @param other [Color]
	// Adds the two color values by components to a new value
	MrbWrap::define_member_function(mrb, ruby_class_color, "+", MRUBY_FUNC {
	
		auto args = MrbWrap::get_raw_args<sf::Color>(mrb);
		auto other_value = std::get<0>(args);

		auto this_color = MrbWrap::convert_from_object<sf::Color>(mrb, self);
		auto other_color = MrbWrap::convert_from_object<sf::Color>(mrb, other_value);

		auto ruby_class_color = MrbWrap::get_class_info_ptr<sf::Color>();

		auto new_value = mrb_obj_new(mrb, ruby_class_color, 0, NULL);
		auto new_color = MrbWrap::convert_from_object<sf::Color>(mrb, new_value);

		*new_color = *this_color + *other_color;

		return new_value;

	}, MRB_ARGS_REQ(1));

	// @@@ M_IM Color - other
	// @return [Color]
	// @param other [Color]
	// Subtracts the two color values by components to a new value
	MrbWrap::define_member_function(mrb, ruby_class_color, "-", MRUBY_FUNC {
	
		auto args = MrbWrap::get_raw_args<sf::Color>(mrb);
		auto other_value = std::get<0>(args);

		auto this_color = MrbWrap::convert_from_object<sf::Color>(mrb, self);
		auto other_color = MrbWrap::convert_from_object<sf::Color>(mrb, other_value);

		auto ruby_class_color = MrbWrap::get_class_info_ptr<sf::Color>();

		auto new_value = mrb_obj_new(mrb, ruby_class_color, 0, NULL);
		auto new_color = MrbWrap::convert_from_object<sf::Color>(mrb, new_value);

		*new_color = *this_color - *other_color;

		return new_value;

	}, MRB_ARGS_REQ(1));

	// @@@ M_IM Color * other
	// @return [Color]
	// @param other [Color]
	// Multiplies the two color values by components to a new value
	MrbWrap::define_member_function(mrb, ruby_class_color, "*", MRUBY_FUNC {
	
		auto args = MrbWrap::get_raw_args<sf::Color>(mrb);
		auto other_value = std::get<0>(args);

		auto this_color = MrbWrap::convert_from_object<sf::Color>(mrb, self);
		auto other_color = MrbWrap::convert_from_object<sf::Color>(mrb, other_value);

		auto ruby_class_color = MrbWrap::get_class_info_ptr<sf::Color>();

		auto new_value = mrb_obj_new(mrb, ruby_class_color, 0, NULL);
		auto new_color = MrbWrap::convert_from_object<sf::Color>(mrb, new_value);

		*new_color = *this_color * *other_color;

		return new_value;

	}, MRB_ARGS_REQ(1));

	// @@@ M_IM Color to_s
	// @return [String]
	// Converts the color RGBA value to a space-separated string
	MrbWrap::define_member_function(mrb, ruby_class_color, "to_s", MRUBY_FUNC {

		auto content = MrbWrap::convert_from_object<sf::Color>(mrb, self);

		char buffer[16];
		snprintf(buffer, 16, "%u %u %u %u", content->r, content->g, content->b, content->a);

		return mrb_str_new_cstr(mrb, buffer);

	}, MRB_ARGS_NONE());

	// @@@ M_IM Color inspect
	// @return [String]
	// Creates a string with verbose RGBA information
	MrbWrap::define_member_function(mrb, ruby_class_color, "inspect", MRUBY_FUNC {

		auto content = MrbWrap::convert_from_object<sf::Color>(mrb, self);

		char buffer[48];
		snprintf(buffer, 48, "(R = %u, G = %u, B = %u, A = %u)", content->r, content->g, content->b, content->a);

		return mrb_str_new_cstr(mrb, buffer);

	}, MRB_ARGS_NONE());

	//! TODO: Equality checks

}