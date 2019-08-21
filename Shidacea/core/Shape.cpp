#include "Shape.h"

#include "ShapeCollisions.cpp"

mrb_value ruby_collider_test(mrb_state* mrb, mrb_value self) {

	mrb_value ruby_shape_1;
	mrb_value ruby_shape_2;
	mrb_value ruby_pos_1;
	mrb_value ruby_pos_2;

	//! There seem to be ghoooosts

	mrb_get_args(mrb, "oooo", &ruby_shape_1, &ruby_pos_1, &ruby_shape_2, &ruby_pos_2);

	auto type_1 = get_type_of_ruby_shape(mrb, ruby_shape_1);
	auto type_2 = get_type_of_ruby_shape(mrb, ruby_shape_2);

	auto pos_1 = MrbWrap::convert_from_object<sf::Vector2f>(mrb, ruby_pos_1);
	auto pos_2 = MrbWrap::convert_from_object<sf::Vector2f>(mrb, ruby_pos_2);

	auto result = false;
	
	//! A bit hacky, but we don't want to repeat ourselves too many times
	//! Also, this makes the code MUCH more readable and extendable

	TEST_COLLISION_CASE(Point, Point)
	else TEST_COLLISION_CASE_WITH_REVERSE(Point, Line)
	else TEST_COLLISION_CASE_WITH_REVERSE(Point, Circle)
	else TEST_COLLISION_CASE_WITH_REVERSE(Point, Box)
	else TEST_COLLISION_CASE_WITH_REVERSE(Point, Triangle)
	else TEST_COLLISION_CASE_WITH_REVERSE(Point, Quadrangle)
	else TEST_COLLISION_CASE_WITH_REVERSE(Point, Ellipse)
	else TEST_COLLISION_CASE(Line, Line)
	else TEST_COLLISION_CASE_WITH_REVERSE(Line, Circle)
	else TEST_COLLISION_CASE_WITH_REVERSE(Line, Box)
	else TEST_COLLISION_CASE_WITH_REVERSE(Line, Triangle)
	else TEST_COLLISION_CASE_WITH_REVERSE(Line, Quadrangle)
	else TEST_COLLISION_CASE_WITH_REVERSE(Line, Ellipse)
	else TEST_COLLISION_CASE(Circle, Circle)
	else TEST_COLLISION_CASE_WITH_REVERSE(Circle, Box)
	else TEST_COLLISION_CASE_WITH_REVERSE(Circle, Triangle)
	else TEST_COLLISION_CASE_WITH_REVERSE(Circle, Quadrangle)
	else TEST_COLLISION_CASE_WITH_REVERSE(Circle, Ellipse)
	else TEST_COLLISION_CASE(Box, Box)
	else TEST_COLLISION_CASE_WITH_REVERSE(Box, Triangle)
	else TEST_COLLISION_CASE_WITH_REVERSE(Box, Quadrangle)
	else TEST_COLLISION_CASE_WITH_REVERSE(Box, Ellipse)
	else TEST_COLLISION_CASE(Triangle, Triangle)
	else TEST_COLLISION_CASE_WITH_REVERSE(Triangle, Quadrangle)
	else TEST_COLLISION_CASE_WITH_REVERSE(Triangle, Ellipse)
	else TEST_COLLISION_CASE(Quadrangle, Quadrangle)
	else TEST_COLLISION_CASE_WITH_REVERSE(Quadrangle, Ellipse)
	else TEST_COLLISION_CASE(Ellipse, Ellipse)

	//! Other invalid cases will only yield false for now

	return mrb_bool_value(result);

}

ShapeType get_type_of_ruby_shape(mrb_state* mrb, mrb_value ruby_shape) {

	static auto ruby_class_shape_point = mrb_class_get(mrb, "ShapePoint");
	static auto ruby_class_shape_line = mrb_class_get(mrb, "ShapeLine");
	static auto ruby_class_shape_circle = mrb_class_get(mrb, "ShapeCircle");
	static auto ruby_class_shape_box = mrb_class_get(mrb, "ShapeBox");
	static auto ruby_class_shape_triangle = mrb_class_get(mrb, "ShapeTriangle");
	static auto ruby_class_shape_quadrangle = mrb_class_get(mrb, "ShapeQuadrangle");
	static auto ruby_class_shape_ellipse = mrb_class_get(mrb, "ShapeEllipse");

	if (mrb_obj_is_instance_of(mrb, ruby_shape, ruby_class_shape_point)) return ShapeType::Point;
	else if (mrb_obj_is_instance_of(mrb, ruby_shape, ruby_class_shape_line)) return ShapeType::Line;
	else if (mrb_obj_is_instance_of(mrb, ruby_shape, ruby_class_shape_circle)) return ShapeType::Circle;
	else if (mrb_obj_is_instance_of(mrb, ruby_shape, ruby_class_shape_box)) return ShapeType::Box;
	else if (mrb_obj_is_instance_of(mrb, ruby_shape, ruby_class_shape_triangle)) return ShapeType::Triangle;
	else if (mrb_obj_is_instance_of(mrb, ruby_shape, ruby_class_shape_quadrangle)) return ShapeType::Quadrangle;
	else if (mrb_obj_is_instance_of(mrb, ruby_shape, ruby_class_shape_ellipse)) return ShapeType::Ellipse;
	else return ShapeType::Unknown;

}

mrb_value ruby_shape_class_init(mrb_state* mrb, mrb_value self) {

	return self;

}

mrb_value ruby_shape_point_class_init(mrb_state* mrb, mrb_value self) {

	auto shape = MrbWrap::convert_to_object<ShapePoint>(mrb, self);
	return self;

}

mrb_value ruby_shape_line_class_init(mrb_state* mrb, mrb_value self) {

	mrb_value ruby_offset;
	mrb_value ruby_coordinates;

	mrb_get_args(mrb, "oo", &ruby_offset, &ruby_coordinates);

	auto coordinates = MrbWrap::convert_from_object<sf::Vector2f>(mrb, ruby_coordinates);

	auto shape = MrbWrap::convert_to_object<ShapeLine>(mrb, self);
	shape->line = *coordinates;

	auto offset = MrbWrap::convert_from_object<sf::Vector2f>(mrb, ruby_offset);
	shape->offset = *offset;

	return self;

}

mrb_value ruby_shape_circle_class_init(mrb_state* mrb, mrb_value self) {

	mrb_value ruby_offset;
	float radius;

	mrb_get_args(mrb, "of", &ruby_offset, &radius);

	auto shape = MrbWrap::convert_to_object<ShapeCircle>(mrb, self);
	shape->radius = radius;
	shape->initial_radius = radius;

	auto offset = MrbWrap::convert_from_object<sf::Vector2f>(mrb, ruby_offset);
	shape->offset = *offset;

	return self;

}

mrb_value ruby_shape_circle_class_radius(mrb_state* mrb, mrb_value self) {

	auto shape = MrbWrap::convert_from_object<ShapeCircle>(mrb, self);

	return mrb_float_value(mrb, shape->radius);

}

mrb_value ruby_shape_circle_class_scale(mrb_state* mrb, mrb_value self) {

	float factor;

	mrb_get_args(mrb, "f", &factor);

	auto shape = MrbWrap::convert_from_object<ShapeCircle>(mrb, self);
	shape->radius *= factor;

	return mrb_nil_value();

}

mrb_value ruby_shape_circle_class_reset(mrb_state* mrb, mrb_value self) {

	auto shape = MrbWrap::convert_from_object<ShapeCircle>(mrb, self);
	shape->radius = shape->initial_radius;

	return mrb_nil_value();
	
}

mrb_value ruby_shape_box_class_init(mrb_state* mrb, mrb_value self) {

	mrb_value ruby_offset;
	mrb_value ruby_coordinates;

	mrb_get_args(mrb, "oo", &ruby_offset, &ruby_coordinates);

	auto coordinates = MrbWrap::convert_from_object<sf::Vector2f>(mrb, ruby_coordinates);

	auto shape = MrbWrap::convert_to_object<ShapeBox>(mrb, self);
	shape->diagonal = *coordinates;
	shape->initial_diagonal = *coordinates;

	auto offset = MrbWrap::convert_from_object<sf::Vector2f>(mrb, ruby_offset);
	shape->offset = *offset;

	return self;

}

mrb_value ruby_shape_box_class_diagonal(mrb_state* mrb, mrb_value self) {

	auto shape = MrbWrap::convert_to_object<ShapeBox>(mrb, self);

	static auto coordinates_class = mrb_class_get(mrb, "Coordinates");

	auto new_coordinates = mrb_obj_new(mrb, coordinates_class, 0, NULL);
	auto new_vector = MrbWrap::convert_from_object<sf::Vector2f>(mrb, new_coordinates);

	*new_vector = shape->diagonal;

	return new_coordinates;

}

mrb_value ruby_shape_box_class_scale(mrb_state* mrb, mrb_value self) {

	mrb_value factors;

	mrb_get_args(mrb, "o", &factors);

	auto shape = MrbWrap::convert_from_object<ShapeBox>(mrb, self);

	if (mrb_float_p(factors)) {

		auto factor = mrb_float(factors);
		shape->diagonal *= static_cast<float>(factor);

	}
	else {

		auto factor_vector = MrbWrap::convert_from_object<sf::Vector2f>(mrb, factors);
		shape->diagonal.x *= factor_vector->x;
		shape->diagonal.y *= factor_vector->y;
	}

	return mrb_nil_value();

}

mrb_value ruby_shape_box_class_reset(mrb_state* mrb, mrb_value self) {

	auto shape = MrbWrap::convert_from_object<ShapeBox>(mrb, self);
	shape->diagonal = shape->initial_diagonal;

	return mrb_nil_value();

}

mrb_value ruby_shape_triangle_class_init(mrb_state* mrb, mrb_value self) {

	//! TODO

	auto shape = MrbWrap::convert_to_object<ShapeTriangle>(mrb, self);

	//auto offset = MrbWrap::convert_from_object<sf::Vector2f>(mrb, ruby_offset);
	//shape->offset = *offset;

	return self;

}

mrb_value ruby_shape_quadrangle_class_init(mrb_state* mrb, mrb_value self) {

	//! TODO

	auto shape = MrbWrap::convert_to_object<ShapeQuadrangle>(mrb, self);

	//auto offset = MrbWrap::convert_from_object<sf::Vector2f>(mrb, ruby_offset);
	//shape->offset = *offset;

	return self;

}

mrb_value ruby_shape_ellipse_class_init(mrb_state* mrb, mrb_value self) {

	mrb_value ruby_offset;
	mrb_value ruby_coordinates;

	mrb_get_args(mrb, "oo", &ruby_offset, &ruby_coordinates);

	auto coordinates = MrbWrap::convert_from_object<sf::Vector2f>(mrb, ruby_coordinates);

	auto shape = MrbWrap::convert_to_object<ShapeEllipse>(mrb, self);
	shape->semiaxes = *coordinates;

	auto offset = MrbWrap::convert_from_object<sf::Vector2f>(mrb, ruby_offset);
	shape->offset = *offset;

	return self;

}

mrb_value ruby_shape_class_offset(mrb_state* mrb, mrb_value self) {

	auto shape = MrbWrap::convert_from_object<Shape>(mrb, self);

	static auto coordinates_class = mrb_class_get(mrb, "Coordinates");

	auto new_coordinates = mrb_obj_new(mrb, coordinates_class, 0, NULL);
	auto new_vector = MrbWrap::convert_from_object<sf::Vector2f>(mrb, new_coordinates);

	*new_vector = shape->offset;

	return new_coordinates;

}

mrb_value ruby_shape_class_offset_equals(mrb_state* mrb, mrb_value self) {

	mrb_value ruby_coordinates;

	mrb_get_args(mrb, "o", &ruby_coordinates);

	auto shape = MrbWrap::convert_from_object<Shape>(mrb, self);
	auto coordinates = MrbWrap::convert_from_object<sf::Vector2f>(mrb, ruby_coordinates);

	shape->offset = *coordinates;

	return ruby_coordinates;

}

void setup_ruby_collider(mrb_state* mrb) {

	auto module_collider = mrb_define_module(mrb, "Collider");
	auto ruby_shape_class = mrb_define_class(mrb, "Shape", mrb->object_class);

	auto ruby_shape_point_class = MrbWrap::define_data_class(mrb, "ShapePoint", ruby_shape_class);
	auto ruby_shape_line_class = MrbWrap::define_data_class(mrb, "ShapeLine", ruby_shape_class);
	auto ruby_shape_circle_class = MrbWrap::define_data_class(mrb, "ShapeCircle", ruby_shape_class);
	auto ruby_shape_box_class = MrbWrap::define_data_class(mrb, "ShapeBox", ruby_shape_class);
	auto ruby_shape_triangle_class = MrbWrap::define_data_class(mrb, "ShapeTriangle", ruby_shape_class);
	auto ruby_shape_quadrangle_class = MrbWrap::define_data_class(mrb, "ShapeQuadrangle", ruby_shape_class);
	auto ruby_shape_ellipse_class = MrbWrap::define_data_class(mrb, "ShapeEllipse", ruby_shape_class);

	mrb_define_method(mrb, ruby_shape_class, "initialize", ruby_shape_class_init, MRB_ARGS_NONE());

	mrb_define_method(mrb, ruby_shape_point_class, "initialize", ruby_shape_point_class_init, MRB_ARGS_REQ(1));
	MrbWrap::define_default_copy_init<ShapePoint>(mrb, ruby_shape_point_class);

	mrb_define_method(mrb, ruby_shape_line_class, "initialize", ruby_shape_line_class_init, MRB_ARGS_REQ(2));
	MrbWrap::define_default_copy_init<ShapeLine>(mrb, ruby_shape_line_class);

	mrb_define_method(mrb, ruby_shape_circle_class, "initialize", ruby_shape_circle_class_init, MRB_ARGS_REQ(2));
	MrbWrap::define_default_copy_init<ShapeCircle>(mrb, ruby_shape_circle_class);
	mrb_define_method(mrb, ruby_shape_circle_class, "radius", ruby_shape_circle_class_radius, MRB_ARGS_NONE());
	mrb_define_method(mrb, ruby_shape_circle_class, "scale", ruby_shape_circle_class_scale, MRB_ARGS_REQ(1));
	mrb_define_method(mrb, ruby_shape_circle_class, "reset", ruby_shape_circle_class_reset, MRB_ARGS_NONE());	//! TODO: Replace this all with attribute accessors

	mrb_define_method(mrb, ruby_shape_box_class, "initialize", ruby_shape_box_class_init, MRB_ARGS_REQ(2));
	MrbWrap::define_default_copy_init<ShapeBox>(mrb, ruby_shape_box_class);
	mrb_define_method(mrb, ruby_shape_box_class, "diagonal", ruby_shape_box_class_diagonal, MRB_ARGS_NONE());
	mrb_define_method(mrb, ruby_shape_box_class, "scale", ruby_shape_box_class_scale, MRB_ARGS_REQ(1));
	mrb_define_method(mrb, ruby_shape_box_class, "reset", ruby_shape_box_class_reset, MRB_ARGS_NONE());

	mrb_define_method(mrb, ruby_shape_triangle_class, "initialize", ruby_shape_triangle_class_init, MRB_ARGS_NONE());	//! TODO
	MrbWrap::define_default_copy_init<ShapeTriangle>(mrb, ruby_shape_triangle_class);

	mrb_define_method(mrb, ruby_shape_quadrangle_class, "initialize", ruby_shape_quadrangle_class_init, MRB_ARGS_NONE());	//! TODO
	MrbWrap::define_default_copy_init<ShapeQuadrangle>(mrb, ruby_shape_quadrangle_class);

	mrb_define_method(mrb, ruby_shape_ellipse_class, "initialize", ruby_shape_ellipse_class_init, MRB_ARGS_REQ(2));
	MrbWrap::define_default_copy_init<ShapeEllipse>(mrb, ruby_shape_ellipse_class);

	mrb_define_method(mrb, ruby_shape_class, "offset", ruby_shape_class_offset, MRB_ARGS_NONE());
	mrb_define_method(mrb, ruby_shape_class, "offset=", ruby_shape_class_offset_equals, MRB_ARGS_REQ(1));

	mrb_define_module_function(mrb, module_collider, "test", ruby_collider_test, MRB_ARGS_REQ(4));

}
