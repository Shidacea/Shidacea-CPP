#include "Shape.h"

//! Collision algorithms referencing to pure mathematical methods

DEFINE_COLLISION(ShapePoint, ShapePoint) {

	GET_POSITIONS

	return collision_point_point(x1, y1, x2, y2);

}

DEFINE_COLLISION(ShapePoint, ShapeLine) {

	return false;	// TODO

}

DEFINE_COLLISION(ShapePoint, ShapeCircle) {

	return false;	// TODO

}

DEFINE_COLLISION(ShapePoint, ShapeBox) {

	return false;	// TODO

}

DEFINE_COLLISION(ShapePoint, ShapeTriangle) {

	return false;	// TODO

}

DEFINE_COLLISION(ShapePoint, ShapeQuadrangle) {

	return false;	// TODO

}

DEFINE_COLLISION(ShapePoint, ShapeEllipse) {

	return false;	// TODO

}

DEFINE_COLLISION(ShapeLine, ShapeLine) {

	return false;	// TODO

}

DEFINE_COLLISION(ShapeLine, ShapeCircle) {

	return false;	// TODO

}

DEFINE_COLLISION(ShapeLine, ShapeBox) {

	return false;	// TODO

}

DEFINE_COLLISION(ShapeLine, ShapeTriangle) {

	return false;	// TODO

}

DEFINE_COLLISION(ShapeLine, ShapeQuadrangle) {

	return false;	// TODO

}

DEFINE_COLLISION(ShapeLine, ShapeEllipse) {

	return false;	// TODO

}

DEFINE_COLLISION(ShapeCircle, ShapeCircle) {

	GET_POSITIONS

	auto r1 = shape1.radius * shape1.scale;
	auto r2 = shape2.radius * shape2.scale;

	return collision_circle_circle(x1, y1, r1, x2, y2, r2);

}

DEFINE_COLLISION(ShapeCircle, ShapeBox) {

	return false;	// TODO

}

DEFINE_COLLISION(ShapeCircle, ShapeTriangle) {

	return false;	// TODO

}

DEFINE_COLLISION(ShapeCircle, ShapeQuadrangle) {

	return false;	// TODO

}

DEFINE_COLLISION(ShapeCircle, ShapeEllipse) {

	return false;	// TODO

}

DEFINE_COLLISION(ShapeBox, ShapeBox) {

	GET_POSITIONS

	auto w1 = shape1.diagonal.x * shape1.scale.x;
	auto h1 = shape1.diagonal.y * shape1.scale.y;

	auto w2 = shape2.diagonal.x * shape2.scale.x;
	auto h2 = shape2.diagonal.y * shape2.scale.y;

	return collision_box_box(x1, y1, w1, h1, x2, y2, w2, h2);

}

DEFINE_COLLISION(ShapeBox, ShapeTriangle) {

	return false;	// TODO

}

DEFINE_COLLISION(ShapeBox, ShapeQuadrangle) {

	return false;	// TODO

}

DEFINE_COLLISION(ShapeBox, ShapeEllipse) {

	return false;	// TODO

}

DEFINE_COLLISION(ShapeTriangle, ShapeTriangle) {

	return false;	// TODO

}

DEFINE_COLLISION(ShapeTriangle, ShapeQuadrangle) {

	return false;	// TODO

}

DEFINE_COLLISION(ShapeTriangle, ShapeEllipse) {

	return false;	// TODO

}

DEFINE_COLLISION(ShapeQuadrangle, ShapeQuadrangle) {

	return false;	// TODO

}

DEFINE_COLLISION(ShapeQuadrangle, ShapeEllipse) {

	return false;	// TODO

}

DEFINE_COLLISION(ShapeEllipse, ShapeEllipse) {

	return false;	// TODO

}