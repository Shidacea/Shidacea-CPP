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
if (type_1 == ShapeType::type1 && type_2 == ShapeType::type2) { \
auto shape_1 = MrbWrap::convert_from_object<Shape##type1>(mrb, ruby_shape_1); \
auto shape_2 = MrbWrap::convert_from_object<Shape##type2>(mrb, ruby_shape_2); \
auto offset_1 = shape_1->offset; \
auto offset_2 = shape_2->offset; \
result = check_collision(*shape_1, *shape_2, *pos_1 + offset_1, *pos_2 + offset_2); \
}

//! A lot of code just to define the same function in reverse
//! This macro is just a concatenation of the part above together with its reversed form

#define TEST_COLLISION_CASE_WITH_REVERSE(type1, type2) \
if (type_1 == ShapeType::type1 && type_2 == ShapeType::type2) { \
auto shape_1 = MrbWrap::convert_from_object<Shape##type1>(mrb, ruby_shape_1); \
auto shape_2 = MrbWrap::convert_from_object<Shape##type2>(mrb, ruby_shape_2); \
auto offset_1 = shape_1->offset; \
auto offset_2 = shape_2->offset; \
result = check_collision(*shape_1, *shape_2, *pos_1 + offset_1, *pos_2 + offset_2); \
} \
else if (type_1 == ShapeType::type2 && type_2 == ShapeType::type1) { \
auto shape_1 = MrbWrap::convert_from_object<Shape##type2>(mrb, ruby_shape_1); \
auto shape_2 = MrbWrap::convert_from_object<Shape##type1>(mrb, ruby_shape_2); \
auto offset_1 = shape_1->offset; \
auto offset_2 = shape_2->offset; \
result = check_collision(*shape_2, *shape_1, *pos_2 + offset_2, *pos_1 + offset_1); \
}

class Shape {

public:

	sf::Vector2f offset;

};

class ShapePoint : public Shape {

};

class ShapeLine : public Shape {

public:

	sf::Vector2f line;

};

class ShapeCircle : public Shape {

public:

	float radius = 0.0;
	float scale = 1.0;

};

class ShapeBox : public Shape {

public:

	sf::Vector2f size = {0.0, 0.0};
	sf::Vector2f scale = {1.0, 1.0};

};

struct ShapeTriangle : public Shape {

public:

	//! TODO

};

struct ShapeQuadrangle : public Shape {

public:

	//! TODO

};

struct ShapeEllipse : public Shape {

public:

	sf::Vector2f semiaxes;

};

enum class ShapeType {

	Unknown = 0,
	Point,
	Line,
	Circle,
	Box,
	Triangle,
	Quadrangle,
	Ellipse

};

template <class T1, class T2> bool check_collision(T1 shape1, T2 shape2, sf::Vector2f pos1, sf::Vector2f pos2);

ShapeType get_type_of_ruby_shape(mrb_state* mrb, mrb_value ruby_shape);

void setup_ruby_collider(mrb_state* mrb, RClass* ruby_module);

static RClass* shape_ruby_module;