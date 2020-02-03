#include "IntRect.h"

void setup_ruby_class_intrect(mrb_state* mrb, RClass* ruby_module) {

	auto ruby_intrect_class = MrbWrap::define_data_class_under(mrb, "IntRect", ruby_module);

	MrbWrap::wrap_constructor<sf::IntRect, MRBW_OPT<int, 0>, MRBW_OPT<int, 0>, MRBW_OPT<int, 0>, MRBW_OPT<int, 0>>(mrb, ruby_intrect_class);
	MrbWrap::define_default_copy_init<sf::IntRect>(mrb, ruby_intrect_class);

	MrbWrap::wrap_getter<MRBW_FUNC(sf::IntRect, sf::IntRect::width)>(mrb, ruby_intrect_class, "width");
	MrbWrap::wrap_setter<MRBW_FUNC(sf::IntRect, sf::IntRect::width), int>(mrb, ruby_intrect_class, "width=");

	MrbWrap::wrap_getter<MRBW_FUNC(sf::IntRect, sf::IntRect::height)>(mrb, ruby_intrect_class, "height");
	MrbWrap::wrap_setter<MRBW_FUNC(sf::IntRect, sf::IntRect::height), int>(mrb, ruby_intrect_class, "height=");

	MrbWrap::wrap_getter<MRBW_FUNC(sf::IntRect, sf::IntRect::left)>(mrb, ruby_intrect_class, "left");
	MrbWrap::wrap_setter<MRBW_FUNC(sf::IntRect, sf::IntRect::left), int>(mrb, ruby_intrect_class, "left=");

	MrbWrap::wrap_getter<MRBW_FUNC(sf::IntRect, sf::IntRect::top)>(mrb, ruby_intrect_class, "top");
	MrbWrap::wrap_setter<MRBW_FUNC(sf::IntRect, sf::IntRect::top), int>(mrb, ruby_intrect_class, "top=");

}