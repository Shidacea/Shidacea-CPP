#include "Collisions.h"

bool collision_point_point(float x1, float y1, float x2, float y2) {

	if (EQUAL_OVERLAP) return (x1 == x2 && y1 == y2);
	else return false;

}

bool collision_circle_circle(float x1, float y1, float r1, float x2, float y2, float r2) {

	auto dx = x1 - x2;
	auto dy = y1 - y2;

	auto combined_radius = r1 + r2;

	if(dx * dx + dy * dy GREATER_THAN combined_radius * combined_radius) return false;
	else return true;

}

bool collision_box_box(float x1, float y1, float w1, float h1, float x2, float y2, float w2, float h2) {

	if (x1 + w1 LESS_THAN x2 - w2) return false;
	else if (y1 + h1 LESS_THAN y2 - h2) return false;
	else if (x2 + w2 LESS_THAN x1 - w1) return false;
	else if (y2 + h2 LESS_THAN y1 - h1) return false;
	else return true;

}

bool collision_circle_box(float x1, float y1, float r1, float x2, float y2, float w2, float h2) {

	auto dxp = (x2 + w2 - x1);
	auto dyp = (y2 + h2 - y1);
	auto dxm = (x2 - w2 - x1);
	auto dym = (y2 - h2 - y1);

	if (r1 LESS_THAN dxm) return false;
	else if (r1 LESS_THAN dym) return false;
	else if (dxp LESS_THAN -r1) return false;
	else if (dyp LESS_THAN -r1) return false;
	else {

		auto r2 = r1 * r1;

		auto dxp2 = dxp * dxp;
		auto dxm2 = dxm * dxm;
		auto dyp2 = dyp * dyp;
		auto dym2 = dym * dym;

		if (r2 GREATER_THAN dxp2 + dyp2) return true;
		else if (r2 GREATER_THAN dxm2 + dyp2) return true;
		else if (r2 GREATER_THAN dxp2 + dym2) return true;
		else if (r2 GREATER_THAN dxm2 + dym2) return true;
		else return false;

	}

}