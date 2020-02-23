#include "Coordinates.h"

void setup_ruby_class_coordinates(mrb_state* mrb, RClass* ruby_module) {

	coordinates_ruby_module = ruby_module;

	MrbWrap::wrap_class_under<sf::Vector2f>(mrb, "Coordinates", ruby_module);

	auto ruby_coordinates_class = MrbWrap::define_data_class_under(mrb, "Coordinates", ruby_module);

	MrbWrap::wrap_constructor<sf::Vector2f, MRBW_RAT_OPT<float>, MRBW_RAT_OPT<float>>(mrb);
	MrbWrap::define_default_copy_init<sf::Vector2f>(mrb);

	MrbWrap::wrap_getter<MRBW_FUNC(sf::Vector2f, sf::Vector2f::x)>(mrb, "x");
	MrbWrap::wrap_getter<MRBW_FUNC(sf::Vector2f, sf::Vector2f::y)>(mrb, "y");

	MrbWrap::wrap_setter<MRBW_FUNC(sf::Vector2f, sf::Vector2f::x), float>(mrb, "x=");
	MrbWrap::wrap_setter<MRBW_FUNC(sf::Vector2f, sf::Vector2f::y), float>(mrb, "y=");

	MrbWrap::define_mruby_function(mrb, ruby_coordinates_class, "+", MRUBY_FUNC {

		auto args = MrbWrap::get_raw_args<sf::Vector2f>(mrb);
		auto other_value = std::get<0>(args);

		auto this_vector = MrbWrap::convert_from_object<sf::Vector2f>(mrb, self);
		auto other_vector = MrbWrap::convert_from_object<sf::Vector2f>(mrb, other_value);

		static auto coordinates_class = mrb_class_get_under(mrb, coordinates_ruby_module, "Coordinates");

		auto new_value = mrb_obj_new(mrb, coordinates_class, 0, NULL);
		auto new_vector = MrbWrap::convert_from_object<sf::Vector2f>(mrb, new_value);

		//! The SFML vector has overloaded operators, so we can just do this the easy way
		//! Technically, the whole methods just creates an empty Coordinates object and then directly modifies its contents
		*new_vector = *this_vector + *other_vector;

		return new_value;

	});

	MrbWrap::define_mruby_function(mrb, ruby_coordinates_class, "-", MRUBY_FUNC {

		auto args = MrbWrap::get_raw_args<sf::Vector2f>(mrb);
		auto other_value = std::get<0>(args);

		auto this_vector = MrbWrap::convert_from_object<sf::Vector2f>(mrb, self);
		auto other_vector = MrbWrap::convert_from_object<sf::Vector2f>(mrb, other_value);

		static auto coordinates_class = mrb_class_get_under(mrb, coordinates_ruby_module, "Coordinates");

		auto new_value = mrb_obj_new(mrb, coordinates_class, 0, NULL);
		auto new_vector = MrbWrap::convert_from_object<sf::Vector2f>(mrb, new_value);

		*new_vector = *this_vector - *other_vector;

		return new_value;

	});

	MrbWrap::define_mruby_function(mrb, ruby_coordinates_class, "*", MRUBY_FUNC {

		auto args = MrbWrap::get_raw_args<float>(mrb);
		auto scalar = std::get<0>(args);

		auto this_vector = MrbWrap::convert_from_object<sf::Vector2f>(mrb, self);

		static auto coordinates_class = mrb_class_get_under(mrb, coordinates_ruby_module, "Coordinates");

		auto new_value = mrb_obj_new(mrb, coordinates_class, 0, NULL);
		auto new_vector = MrbWrap::convert_from_object<sf::Vector2f>(mrb, new_value);

		*new_vector = *this_vector * scalar;

		return new_value;

	});

	MrbWrap::define_mruby_function(mrb, ruby_coordinates_class, "dot", MRUBY_FUNC {

		auto args = MrbWrap::get_converted_args<sf::Vector2f>(mrb);
		auto other_vector = std::get<0>(args);

		auto this_vector = MrbWrap::convert_from_object<sf::Vector2f>(mrb, self);

		return mrb_float_value(mrb, this_vector->x * other_vector.x + this_vector->y * other_vector.y);

	});

	MrbWrap::define_mruby_function(mrb, ruby_coordinates_class, "squared_norm", MRUBY_FUNC {

		auto content = MrbWrap::convert_from_object<sf::Vector2f>(mrb, self);

		return mrb_float_value(mrb, content->x * content->x + content->y * content->y);

	});

	MrbWrap::define_mruby_function(mrb, ruby_coordinates_class, "to_s", MRUBY_FUNC {

		auto content = MrbWrap::convert_from_object<sf::Vector2f>(mrb, self);

		char buffer[32];
		snprintf(buffer, 32, "%.8g %.8g", content->x, content->y);

		return mrb_str_new_cstr(mrb, buffer);

	});

	MrbWrap::define_mruby_function(mrb, ruby_coordinates_class, "inspect", MRUBY_FUNC {

		auto content = MrbWrap::convert_from_object<sf::Vector2f>(mrb, self);

		char buffer[36];
		snprintf(buffer, 36, "(%.8g | %.8g)", content->x, content->y);

		return mrb_str_new_cstr(mrb, buffer);

	});

}