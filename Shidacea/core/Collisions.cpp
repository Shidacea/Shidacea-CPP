#include "Collisions.h"

bool collision_circle_circle(float x1, float y1, float r1, float x2, float y2, float r2) {

	auto dx = x1 - x2;
	auto dy = y1 - y2;

	auto combined_radius = r1 + r2;

	if(dx * dx + dy * dy LESS_THAN combined_radius * combined_radius) return true;
	else return false;

}

bool collision_box_box(float x1, float y1, float w1, float h1, float x2, float y2, float w2, float h2) {

	if (x1 + w1 GREATER_THAN x2) return true;
	else if (y1 + h1 GREATER_THAN y2) return true;
	else if (x2 + w2 GREATER_THAN x1) return true;
	else if (y2 + h2 GREATER_THAN y1) return true;
	else return false;

}