#include "Shape.h"

DEFINE_COLLISION(ShapeCircle, ShapeCircle) {

	GET_POSITIONS

	auto r1 = shape1.radius;
	auto r2 = shape2.radius;

	return collision_circle_circle(x1, y1, r1, x2, y2, r2);

}

DEFINE_COLLISION(ShapeBox, ShapeBox) {

	GET_POSITIONS

	auto w1 = shape1.width;
	auto h1 = shape1.height;

	auto w2 = shape2.width;
	auto h2 = shape2.height;

	return collision_box_box(x1, y1, w1, h1, x2, y2, w2, h2);

}

DEFINE_COLLISION(ShapeCircle, ShapeBox) {

	return false;	// TODO: Implement this

}

ShapeType get_type_of_ruby_shape(mrb_state* mrb, mrb_value ruby_shape) {

	return ShapeType::Circle;

	static auto ruby_class_shape_circle = mrb_class_get(mrb, "ShapeCircle");
	static auto ruby_class_shape_box = mrb_class_get(mrb, "ShapeBox");

	if (mrb_obj_is_instance_of(mrb, ruby_shape, ruby_class_shape_circle)) return ShapeType::Circle;
	else if (mrb_obj_is_instance_of(mrb, ruby_shape, ruby_class_shape_box)) return ShapeType::Box;
	else return ShapeType::Unknown;

}

mrb_value ruby_collider_test(mrb_state* mrb, mrb_value self) {

	mrb_value ruby_shape_1;
	mrb_value ruby_shape_2;
	mrb_value ruby_pos_1;
	mrb_value ruby_pos_2;

	//! There seem to be ghoooosts

	mrb_get_args(mrb, "oooo", &ruby_shape_1, &ruby_pos_1, &ruby_shape_2, &ruby_pos_2);

	auto type_1 = get_type_of_ruby_shape(mrb, ruby_shape_1);
	auto type_2 = get_type_of_ruby_shape(mrb, ruby_shape_2);

	auto pos_1 = MrbWrap::convert_from_instance_variable<sf::Vector2f>(mrb, ruby_pos_1, "@_vector");
	auto pos_2 = MrbWrap::convert_from_instance_variable<sf::Vector2f>(mrb, ruby_pos_2, "@_vector");

	auto result = false;
	
	//! A bit hacky, but we don't want to repeat ourselves too many times
	//! Also, this makes the code MUCH more readable and extendable

	TEST_COLLISION_CASE(Circle, Circle)
	else TEST_COLLISION_CASE(Circle, Box)
	else TEST_COLLISION_CASE_REVERSE(Circle, Box)
	else TEST_COLLISION_CASE(Box, Box)

	return mrb_bool_value(result);

}

mrb_value ruby_shape_class_init(mrb_state* mrb, mrb_value self) {

	return self;

}

mrb_value ruby_shape_circle_class_init(mrb_state* mrb, mrb_value self) {

	float radius = 0.0;

	//! Default arguments yield a zero vector
	mrb_get_args(mrb, "|f", &radius);

	auto shape = MrbWrap::convert_to_instance_variable<ShapeCircle>(mrb, self, "@_shape", "shape");
	shape->radius = radius;

	return self;

}

mrb_value ruby_shape_box_class_init(mrb_state* mrb, mrb_value self) {

	float width = 0.0;
	float height = 0.0;

	mrb_get_args(mrb, "|f", &width, &height);

	auto shape = MrbWrap::convert_to_instance_variable<ShapeBox>(mrb, self, "@_shape", "shape");
	shape->width = width;
	shape->height = height;

	return self;

}

void setup_ruby_collider(mrb_state* mrb) {

	auto module_collider = mrb_define_module(mrb, "Collider");
	
	auto ruby_shape_class = mrb_define_class(mrb, "Shape", mrb->object_class);
	auto ruby_shape_circle_class = mrb_define_class(mrb, "ShapeCircle", mrb->object_class);
	auto ruby_shape_box_class = mrb_define_class(mrb, "ShapeBox", ruby_shape_class);

	mrb_define_method(mrb, ruby_shape_class, "initialize", ruby_shape_class_init, MRB_ARGS_NONE());
	mrb_define_method(mrb, ruby_shape_circle_class, "initialize", ruby_shape_circle_class_init, MRB_ARGS_OPT(1));
	mrb_define_method(mrb, ruby_shape_box_class, "initialize", ruby_shape_box_class_init, MRB_ARGS_OPT(2));

	mrb_define_module_function(mrb, module_collider, "test", ruby_collider_test, MRB_ARGS_REQ(4));

}