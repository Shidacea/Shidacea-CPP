#include "DrawShape.h"

void setup_ruby_class_draw_shape(mrb_state* mrb, RClass* ruby_module) {

	MrbWrap::wrap_class_under<sf::Shape>(mrb, "DrawShape", ruby_module);

	auto ruby_draw_shape_class = MrbWrap::get_class_info_ptr<sf::Shape>();

	MrbWrap::wrap_getter<sf::Shape, &sf::Shape::getFillColor>(mrb, "fill_color");
	MrbWrap::wrap_setter<sf::Shape, &sf::Shape::setFillColor, sf::Color>(mrb, "fill_color=");

	MrbWrap::wrap_getter<sf::Shape, &sf::Shape::getOutlineThickness>(mrb, "outline_thickness");
	MrbWrap::wrap_setter<sf::Shape, &sf::Shape::setOutlineThickness, float>(mrb, "outline_thickness=");

	MrbWrap::wrap_getter<sf::Shape, &sf::Shape::getOutlineColor>(mrb, "outline_color");
	MrbWrap::wrap_setter<sf::Shape, &sf::Shape::setOutlineColor, sf::Color>(mrb, "outline_color=");

	MrbWrap::wrap_getter<sf::Shape, &sf::Shape::getTextureRect>(mrb, "texture_rect");
	MrbWrap::wrap_setter<sf::Shape, &sf::Shape::setTextureRect, sf::IntRect>(mrb, "texture_rect=");

	MrbWrap::wrap_getter<sf::Shape, &sf::Shape::getTextureRect>(mrb, "texture_rect");
	MrbWrap::wrap_setter<sf::Shape, &sf::Shape::setTextureRect, sf::IntRect>(mrb, "texture_rect=");

	MrbWrap::wrap_getter<sf::Shape, &sf::Shape::getPosition>(mrb, "position");
	MrbWrap::wrap_setter<sf::Shape, MrbWrap::specify<sf::Transformable, void, const sf::Vector2f&>(&sf::Shape::setPosition), sf::Vector2f>(mrb, "position=");

	MrbWrap::wrap_getter<sf::Shape, &sf::Shape::getScale>(mrb, "scale");
	MrbWrap::wrap_setter<sf::Shape, MrbWrap::specify<sf::Transformable, void, const sf::Vector2f&>(&sf::Shape::setScale), sf::Vector2f>(mrb, "scale=");

	MrbWrap::wrap_getter<sf::Shape, &sf::Shape::getRotation>(mrb, "rotation");
	MrbWrap::wrap_setter<sf::Shape, &sf::Shape::setRotation, float>(mrb, "rotation=");

	MrbWrap::wrap_getter<sf::Shape, &sf::Shape::getOrigin>(mrb, "origin");
	MrbWrap::wrap_setter<sf::Shape, MrbWrap::specify<sf::Transformable, void, const sf::Vector2f&>(&sf::Shape::setOrigin), sf::Vector2f>(mrb, "origin=");

	MrbWrap::define_member_function(mrb, ruby_draw_shape_class, "link_texture", MRUBY_FUNC {

		auto args = MrbWrap::get_raw_args<sf::Texture>(mrb);
		auto ruby_texture = std::get<0>(args);

		auto shape = MrbWrap::convert_from_object<sf::Shape>(mrb, self);
		auto texture = MrbWrap::convert_from_object<sf::Texture>(mrb, ruby_texture);

		shape->setTexture(texture);

		return mrb_true_value();

	}, MRB_ARGS_REQ(1));

	//! TODO: Implement these using wrapped vertex arrays instead

	//! Point

	MrbWrap::wrap_class_under<PointShape>(mrb, "DrawShapePoint", ruby_module, ruby_draw_shape_class);
	MrbWrap::wrap_constructor<PointShape>(mrb);

	MrbWrap::define_member_function(mrb, MrbWrap::get_class_info_ptr<PointShape>(), "get_from", MRUBY_FUNC {

		auto args = MrbWrap::get_converted_args<ShapePoint>(mrb);
		auto point = std::get<0>(args);

		auto new_point = MrbWrap::convert_from_object<PointShape>(mrb, self);

		new_point->setPoint(sf::Vector2f());

		new_point->setPosition(point.getPosition());
		new_point->setScale(point.getScale());
		new_point->setOrigin(point.getOrigin());
		new_point->setRotation(point.getRotation());

		return mrb_nil_value();

	}, MRB_ARGS_REQ(1));

	//! Line

	MrbWrap::wrap_class_under<LineShape>(mrb, "DrawShapeLine", ruby_module, ruby_draw_shape_class);
	MrbWrap::wrap_constructor<LineShape>(mrb);

	MrbWrap::define_member_function(mrb, MrbWrap::get_class_info_ptr<LineShape>(), "get_from", MRUBY_FUNC {

		auto args = MrbWrap::get_converted_args<ShapeLine>(mrb);
		auto line = std::get<0>(args);

		auto new_line = MrbWrap::convert_from_object<LineShape>(mrb, self);

		new_line->setStartPoint(sf::Vector2f());
		new_line->setEndPoint(line.line);

		new_line->setPosition(line.getPosition());
		new_line->setScale(line.getScale());
		new_line->setOrigin(line.getOrigin());
		new_line->setRotation(line.getRotation());

		return mrb_nil_value();

	}, MRB_ARGS_REQ(1));

	//! Box

	MrbWrap::wrap_class_under<sf::RectangleShape>(mrb, "DrawShapeRectangle", ruby_module, ruby_draw_shape_class);
	MrbWrap::wrap_constructor<sf::RectangleShape>(mrb);

	MrbWrap::define_member_function(mrb, MrbWrap::get_class_info_ptr<sf::RectangleShape>(), "get_from", MRUBY_FUNC {

		auto args = MrbWrap::get_converted_args<ShapeBox>(mrb);
		auto box = std::get<0>(args);

		auto new_rectangle = MrbWrap::convert_from_object<sf::RectangleShape>(mrb, self);

		new_rectangle->setSize(box.size);

		new_rectangle->setPosition(box.getPosition());
		new_rectangle->setScale(box.getScale());
		new_rectangle->setOrigin(box.getOrigin());

		return mrb_nil_value();

	}, MRB_ARGS_REQ(1));

	//! Circle

	MrbWrap::wrap_class_under<sf::CircleShape>(mrb, "DrawShapeCircle", ruby_module, ruby_draw_shape_class);
	MrbWrap::wrap_constructor<sf::CircleShape>(mrb);

	MrbWrap::define_member_function(mrb, MrbWrap::get_class_info_ptr<sf::CircleShape>(), "get_from", MRUBY_FUNC {

		auto args = MrbWrap::get_converted_args<ShapeCircle>(mrb);
		auto circle = std::get<0>(args);

		auto new_circle = MrbWrap::convert_from_object<sf::CircleShape>(mrb, self);

		new_circle->setRadius(circle.radius);

		new_circle->setPosition(circle.getPosition() - sf::Vector2(circle.radius * circle.getSingleArgScale(), circle.radius * circle.getSingleArgScale()));
		new_circle->setScale(circle.getScale());
		new_circle->setOrigin(circle.getOrigin());

		return mrb_nil_value();

	}, MRB_ARGS_REQ(1));

	//! Triangle

	MrbWrap::wrap_class_under<TriangleShape>(mrb, "DrawShapeTriangle", ruby_module, ruby_draw_shape_class);
	MrbWrap::wrap_constructor<TriangleShape>(mrb);

	MrbWrap::define_member_function(mrb, MrbWrap::get_class_info_ptr<TriangleShape>(), "get_from", MRUBY_FUNC {

		auto args = MrbWrap::get_converted_args<ShapeTriangle>(mrb);
		auto triangle = std::get<0>(args);

		auto new_triangle = MrbWrap::convert_from_object<TriangleShape>(mrb, self);

		new_triangle->setPoint(0, sf::Vector2f());
		new_triangle->setPoint(1, triangle.side_1);
		new_triangle->setPoint(2, triangle.side_2);

		new_triangle->setPosition(triangle.getPosition());
		new_triangle->setScale(triangle.getScale());
		new_triangle->setOrigin(triangle.getOrigin());
		new_triangle->setRotation(triangle.getRotation());

		return mrb_nil_value();

	}, MRB_ARGS_REQ(1));

}