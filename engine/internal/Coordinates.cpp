#include "Coordinates.h"

void setup_ruby_class_coordinates(mrb_state* mrb, RClass* ruby_module) {

	// @@@ MRBWRAPDOC_CLASS Coordinates
	// 2D coordinate vector class for positions
	MrbWrap::wrap_class_under<sf::Vector2f>(mrb, "Coordinates", ruby_module);

	auto ruby_coordinates_class = MrbWrap::get_class_info_ptr<sf::Vector2f>();

	// @@@ MRBWRAPDOC_IM Coordinates initialize x=0.0 y=0.0
	// @return [Coordinates]
	// @param x [Float]
	// @param y [Float]
	// Creates a coordinate object with the given coordinates
	MrbWrap::wrap_constructor<sf::Vector2f, MRBW_RAT_OPT<float>, MRBW_RAT_OPT<float>>(mrb);
	MrbWrap::define_default_copy_init<sf::Vector2f>(mrb);

	//! TODO: Setters doe not work reliably yet, find out, why

	// @@@ MRBWRAPDOC_ATTR Coordinates x Float rw
	// Horizontal component of the vector
	MrbWrap::wrap_getter<sf::Vector2f, &sf::Vector2f::x>(mrb, "x");
	MrbWrap::wrap_setter<sf::Vector2f, &sf::Vector2f::x, float>(mrb, "x=");

	// @@@ MRBWRAPDOC_ATTR Coordinates y Float rw
	// Vertical component of the vector
	MrbWrap::wrap_getter<sf::Vector2f, &sf::Vector2f::y>(mrb, "y");
	MrbWrap::wrap_setter<sf::Vector2f, &sf::Vector2f::y, float>(mrb, "y=");

	// @@@ MRBWRAPDOC_IM Coordinates + other
	// @return [Coordinates]
	// @param other [Coordinates]
	// Adds the two vectors to a new vector
	MrbWrap::define_member_function(mrb, ruby_coordinates_class, "+", MRUBY_FUNC {

		auto args = MrbWrap::get_raw_args<sf::Vector2f>(mrb);
		auto other_value = std::get<0>(args);

		auto this_vector = MrbWrap::convert_from_object<sf::Vector2f>(mrb, self);
		auto other_vector = MrbWrap::convert_from_object<sf::Vector2f>(mrb, other_value);

		auto ruby_coordinates_class = MrbWrap::get_class_info_ptr<sf::Vector2f>();

		auto new_value = mrb_obj_new(mrb, ruby_coordinates_class, 0, NULL);
		auto new_vector = MrbWrap::convert_from_object<sf::Vector2f>(mrb, new_value);

		//! The SFML vector has overloaded operators, so we can just do this the easy way
		//! Technically, the whole methods just creates an empty Coordinates object and then directly modifies its contents
		*new_vector = *this_vector + *other_vector;

		return new_value;

	}, MRB_ARGS_REQ(1));

	// @@@ MRBWRAPDOC_IM Coordinates - other
	// @return [Coordinates]
	// @param other [Coordinates]
	// Subtracts the two vectors to a new vector
	MrbWrap::define_member_function(mrb, ruby_coordinates_class, "-", MRUBY_FUNC {

		auto args = MrbWrap::get_raw_args<sf::Vector2f>(mrb);
		auto other_value = std::get<0>(args);

		auto this_vector = MrbWrap::convert_from_object<sf::Vector2f>(mrb, self);
		auto other_vector = MrbWrap::convert_from_object<sf::Vector2f>(mrb, other_value);

		auto ruby_coordinates_class = MrbWrap::get_class_info_ptr<sf::Vector2f>();

		auto new_value = mrb_obj_new(mrb, ruby_coordinates_class, 0, NULL);
		auto new_vector = MrbWrap::convert_from_object<sf::Vector2f>(mrb, new_value);

		*new_vector = *this_vector - *other_vector;

		return new_value;

	}, MRB_ARGS_REQ(1));

	// @@@ MRBWRAPDOC_IM Coordinates * scalar
	// @return [Coordinates]
	// @param scalar [Float]
	// Returns the vector multiplied by the scalar value
	MrbWrap::define_member_function(mrb, ruby_coordinates_class, "*", MRUBY_FUNC {

		auto args = MrbWrap::get_raw_args<float>(mrb);
		auto scalar = std::get<0>(args);

		auto this_vector = MrbWrap::convert_from_object<sf::Vector2f>(mrb, self);

		auto ruby_coordinates_class = MrbWrap::get_class_info_ptr<sf::Vector2f>();

		auto new_value = mrb_obj_new(mrb, ruby_coordinates_class, 0, NULL);
		auto new_vector = MrbWrap::convert_from_object<sf::Vector2f>(mrb, new_value);

		*new_vector = *this_vector * scalar;

		return new_value;

	}, MRB_ARGS_REQ(1));

	// @@@ MRBWRAPDOC_IM Coordinates dot other
	// @return [Float]
	// @param other [Coordinates]
	// Returns the scalar product of the two vectors
	MrbWrap::define_member_function(mrb, ruby_coordinates_class, "dot", MRUBY_FUNC {

		auto args = MrbWrap::get_converted_args<sf::Vector2f>(mrb);
		auto other_vector = std::get<0>(args);

		auto this_vector = MrbWrap::convert_from_object<sf::Vector2f>(mrb, self);

		return mrb_float_value(mrb, this_vector->x * other_vector.x + this_vector->y * other_vector.y);

	}, MRB_ARGS_REQ(1));

	// @@@ MRBWRAPDOC_IM Coordinates squared_norm
	// @return [Float]
	// Returns the squared norm of the vector
	MrbWrap::define_member_function(mrb, ruby_coordinates_class, "squared_norm", MRUBY_FUNC {

		auto content = MrbWrap::convert_from_object<sf::Vector2f>(mrb, self);

		return mrb_float_value(mrb, content->x * content->x + content->y * content->y);

	}, MRB_ARGS_NONE());

	// @@@ MRBWRAPDOC_IM Coordinates to_s
	// @return [String]
	// Puts the coordinates in a string
	MrbWrap::define_member_function(mrb, ruby_coordinates_class, "to_s", MRUBY_FUNC {

		auto content = MrbWrap::convert_from_object<sf::Vector2f>(mrb, self);

		char buffer[32];
		snprintf(buffer, 32, "%.8g %.8g", content->x, content->y);

		return mrb_str_new_cstr(mrb, buffer);

	}, MRB_ARGS_NONE());

	// @@@ MRBWRAPDOC_IM Coordinates inspect
	// @return [String]
	// Returns the vector in a easily readable string format
	MrbWrap::define_member_function(mrb, ruby_coordinates_class, "inspect", MRUBY_FUNC {

		auto content = MrbWrap::convert_from_object<sf::Vector2f>(mrb, self);

		char buffer[36];
		snprintf(buffer, 36, "(%.8g | %.8g)", content->x, content->y);

		return mrb_str_new_cstr(mrb, buffer);

	}, MRB_ARGS_NONE());

}