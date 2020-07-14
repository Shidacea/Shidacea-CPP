#include "IntRect.h"

void setup_ruby_class_intrect(mrb_state* mrb, RClass* ruby_module) {

	// @@@ M_CLASS IntRect
	// Simple rectangle consisting of integer valued boundaries
	MrbWrap::wrap_class_under<sf::IntRect>(mrb, "IntRect", ruby_module);

	// @@@ M_IM IntRect initialize left=0 top=0 width=0 height=0
	// @return [IntRect]
	// @param left [Integer]
	// @param top [Integer]
	// @param width [Integer]
	// @param height [Integer]
	// Creates a rectangle with given left top point, width and height
	MrbWrap::wrap_constructor<sf::IntRect, MRBW_OPT<int, 0>, MRBW_OPT<int, 0>, MRBW_OPT<int, 0>, MRBW_OPT<int, 0>>(mrb);
	MrbWrap::define_default_copy_init<sf::IntRect>(mrb);

	// @@@ M_ATTR IntRect width Integer rw
	// Width of the rectangle
	MrbWrap::wrap_getter<sf::IntRect, &sf::IntRect::width>(mrb, "width");
	MrbWrap::wrap_setter<sf::IntRect, &sf::IntRect::width, int>(mrb, "width=");

	// @@@ M_ATTR IntRect height Integer rw
	// Height of the rectangle
	MrbWrap::wrap_getter<sf::IntRect, &sf::IntRect::height>(mrb, "height");
	MrbWrap::wrap_setter<sf::IntRect, &sf::IntRect::height, int>(mrb, "height=");

	// @@@ M_ATTR IntRect left Integer rw
	// x coordinate of the left rectangle side
	MrbWrap::wrap_getter<sf::IntRect, &sf::IntRect::left>(mrb, "left");
	MrbWrap::wrap_setter<sf::IntRect, &sf::IntRect::left, int>(mrb, "left=");

	// @@@ M_ATTR IntRect top Integer rw
	// y coordinate of the upper rectangle side
	MrbWrap::wrap_getter<sf::IntRect, &sf::IntRect::top>(mrb, "top");
	MrbWrap::wrap_setter<sf::IntRect, &sf::IntRect::top, int>(mrb, "top=");

}