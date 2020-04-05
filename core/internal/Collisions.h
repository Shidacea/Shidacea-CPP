#pragma once

#include <cmath>

//! Here resides the actual mathematical core of the collision routines
//! These are completely decoupled from any Ruby or SFML magic

//! The following defines allow for simple changes of the collision routines
//! This is especially useful if you want to include border cases
//! The algorithms are usually checking non-collision-criteria, so an <= means rejection at direct contact
//! Reasonable combinations are <=,>=,<,>,false and <,>,<=,>=,true

#define LESS_THAN <=
#define GREATER_THAN >=
#define LESS_THAN_ACCEPT <
#define GREATER_THAN_ACCEPT >
#define EQUAL_OVERLAP false

template <class T> constexpr T constexpr_abs(T value) {

	return (value < 0.0 ? -value : value);

}

constexpr bool collision_point_point(float x1, float y1, float x2, float y2) {

	//! Usually, this routine will yield false

	if (EQUAL_OVERLAP) return (x1 == x2 && y1 == y2);

	return false;

}

constexpr bool collision_point_line(float x1, float y1, float x2, float y2, float dx2, float dy2) {

	//! If equal overlap is not set, this is always false

	if (!EQUAL_OVERLAP) return false;

	//! First, check whether the point is behind one of the line segment points
	//! It is not necessary to check whether the point is actually on the line yet
	//! Effectively, this is the equation to check if the line parameter is smaller than 0
	//! The same test could be done with dy12 and dx2, but if they are not equal, a collision is excluded

	auto dx12 = x1 - x2;

	if (static_cast<bool>(dx12 LESS_THAN 0.0) != static_cast<bool>(dy2 LESS_THAN 0.0)) return false;

	//! The next check tests whether the line parameter is greater than 1
	//! Checking the absolute values is sufficient, as the signs of dx12 and dy2 is now proven equal

	if (constexpr_abs(dx12) LESS_THAN constexpr_abs(dy2)) return false;

	auto dy12 = y1 - y2;

	//! If the following equation is not satisfied, the point has a normal component to the line
	//! This formula can be obtained via two ways
	//! Firstly, the line parameter of the point can be obtained from a oversatisfied equation system
	//! Also the cross product of the distance from point to start point with the line direction can be taken
	//! The latter one should be zero if the point is on the infinitely extended line
	//! If it isn't, the following statement is true and the function returns false

	if (dx12 * dy2 != dy12 * dx2) return false;
	return true;

}

constexpr bool collision_point_circle(float x1, float y1, float x2, float y2, float r2) {

	//! Simple check whether the point is inside the circle radius

	auto dx = x1 - x2;
	auto dy = y1 - y2;

	if (dx * dx + dy * dy GREATER_THAN r2 * r2) return false;
	
	return true;

}

constexpr bool collision_point_box(float x1, float y1, float x2, float y2, float w2, float h2) {

	//! Literally the definition of an AABB

	if (x1 LESS_THAN x2 - w2) return false;
	if (y1 LESS_THAN y2 - h2) return false;
	if (x2 + w2 LESS_THAN x1) return false;
	if (y2 + h2 LESS_THAN y1) return false;
	
	return true;
}

constexpr bool collision_line_line(float x1, float y1, float dx1, float dy1, float x2, float y2, float dx2, float dy2) {

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

	if (static_cast<bool>(nominator_1 LESS_THAN 0.0) != static_cast<bool>(denominator_1 LESS_THAN 0.0)) return false;

	//! First line parameter is positive, so check the other one

	auto dx21_y1 = dx21 * y1;
	auto x1_dy21 = x1 * dy21;

	auto nominator_2 = dx21_y1 - x1_dy21;
	auto denominator_2 = dx1_dy2 - dx2_dy1;

	if (static_cast<bool>(nominator_2 LESS_THAN 0.0) != static_cast<bool>(denominator_2 LESS_THAN 0.0)) return false;

	//! Check whether one of the line parameters is greater than 1
	//! This can again be done by comparing nominator and denominator
	//! Since the case of a negative parameter is already excluded, the absolute values are sufficient here

	if (constexpr_abs(denominator_1) LESS_THAN constexpr_abs(nominator_1)) return false;
	if (constexpr_abs(denominator_2) LESS_THAN constexpr_abs(nominator_2)) return false;

	//! Both line parameters are between 0 and 1, so a collision is definitely happening

	return true;

}

constexpr bool collision_line_box(float x1, float y1, float dx1, float dy1, float x2, float y2, float w2, float h2) {

	//! First check whether any end point lies inside the box

	if (collision_point_box(x1, y1, x2, y2, w2, h2)) return true;
	if (collision_point_box(x1 + dx1, y1 + dy1, x2, y2, w2, h2)) return true;
	
	//! If this is not the case, check each axis for an intersection inside the rectangle

	//! These value can all be calculated in beforehand, since 3/4 of them will be already used in the first check
	//! This will make the code much less complicated

	//! Nominators of the line parameter

	auto nominator_x_neg = x2 - w2 - x1;
	auto nominator_x_pos = x2 + w2 - x1;
	auto nominator_y_neg = y2 - h2 - y1;
	auto nominator_y_pos = y2 + h2 - y1;

	//! These terms can be obtained by inserting the line parameter for one coordinate into the intersection equation
	//! This is only a mathematical trick to avoid divisions here

	auto nom_x_neg_dy = nominator_x_neg * dy1;
	auto nom_x_pos_dy = nominator_x_pos * dy1;
	auto nom_y_neg_dx = nominator_y_neg * dx1;
	auto nom_y_pos_dx = nominator_y_pos * dx1;

	//! Check whether the y coordinate of the intersection point with the left AABB side is actually inside the AABB
	//! The following checks will repeat this procedure for the other sides

	if ((nom_x_neg_dy GREATER_THAN_ACCEPT nom_y_neg_dx) && (nom_x_neg_dy LESS_THAN_ACCEPT nom_y_pos_dx)) {

		//! The case of a vanishing dx1 should not occur, but even then, the next check will rule it out definitely
		//! Here, the line parameter of the intersection point will be checked for its sign
		//! If it is smaller than 0, the line segment does not touch the AABB at this side
		//! This can again be checked by comparing the signs of the nominator and the denominator
		//! We still need to check the other sides, however

		if (static_cast<bool>(nominator_x_neg LESS_THAN 0.0) == static_cast<bool>(dx1 LESS_THAN 0.0)) {

			//! Check whether the line parameter is smaller than 1
			//! If it is, a collision definitely occurs here and we can finally return a value

			if (constexpr_abs(nominator_x_neg) LESS_THAN_ACCEPT constexpr_abs(dx1)) return true;

		}

	}

	//! Check right side

	if ((nom_x_pos_dy GREATER_THAN_ACCEPT nom_y_neg_dx) && (nom_x_pos_dy LESS_THAN_ACCEPT nom_y_pos_dx)) {

		//! The line got shifted in its coordinates, so a new line parameter check is necessary

		if (static_cast<bool>(nominator_x_pos LESS_THAN 0.0) == static_cast<bool>(dx1 LESS_THAN 0.0)) {

			if (constexpr_abs(nominator_x_pos) LESS_THAN_ACCEPT constexpr_abs(dx1)) return true;

		}

	}

	//! Check bottom side

	if ((nom_y_neg_dx GREATER_THAN_ACCEPT nom_x_neg_dy) && (nom_y_neg_dx LESS_THAN_ACCEPT nom_x_pos_dy)) {

		if (static_cast<bool>(nominator_y_neg LESS_THAN 0.0) == static_cast<bool>(dy1 LESS_THAN 0.0)) {

			if (constexpr_abs(nominator_y_neg) LESS_THAN_ACCEPT constexpr_abs(dy1)) return true;

		}

	}

	//! Check top side

	if ((nom_y_pos_dx GREATER_THAN_ACCEPT nom_x_neg_dy) && (nom_y_pos_dx LESS_THAN_ACCEPT nom_x_pos_dy)) {

		if (static_cast<bool>(nominator_y_pos LESS_THAN 0.0) == static_cast<bool>(dy1 LESS_THAN 0.0)) {

			if (constexpr_abs(nominator_y_pos) LESS_THAN_ACCEPT constexpr_abs(dy1)) return true;

		}

	}

	return false;

}

constexpr bool collision_circle_circle(float x1, float y1, float r1, float x2, float y2, float r2) {

	//! Simple generalization of point/circle

	auto dx = x1 - x2;
	auto dy = y1 - y2;

	auto combined_radius = r1 + r2;

	if (dx * dx + dy * dy GREATER_THAN combined_radius * combined_radius) return false;

	return true;

}

constexpr bool collision_box_box(float x1, float y1, float w1, float h1, float x2, float y2, float w2, float h2) {

	//! Simple generalization of point/box

	if (x1 + w1 LESS_THAN x2 - w2) return false;
	if (y1 + h1 LESS_THAN y2 - h2) return false;
	if (x2 + w2 LESS_THAN x1 - w1) return false;
	if (y2 + h2 LESS_THAN y1 - h1) return false;

	return true;

}

constexpr bool collision_circle_box(float x1, float y1, float r1, float x2, float y2, float w2, float h2) {

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
	if (r1 LESS_THAN dym) return false;
	if (dxp LESS_THAN - r1) return false;
	if (dyp LESS_THAN - r1) return false;

	//! Squared values of the points

	auto r2 = r1 * r1;

	auto dxp2 = dxp * dxp;
	auto dxm2 = dxm * dxm;
	auto dyp2 = dyp * dyp;
	auto dym2 = dym * dym;

	//! Test collision of each border point with the circle
	//! This is effectively just another point/circle test

	if (r2 GREATER_THAN dxp2 + dyp2) return true;
	if (r2 GREATER_THAN dxm2 + dyp2) return true;
	if (r2 GREATER_THAN dxp2 + dym2) return true;
	if (r2 GREATER_THAN dxm2 + dym2) return true;

	//! The last possibility is that the circle is inside the box, which can be checked quickly

	return collision_point_box(x1, y1, x2, y2, w2, h2);

}

//! Compile time assertions to check some test cases
//! Please submit a bug report if one of these fails

static_assert(false == collision_point_point(1.0f, 2.0f,     3.0f, 4.0f));
static_assert(EQUAL_OVERLAP == collision_point_point(1.0f, 9.0f,     1.0f, 9.0f));

static_assert(true == collision_point_circle(2.0f, 3.0f,     4.0f, 5.0f, 3.0f));

static_assert(true == collision_point_box(-3.0f, -5.0f,     3.0f, 2.0f, 10.0f, 9.0f));

static_assert(true == collision_line_box(3.0f, 2.0f, 8.0f, 11.0f,     5.0f, 6.0f, 5.0f, 5.0f));
static_assert(false == collision_line_box(11.0f, 0.0f, 11.0f, 13.0f,     5.0f, 6.0f, 5.0f, 5.0f));

static_assert(true == collision_box_box(1.0f, 2.0f, 3.0f, 4.0f,     4.5f, 7.5f, 2.0f, 2.0f));
static_assert(false == collision_box_box(1.0f, 2.0f, 3.0f, 4.0f,     4.5f, 7.5f, 1.4f, 1.4f));

static_assert(true == collision_circle_box(1.0f, -3.0f, 4.0f,     0.0f, 0.0f, 5.0f, 4.0f));
static_assert(false == collision_circle_box(1.0f, -3.0f, 4.0f,     0.0f, 0.0f, 5.0f, 2.0f));