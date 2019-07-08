#pragma once

//! The following defines allow for simple changes of the collision routines
//! This is especially useful if you want to include border cases

#define LESS_THAN <
#define GREATER_THAN >

bool collision_circle_circle(float x1, float y1, float r1, float x2, float y2, float r2);
bool collision_box_box(float x1, float y1, float w1, float h1, float x2, float y2, float w2, float h2);