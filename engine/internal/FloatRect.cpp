#include "FloatRect.h"

void setup_ruby_class_floatrect(mrb_state* mrb, RClass* ruby_module) {

	// @@@ M_CLASS FloatRect
	// Simple rectangle consisting of float valued boundaries
	MrbWrap::wrap_class_under<sf::FloatRect>(mrb, "FloatRect", ruby_module);

	// @@@ M_IM FloatRect initialize left=0.0 top=0.0 width=0.0 height=0.0
	// @return [FloatRect]
	// @param left [Float]
	// @param top [Float]
	// @param width [Float]
	// @param height [Float]
	// Creates a rectangle with given left top point, width and height
	MrbWrap::wrap_constructor<sf::FloatRect, MRBW_RAT_OPT<float, 0>, MRBW_RAT_OPT<float, 0>, MRBW_RAT_OPT<float, 0>, MRBW_RAT_OPT<float, 0>>(mrb);
	MrbWrap::define_default_copy_init<sf::FloatRect>(mrb);

	// @@@ M_ATTR FloatRect width Float rw
	// Width of the rectangle
	MrbWrap::wrap_getter<sf::FloatRect, &sf::FloatRect::width>(mrb, "width");
	MrbWrap::wrap_setter<sf::FloatRect, &sf::FloatRect::width, float>(mrb, "width=");

	// @@@ M_ATTR FloatRect height Float rw
	// Height of the rectangle
	MrbWrap::wrap_getter<sf::FloatRect, &sf::FloatRect::height>(mrb, "height");
	MrbWrap::wrap_setter<sf::FloatRect, &sf::FloatRect::height, float>(mrb, "height=");

	// @@@ M_ATTR FloatRect left Float rw
	// x coordinate of the left rectangle side
	MrbWrap::wrap_getter<sf::FloatRect, &sf::FloatRect::left>(mrb, "left");
	MrbWrap::wrap_setter<sf::FloatRect, &sf::FloatRect::left, float>(mrb, "left=");

	// @@@ M_ATTR FloatRect top Float rw
	// y coordinate of the upper rectangle side
	MrbWrap::wrap_getter<sf::FloatRect, &sf::FloatRect::top>(mrb, "top");
	MrbWrap::wrap_setter<sf::FloatRect, &sf::FloatRect::top, float>(mrb, "top=");

}