#include "Coordinates.h"

mrb_value ruby_coordinates_init(mrb_state* mrb, mrb_value self) {

	mrb_float x = 0.0;
	mrb_float y = 0.0;

	//! Default arguments yield a zero vector
	mrb_get_args(mrb, "|ff", &x, &y);

	MrbWrap::convert_to_object<sf::Vector2f>(mrb, self, x, y);

	return self;

}

mrb_value ruby_coordinates_x(mrb_state* mrb, mrb_value self) {

	auto content = MrbWrap::convert_from_object<sf::Vector2f>(mrb, self);
	
	return mrb_float_value(mrb, content->x);

}

mrb_value ruby_coordinates_y(mrb_state* mrb, mrb_value self) {

	auto content = MrbWrap::convert_from_object<sf::Vector2f>(mrb, self);

	return mrb_float_value(mrb, content->y);

}

mrb_value ruby_coordinates_x_equals(mrb_state* mrb, mrb_value self) {

	mrb_float new_value;

	mrb_get_args(mrb, "f", &new_value);

	auto content = MrbWrap::convert_from_object<sf::Vector2f>(mrb, self);
	content->x = new_value;

	return mrb_float_value(mrb, new_value);

}

mrb_value ruby_coordinates_y_equals(mrb_state* mrb, mrb_value self) {

	mrb_float new_value;

	mrb_get_args(mrb, "f", &new_value);

	auto content = MrbWrap::convert_from_object<sf::Vector2f>(mrb, self);
	content->y = new_value;

	return mrb_float_value(mrb, new_value);

}

mrb_value ruby_coordinates_plus(mrb_state* mrb, mrb_value self) {

	mrb_value other_value;

	mrb_get_args(mrb, "o", &other_value);

	auto this_vector = MrbWrap::convert_from_object<sf::Vector2f>(mrb, self);
	auto other_vector = MrbWrap::convert_from_object<sf::Vector2f>(mrb, other_value);

	static auto coordinates_class = mrb_class_get_under(mrb, coordinates_ruby_module, "Coordinates");

	auto new_value = mrb_obj_new(mrb, coordinates_class, 0, NULL);
	auto new_vector = MrbWrap::convert_from_object<sf::Vector2f>(mrb, new_value);

	//! The SFML vector has overloaded operators, so we can just do this the easy way
	//! Technically, the whole methods just creates an empty Coordinates object and then directly modifies its contents
	*new_vector = *this_vector + *other_vector;

	return new_value;

}

mrb_value ruby_coordinates_minus(mrb_state* mrb, mrb_value self) {

	mrb_value other_value;

	mrb_get_args(mrb, "o", &other_value);

	auto this_vector = MrbWrap::convert_from_object<sf::Vector2f>(mrb, self);
	auto other_vector = MrbWrap::convert_from_object<sf::Vector2f>(mrb, other_value);

	static auto coordinates_class = mrb_class_get_under(mrb, coordinates_ruby_module, "Coordinates");

	auto new_value = mrb_obj_new(mrb, coordinates_class, 0, NULL);
	auto new_vector = MrbWrap::convert_from_object<sf::Vector2f>(mrb, new_value);

	*new_vector = *this_vector - *other_vector;

	return new_value;

}

mrb_value ruby_coordinates_times(mrb_state* mrb, mrb_value self) {

	mrb_float scalar;

	mrb_get_args(mrb, "f", &scalar);

	auto this_vector = MrbWrap::convert_from_object<sf::Vector2f>(mrb, self);

	static auto coordinates_class = mrb_class_get_under(mrb, coordinates_ruby_module, "Coordinates");

	auto new_value = mrb_obj_new(mrb, coordinates_class, 0, NULL);
	auto new_vector = MrbWrap::convert_from_object<sf::Vector2f>(mrb, new_value);

	*new_vector = *this_vector * scalar;

	return new_value;

}

mrb_value ruby_coordinates_dot_product(mrb_state* mrb, mrb_value self) {

	mrb_value other_value;

	mrb_get_args(mrb, "o", &other_value);

	auto this_vector = MrbWrap::convert_from_object<sf::Vector2f>(mrb, self);
	auto other_vector = MrbWrap::convert_from_object<sf::Vector2f>(mrb, other_value);

	return mrb_float_value(mrb, this_vector->x * other_vector->x + this_vector->y * other_vector->y);

}

mrb_value ruby_coordinates_squared_norm(mrb_state* mrb, mrb_value self) {

	auto content = MrbWrap::convert_from_object<sf::Vector2f>(mrb, self);

	return mrb_float_value(mrb, content->x * content->x + content->y * content->y);
}

mrb_value ruby_coordinates_to_s(mrb_state* mrb, mrb_value self) {

	auto content = MrbWrap::convert_from_object<sf::Vector2f>(mrb, self);

	char buffer[32];
	snprintf(buffer, 32, "%.8g %.8g", content->x, content->y);

	return mrb_str_new_cstr(mrb, buffer);

}

mrb_value ruby_coordinates_inspect(mrb_state* mrb, mrb_value self) {

	auto content = MrbWrap::convert_from_object<sf::Vector2f>(mrb, self);

	char buffer[36];
	snprintf(buffer, 36, "(%.8g | %.8g)", content->x, content->y);

	return mrb_str_new_cstr(mrb, buffer);

}

void setup_ruby_class_coordinates(mrb_state* mrb, RClass* ruby_module) {

	coordinates_ruby_module = ruby_module;

	auto ruby_coordinates_class = MrbWrap::define_data_class_under(mrb, "Coordinates", ruby_module);

	mrb_define_method(mrb, ruby_coordinates_class, "initialize", ruby_coordinates_init, MRB_ARGS_OPT(2));
	MrbWrap::define_default_copy_init<sf::Vector2f>(mrb, ruby_coordinates_class);

	mrb_define_method(mrb, ruby_coordinates_class, "x", ruby_coordinates_x, MRB_ARGS_NONE());
	mrb_define_method(mrb, ruby_coordinates_class, "y", ruby_coordinates_y, MRB_ARGS_NONE());

	mrb_define_method(mrb, ruby_coordinates_class, "x=", ruby_coordinates_x_equals, MRB_ARGS_NONE());
	mrb_define_method(mrb, ruby_coordinates_class, "y=", ruby_coordinates_y_equals, MRB_ARGS_NONE());

	mrb_define_method(mrb, ruby_coordinates_class, "+", ruby_coordinates_plus, MRB_ARGS_REQ(1));
	mrb_define_method(mrb, ruby_coordinates_class, "-", ruby_coordinates_minus, MRB_ARGS_REQ(1));
	mrb_define_method(mrb, ruby_coordinates_class, "*", ruby_coordinates_times, MRB_ARGS_REQ(1));

	mrb_define_method(mrb, ruby_coordinates_class, "dot", ruby_coordinates_dot_product, MRB_ARGS_REQ(1));
	mrb_define_method(mrb, ruby_coordinates_class, "squared_norm", ruby_coordinates_squared_norm, MRB_ARGS_NONE());

	mrb_define_method(mrb, ruby_coordinates_class, "to_s", ruby_coordinates_to_s, MRB_ARGS_NONE());
	mrb_define_method(mrb, ruby_coordinates_class, "inspect", ruby_coordinates_inspect, MRB_ARGS_NONE());

}