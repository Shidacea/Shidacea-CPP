#include "Color.h"

void setup_ruby_class_color(mrb_state* mrb, RClass* ruby_module) {

	MrbWrap::wrap_class_under<sf::Color>(mrb, "Color", ruby_module);
	auto ruby_class_color = MrbWrap::get_class_info_ptr<sf::Color>();

	MrbWrap::wrap_constructor<sf::Color, MRBW_OPT<uint8_t, 0>, MRBW_OPT<uint8_t, 0>, MRBW_OPT<uint8_t, 0>, MRBW_OPT<uint8_t, 255>>(mrb);

	MrbWrap::wrap_member_function<sf::Color, &sf::Color::toInteger>(mrb, "to_i");

	MrbWrap::wrap_getter<sf::Color, &sf::Color::r>(mrb, "r");
	MrbWrap::wrap_getter<sf::Color, &sf::Color::r>(mrb, "g");
	MrbWrap::wrap_getter<sf::Color, &sf::Color::r>(mrb, "b");
	MrbWrap::wrap_getter<sf::Color, &sf::Color::r>(mrb, "a");

	MrbWrap::wrap_setter<sf::Color, &sf::Color::r, uint8_t>(mrb, "r=");
	MrbWrap::wrap_setter<sf::Color, &sf::Color::r, uint8_t>(mrb, "g=");
	MrbWrap::wrap_setter<sf::Color, &sf::Color::r, uint8_t>(mrb, "b=");
	MrbWrap::wrap_setter<sf::Color, &sf::Color::r, uint8_t>(mrb, "a=");

	MrbWrap::define_mruby_function(mrb, ruby_class_color, "+", MRUBY_FUNC {
	
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

	MrbWrap::define_mruby_function(mrb, ruby_class_color, "-", MRUBY_FUNC {
	
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

	MrbWrap::define_mruby_function(mrb, ruby_class_color, "*", MRUBY_FUNC {
	
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

	MrbWrap::define_mruby_function(mrb, ruby_class_color, "to_s", MRUBY_FUNC {

		auto content = MrbWrap::convert_from_object<sf::Color>(mrb, self);

		char buffer[16];
		snprintf(buffer, 16, "%u %u %u %u", content->r, content->g, content->b, content->a);

		return mrb_str_new_cstr(mrb, buffer);

	}, MRB_ARGS_NONE());

	MrbWrap::define_mruby_function(mrb, ruby_class_color, "inspect", MRUBY_FUNC {

		auto content = MrbWrap::convert_from_object<sf::Color>(mrb, self);

		char buffer[48];
		snprintf(buffer, 48, "(R = %u, G = %u, B = %u, A = %u)", content->r, content->g, content->b, content->a);

		return mrb_str_new_cstr(mrb, buffer);

	}, MRB_ARGS_NONE());

	//! TODO: Equality checks

}