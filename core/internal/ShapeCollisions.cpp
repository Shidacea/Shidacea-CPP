#include "Shape.h"

//! Collision algorithms referencing to pure mathematical methods

DEFINE_COLLISION(ShapePoint, ShapePoint) {

	GET_POSITIONS;

	return collision_point_point(x1, y1, x2, y2);

}

DEFINE_COLLISION(ShapePoint, ShapeLine) {

	GET_POSITIONS;

	auto dx2 = shape2.line.x;
	auto dy2 = shape2.line.y;

	return collision_point_line(x1, y1, x2, y2, dx2, dy2);

}

DEFINE_COLLISION(ShapePoint, ShapeCircle) {

	GET_POSITIONS;

	auto r2 = shape2.radius * shape2.scale;

	return collision_point_circle(x1, y1, x2, y2, r2);

}

DEFINE_COLLISION(ShapePoint, ShapeBox) {

	GET_POSITIONS;

	auto w2 = shape2.size.x * shape2.scale.x;
	auto h2 = shape2.size.y * shape2.scale.y;

	return collision_point_box(x1, y1, x2, y2, w2, h2);

}

DEFINE_COLLISION(ShapePoint, ShapeTriangle) {

	GET_POSITIONS;

	auto sxa2 = shape2.side_1.x;
	auto sya2 = shape2.side_1.y;
	auto sxb2 = shape2.side_2.x;
	auto syb2 = shape2.side_2.y;

	return collision_point_triangle(x1, y1, x2, y2, sxa2, sya2, sxb2, syb2);

}

DEFINE_COLLISION(ShapePoint, ShapeQuadrangle) {

	GET_POSITIONS;

	return false;	// TODO

}

DEFINE_COLLISION(ShapePoint, ShapeEllipse) {

	GET_POSITIONS;

	return false;	// TODO

}

DEFINE_COLLISION(ShapeLine, ShapeLine) {

	GET_POSITIONS;

	auto dx1 = shape1.line.x;
	auto dy1 = shape1.line.y;
	auto dx2 = shape2.line.x;
	auto dy2 = shape2.line.y;

	return collision_line_line(x1, y1, dx1, dy1, x2, y2, dx2, dy2);

}

DEFINE_COLLISION(ShapeLine, ShapeCircle) {

	GET_POSITIONS;

	auto dx1 = shape1.line.x;
	auto dy1 = shape1.line.y;
	auto r2 = shape2.radius;

	return collision_line_circle(x1, y1, dx1, dy1, x2, y2, r2);

}

DEFINE_COLLISION(ShapeLine, ShapeBox) {

	GET_POSITIONS;

	auto dx1 = shape1.line.x;
	auto dy1 = shape1.line.y;
	auto w2 = shape2.size.x * shape2.scale.x;
	auto h2 = shape2.size.y * shape2.scale.y;

	return collision_line_box(x1, y1, dx1, dy1, x2, y2, w2, h2);

}

DEFINE_COLLISION(ShapeLine, ShapeTriangle) {

	GET_POSITIONS;

	auto dx1 = shape1.line.x;
	auto dy1 = shape1.line.y;

	auto sxa2 = shape2.side_1.x;
	auto sya2 = shape2.side_1.y;
	auto sxb2 = shape2.side_2.x;
	auto syb2 = shape2.side_2.y;

	return collision_point_triangle(x1, y1, x2, y2, sxa2, sya2, sxb2, syb2);

}

DEFINE_COLLISION(ShapeLine, ShapeQuadrangle) {

	GET_POSITIONS;

	return false;	// TODO

}

DEFINE_COLLISION(ShapeLine, ShapeEllipse) {

	GET_POSITIONS;

	return false;	// TODO

}

DEFINE_COLLISION(ShapeCircle, ShapeCircle) {

	GET_POSITIONS;

	auto r1 = shape1.radius * shape1.scale;
	auto r2 = shape2.radius * shape2.scale;

	return collision_circle_circle(x1, y1, r1, x2, y2, r2);

}

DEFINE_COLLISION(ShapeCircle, ShapeBox) {

	GET_POSITIONS;

	auto r1 = shape1.radius * shape1.scale;

	auto w2 = shape2.size.x * shape2.scale.x;
	auto h2 = shape2.size.y * shape2.scale.y;

	return collision_circle_box(x1, y1, r1, x2, y2, w2, h2);

}

DEFINE_COLLISION(ShapeCircle, ShapeTriangle) {

	GET_POSITIONS;

	return false;	// TODO

}

DEFINE_COLLISION(ShapeCircle, ShapeQuadrangle) {

	GET_POSITIONS;

	return false;	// TODO

}

DEFINE_COLLISION(ShapeCircle, ShapeEllipse) {

	GET_POSITIONS;

	return false;	// TODO

}

DEFINE_COLLISION(ShapeBox, ShapeBox) {

	GET_POSITIONS;

	auto w1 = shape1.size.x * shape1.scale.x;
	auto h1 = shape1.size.y * shape1.scale.y;

	auto w2 = shape2.size.x * shape2.scale.x;
	auto h2 = shape2.size.y * shape2.scale.y;

	return collision_box_box(x1, y1, w1, h1, x2, y2, w2, h2);

}

DEFINE_COLLISION(ShapeBox, ShapeTriangle) {

	GET_POSITIONS;

	return false;	// TODO

}

DEFINE_COLLISION(ShapeBox, ShapeQuadrangle) {

	GET_POSITIONS;

	return false;	// TODO

}

DEFINE_COLLISION(ShapeBox, ShapeEllipse) {

	GET_POSITIONS;

	return false;	// TODO

}

DEFINE_COLLISION(ShapeTriangle, ShapeTriangle) {

	GET_POSITIONS;

	return false;	// TODO

}

DEFINE_COLLISION(ShapeTriangle, ShapeQuadrangle) {

	GET_POSITIONS;

	return false;	// TODO

}

DEFINE_COLLISION(ShapeTriangle, ShapeEllipse) {

	GET_POSITIONS;

	return false;	// TODO

}

DEFINE_COLLISION(ShapeQuadrangle, ShapeQuadrangle) {

	GET_POSITIONS;

	return false;	// TODO

}

DEFINE_COLLISION(ShapeQuadrangle, ShapeEllipse) {

	GET_POSITIONS;

	return false;	// TODO

}

DEFINE_COLLISION(ShapeEllipse, ShapeEllipse) {

	GET_POSITIONS;

	return false;	// TODO

}