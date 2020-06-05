#include "Shape.h"

#include "ShapeCollisions.cpp"

ShapeType get_type_of_ruby_shape(mrb_state* mrb, mrb_value ruby_shape) {

	if (mrb_obj_is_instance_of(mrb, ruby_shape, MrbWrap::get_class_info_ptr<ShapePoint>())) return ShapeType::Point;
	else if (mrb_obj_is_instance_of(mrb, ruby_shape, MrbWrap::get_class_info_ptr<ShapeLine>())) return ShapeType::Line;
	else if (mrb_obj_is_instance_of(mrb, ruby_shape, MrbWrap::get_class_info_ptr<ShapeCircle>())) return ShapeType::Circle;
	else if (mrb_obj_is_instance_of(mrb, ruby_shape, MrbWrap::get_class_info_ptr<ShapeBox>())) return ShapeType::Box;
	else if (mrb_obj_is_instance_of(mrb, ruby_shape, MrbWrap::get_class_info_ptr<ShapeTriangle>())) return ShapeType::Triangle;
	else if (mrb_obj_is_instance_of(mrb, ruby_shape, MrbWrap::get_class_info_ptr<ShapeQuadrangle>())) return ShapeType::Quadrangle;
	else if (mrb_obj_is_instance_of(mrb, ruby_shape, MrbWrap::get_class_info_ptr<ShapeEllipse>())) return ShapeType::Ellipse;
	else return ShapeType::Unknown;

}

void setup_ruby_collider(mrb_state* mrb, RClass* ruby_module) {

	shape_ruby_module = ruby_module;

	auto module_collider = mrb_define_module_under(mrb, ruby_module, "Collider");

	MrbWrap::wrap_class_under<Shape>(mrb, "CollisionShape", ruby_module);

	auto ruby_shape_class = MrbWrap::get_class_info_ptr<Shape>();

	MrbWrap::wrap_class_under<ShapePoint>(mrb, "CollisionShapePoint", ruby_module, ruby_shape_class);
	MrbWrap::wrap_class_under<ShapeLine>(mrb, "CollisionShapeLine", ruby_module, ruby_shape_class);
	MrbWrap::wrap_class_under<ShapeCircle>(mrb, "CollisionShapeCircle", ruby_module, ruby_shape_class);
	MrbWrap::wrap_class_under<ShapeBox>(mrb, "CollisionShapeBox", ruby_module, ruby_shape_class);
	MrbWrap::wrap_class_under<ShapeTriangle>(mrb, "CollisionShapeTriangle", ruby_module, ruby_shape_class);
	MrbWrap::wrap_class_under<ShapeQuadrangle>(mrb, "CollisionShapeQuadrangle", ruby_module, ruby_shape_class);
	MrbWrap::wrap_class_under<ShapeEllipse>(mrb, "CollisionShapeEllipse", ruby_module, ruby_shape_class);

	auto ruby_shape_point_class = MrbWrap::get_class_info_ptr<ShapePoint>();
	auto ruby_shape_line_class = MrbWrap::get_class_info_ptr<ShapeLine>();
	auto ruby_shape_circle_class = MrbWrap::get_class_info_ptr<ShapeCircle>();
	auto ruby_shape_box_class = MrbWrap::get_class_info_ptr<ShapeBox>();
	auto ruby_shape_triangle_class = MrbWrap::get_class_info_ptr<ShapeTriangle>();
	auto ruby_shape_quadrangle_class = MrbWrap::get_class_info_ptr<ShapeQuadrangle>();
	auto ruby_shape_ellipse_class = MrbWrap::get_class_info_ptr<ShapeEllipse>();

	MrbWrap::wrap_constructor<Shape>(mrb);

	MrbWrap::wrap_getter<Shape, &Shape::getPosition>(mrb, "offset");
	MrbWrap::wrap_setter<Shape, MrbWrap::specify<sf::Transformable, void, const sf::Vector2f&>(&Shape::setPosition), sf::Vector2f>(mrb, "offset=");

	MrbWrap::wrap_getter<Shape, &Shape::getOrigin>(mrb, "origin");
	MrbWrap::wrap_setter<Shape, MrbWrap::specify<sf::Transformable, void, const sf::Vector2f&>(&Shape::setOrigin), sf::Vector2f>(mrb, "origin=");

	//! TODO: Write standard constructors accepting the respective arguments

	MrbWrap::define_member_function(mrb, ruby_shape_point_class, "initialize", MRUBY_FUNC {

		auto args = MrbWrap::get_converted_args<sf::Vector2f>(mrb);
		auto offset = std::get<0>(args);

		auto shape = MrbWrap::convert_to_object<ShapePoint>(mrb, self);
		shape->setPosition(offset);

		return self;

	}, MRB_ARGS_REQ(1));

	MrbWrap::define_default_copy_init<ShapePoint>(mrb);

	MrbWrap::define_member_function(mrb, ruby_shape_line_class, "initialize", MRUBY_FUNC {

		auto args = MrbWrap::get_converted_args<sf::Vector2f, sf::Vector2f>(mrb);
		auto offset = std::get<0>(args);
		auto coordinates = std::get<1>(args);

		auto shape = MrbWrap::convert_to_object<ShapeLine>(mrb, self);
		shape->line = coordinates;
		shape->setPosition(offset);

		return self;

	}, MRB_ARGS_REQ(2));

	MrbWrap::define_default_copy_init<ShapeLine>(mrb);

	MrbWrap::wrap_getter<ShapeLine, &ShapeLine::line>(mrb, "line");
	MrbWrap::wrap_setter<ShapeLine, &ShapeLine::line, sf::Vector2f>(mrb, "line=");

	MrbWrap::define_member_function(mrb, ruby_shape_circle_class, "initialize", MRUBY_FUNC {

		auto args = MrbWrap::get_converted_args<sf::Vector2f, float>(mrb);
		auto offset = std::get<0>(args);
		auto radius = std::get<1>(args);

		auto shape = MrbWrap::convert_to_object<ShapeCircle>(mrb, self);
		shape->radius = radius;
		shape->setPosition(offset);

		return self;

	}, MRB_ARGS_REQ(2));

	MrbWrap::define_default_copy_init<ShapeCircle>(mrb);

	MrbWrap::wrap_getter<ShapeCircle, &ShapeCircle::radius>(mrb, "radius");
	MrbWrap::wrap_setter<ShapeCircle, &ShapeCircle::radius, float>(mrb, "radius=");

	MrbWrap::wrap_getter<ShapeCircle, &ShapeCircle::getSingleArgScale>(mrb, "scale");
	MrbWrap::wrap_setter<ShapeCircle, &ShapeCircle::setSingleArgScale, float>(mrb, "scale=");

	MrbWrap::define_member_function(mrb, ruby_shape_box_class, "initialize", MRUBY_FUNC {

		auto args = MrbWrap::get_converted_args<sf::Vector2f, sf::Vector2f>(mrb);
		auto offset = std::get<0>(args);
		auto coordinates = std::get<1>(args);

		auto shape = MrbWrap::convert_to_object<ShapeBox>(mrb, self);
		shape->size = coordinates;
		shape->setPosition(offset);

		return self;

	}, MRB_ARGS_REQ(2));

	MrbWrap::define_default_copy_init<ShapeBox>(mrb);

	MrbWrap::wrap_getter<ShapeBox, &ShapeBox::size>(mrb, "size");
	MrbWrap::wrap_setter<ShapeBox, &ShapeBox::size, sf::Vector2f>(mrb, "size=");

	MrbWrap::wrap_getter<ShapeBox, &ShapeBox::getScale>(mrb, "scale");
	MrbWrap::wrap_setter<ShapeBox, MrbWrap::specify<sf::Transformable, void, const sf::Vector2f&>(&ShapeBox::setScale), sf::Vector2f>(mrb, "scale=");

	MrbWrap::define_member_function(mrb, ruby_shape_triangle_class, "initialize", MRUBY_FUNC {

		auto args = MrbWrap::get_converted_args<sf::Vector2f, sf::Vector2f, sf::Vector2f>(mrb);
		auto offset = std::get<0>(args);
		auto side_1 = std::get<1>(args);
		auto side_2 = std::get<2>(args);

		auto shape = MrbWrap::convert_to_object<ShapeTriangle>(mrb, self);
		shape->side_1 = side_1;
		shape->side_2 = side_2;
		shape->setPosition(offset);

		return self;

	}, MRB_ARGS_REQ(3));

	MrbWrap::define_default_copy_init<ShapeTriangle>(mrb);

	MrbWrap::wrap_getter<ShapeTriangle, &ShapeTriangle::side_1>(mrb, "side_1");
	MrbWrap::wrap_setter<ShapeTriangle, &ShapeTriangle::side_1, sf::Vector2f>(mrb, "side_1=");

	MrbWrap::wrap_getter<ShapeTriangle, &ShapeTriangle::side_2>(mrb, "side_2");
	MrbWrap::wrap_setter<ShapeTriangle, &ShapeTriangle::side_2, sf::Vector2f>(mrb, "side_2=");

	MrbWrap::wrap_getter<ShapeTriangle, &ShapeTriangle::getScale>(mrb, "scale");
	MrbWrap::wrap_setter<ShapeTriangle, MrbWrap::specify<sf::Transformable, void, const sf::Vector2f&>(&ShapeTriangle::setScale), sf::Vector2f>(mrb, "scale=");

	MrbWrap::define_member_function(mrb, ruby_shape_quadrangle_class, "initialize", MRUBY_FUNC {

		//! TODO

		auto shape = MrbWrap::convert_to_object<ShapeQuadrangle>(mrb, self);

		//auto offset = MrbWrap::convert_from_object<sf::Vector2f>(mrb, ruby_offset);
		//shape->offset = *offset;

		return self;

	}, MRB_ARGS_NONE());

	MrbWrap::define_default_copy_init<ShapeQuadrangle>(mrb);

	MrbWrap::define_member_function(mrb, ruby_shape_ellipse_class, "initialize", MRUBY_FUNC {

		auto args = MrbWrap::get_converted_args<sf::Vector2f, sf::Vector2f>(mrb);
		auto offset = std::get<0>(args);
		auto coordinates = std::get<1>(args);

		auto shape = MrbWrap::convert_from_object<ShapeEllipse>(mrb, self);
		shape->semiaxes = coordinates;
		shape->setPosition(offset);

		return self;

	}, MRB_ARGS_REQ(2));

	MrbWrap::define_default_copy_init<ShapeEllipse>(mrb);

	MrbWrap::define_module_function(mrb, module_collider, "test", MRUBY_FUNC {

		mrb_value ruby_shape_1;
		mrb_value ruby_shape_2;
		mrb_value ruby_pos_1;
		mrb_value ruby_pos_2;

		//! There seem to be ghoooosts

		//! TODO: Add method without additional offset maybe

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

	}, MRB_ARGS_REQ(4));

}
