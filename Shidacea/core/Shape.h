#pragma once

#include <SFML/Graphics.hpp>

#include "Collisions.h"
#include "Helper.h"

#define GET_POSITIONS \
auto x1 = pos1.x; \
auto y1 = pos1.y; \
auto x2 = pos2.x; \
auto y2 = pos2.y;

#define DEFINE_COLLISION(type1, type2) template <> bool check_collision(type1 shape1, type2 shape2, sf::Vector2f pos1, sf::Vector2f pos2)

#define TEST_COLLISION_CASE(type1, type2) \
if (type_1 == ShapeType::##type1 && type_2 == ShapeType::##type2) { \
auto shape_1 = MrbWrap::convert_from_instance_variable<Shape##type1>(mrb, ruby_shape_1, "@_shape"); \
auto shape_2 = MrbWrap::convert_from_instance_variable<Shape##type2>(mrb, ruby_shape_2, "@_shape"); \
result = check_collision(*shape_1, *shape_2, *pos_1, *pos_2); \
}

// type1=Circle, type2=Box
// type_1=Box, type_2=Circle

#define TEST_COLLISION_CASE_REVERSE(type1, type2) \
if (type_1 == ShapeType::##type2 && type_2 == ShapeType::##type1) { \
auto shape_1 = MrbWrap::convert_from_instance_variable<Shape##type2>(mrb, ruby_shape_1, "@_shape"); \
auto shape_2 = MrbWrap::convert_from_instance_variable<Shape##type1>(mrb, ruby_shape_2, "@_shape"); \
result = check_collision(*shape_2, *shape_2, *pos_2, *pos_1); \
}

struct ShapeCircle {

	float radius;

};

struct ShapeBox {

	float width;
	float height;

};

enum class ShapeType {

	Unknown = 0,
	Circle,
	Box

};

ShapeType get_type_of_ruby_shape(mrb_state* mrb, mrb_value ruby_shape);
mrb_value ruby_collider_test(mrb_state* mrb, mrb_value self);
template <class T1, class T2> bool check_collision(T1 shape1, T2 shape2, sf::Vector2f pos1, sf::Vector2f pos2);

mrb_value ruby_shape_class_init(mrb_state* mrb, mrb_value self);
mrb_value ruby_shape_circle_class_init(mrb_state* mrb, mrb_value self);
mrb_value ruby_shape_box_class_init(mrb_state* mrb, mrb_value self);

void setup_ruby_collider(mrb_state* mrb);