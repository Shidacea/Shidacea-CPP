#include "Collisions.h"

bool collision_point_point(float x1, float y1, float x2, float y2) {

	//! Usually, this routine will yield false

	if (EQUAL_OVERLAP) return (x1 == x2 && y1 == y2);
	else return false;

}

bool collision_point_circle(float x1, float y1, float x2, float y2, float r2) {

	//! Simple check whether the point is inside the circle radius

	auto dx = x1 - x2;
	auto dy = y1 - y2;

	if (dx * dx + dy * dy GREATER_THAN r2 * r2) return false;
	else return true;

}

bool collision_point_box(float x1, float y1, float x2, float y2, float w2, float h2) {

	//! If you do not understand this algorith, do not look any further
	//! This is one of the easy ones

	if (x1 LESS_THAN x2 - w2) return false;
	else if (y1 LESS_THAN y2 - h2) return false;
	else if (x2 + w2 LESS_THAN x1) return false;
	else if (y2 + h2 LESS_THAN y1) return false;
	else return true;
}

bool collision_line_line(float x1, float y1, float dx1, float dy1, float x2, float y2, float dx2, float dy2) {

	//! Determine difference vector between line starting points

	auto dx21 = x2 - x1;
	auto dy21 = y2 - y1;

	//! Cross-terms which are needed to calculate the line parameters at which the lines intersect
	//! These can be obtained by solving the equation system of two separating lines
	
	auto dx1_dy2 = dx1 * dy2;
	auto dx2_dy1 = dx2 * dy1;
	auto dx2_dy21 = dx2 * dy21;
	auto dx21_dy2 = dx21 * dy2;

	//! Parameter for the first line at which intersection happens
	//! The split into nominator and denominator avoids divisions
	//! Both parameters need to be between 0 and 1 for a collision
	//! An easy way to check this is to study nominator and denominator

	auto nominator_1 = dx2_dy21 - dx21_dy2;
	auto denominator_1 = dx2_dy1 - dx1_dy2;

	//! If nominator and denominator signs are different, the parameter is smaller than 0

	if (static_cast<bool>(nominator_1 LESS_THAN 0) != static_cast<bool>(denominator_1 LESS_THAN 0)) return false;
	else {

		//! First line parameter is positive, so check the other one

		auto dx21_y1 = dx21 * y1;
		auto x1_dy21 = x1 * dy21;

		auto nominator_2 = dx21_y1 - x1_dy21;
		auto denominator_2 = dx1_dy2 - dx2_dy1;

		if (static_cast<bool>(nominator_2 LESS_THAN 0) != static_cast<bool>(denominator_2 LESS_THAN 0)) return false;

		//! Check whether one of the line parameters is greater than 1
		//! This can again be done by comparing nominator and denominator
		//! Since the case of a negative parameter is already excluded, the absolute values are sufficient here

		else if (std::abs(denominator_1) LESS_THAN std::abs(nominator_1)) return false;
		else if (std::abs(denominator_2) LESS_THAN std::abs(nominator_2)) return false;

		//! Both line parameters are between 0 and 1, so a collision is definitely happening

		else return true;

	}

}

bool collision_circle_circle(float x1, float y1, float r1, float x2, float y2, float r2) {

	//! Simple generalization of point/circle

	auto dx = x1 - x2;
	auto dy = y1 - y2;

	auto combined_radius = r1 + r2;

	if (dx * dx + dy * dy GREATER_THAN combined_radius * combined_radius) return false;
	else return true;

}

bool collision_box_box(float x1, float y1, float w1, float h1, float x2, float y2, float w2, float h2) {

	//! Simple generalization of point/box

	if (x1 + w1 LESS_THAN x2 - w2) return false;
	else if (y1 + h1 LESS_THAN y2 - h2) return false;
	else if (x2 + w2 LESS_THAN x1 - w1) return false;
	else if (y2 + h2 LESS_THAN y1 - h1) return false;
	else return true;

}

bool collision_circle_box(float x1, float y1, float r1, float x2, float y2, float w2, float h2) {

	//! This algorithm makes use of the separating axis theorem (SAT)
	//! Essentially, the circle is projected onto both cardinal axes
	//! Then, the border points of the AABB are checked for intersection with the circle

	//! Projections of the circle onto the axes

	auto dxp = (x2 + w2 - x1);
	auto dyp = (y2 + h2 - y1);
	auto dxm = (x2 - w2 - x1);
	auto dym = (y2 - h2 - y1);

	//! Check for intersection of the circle projections with the AABB projections

	if (r1 LESS_THAN dxm) return false;
	else if (r1 LESS_THAN dym) return false;
	else if (dxp LESS_THAN -r1) return false;
	else if (dyp LESS_THAN -r1) return false;
	else {

		//! Squared values of the points

		auto r2 = r1 * r1;

		auto dxp2 = dxp * dxp;
		auto dxm2 = dxm * dxm;
		auto dyp2 = dyp * dyp;
		auto dym2 = dym * dym;

		//! Test collision of each border point with the circle
		//! This is effectively just another point/circle test

		if (r2 GREATER_THAN dxp2 + dyp2) return true;
		else if (r2 GREATER_THAN dxm2 + dyp2) return true;
		else if (r2 GREATER_THAN dxp2 + dym2) return true;
		else if (r2 GREATER_THAN dxm2 + dym2) return true;
		else return false;

	}

}

//! TODO: Assertions