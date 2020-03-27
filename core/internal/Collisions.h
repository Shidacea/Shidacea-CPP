#pragma once

//! Here resides the actual mathematical core of the collision routines
//! These are completely decoupled from any Ruby or SFML magic

//! The following defines allow for simple changes of the collision routines
//! This is especially useful if you want to include border cases
//! The algorithms are usually checking non-collision-criteria, so an <= means rejection at direct contact
//! Reasonable combinations are <=,>=,false and <,>,true

#define LESS_THAN <=
#define GREATER_THAN >=
#define EQUAL_OVERLAP false

bool collision_point_point(float x1, float y1, float x2, float y2);
bool collision_point_circle(float x1, float y1, float x2, float y2, float r2);
bool collision_point_box(float x1, float y1, float x2, float y2, float w2, float h2);
bool collision_circle_circle(float x1, float y1, float r1, float x2, float y2, float r2);
bool collision_box_box(float x1, float y1, float w1, float h1, float x2, float y2, float w2, float h2);
bool collision_circle_box(float x1, float y1, float r1, float x2, float y2, float w2, float h2);