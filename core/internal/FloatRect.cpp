#include "FloatRect.h"

void setup_ruby_class_floatrect(mrb_state* mrb, RClass* ruby_module) {

	auto ruby_floatrect_class = MrbWrap::define_data_class_under(mrb, "FloatRect", ruby_module);

	MrbWrap::wrap_constructor<sf::FloatRect, MRBW_RAT_OPT<float, 0>, MRBW_RAT_OPT<float, 0>, MRBW_RAT_OPT<float, 0>, MRBW_RAT_OPT<float, 0>>(mrb, ruby_floatrect_class);
	MrbWrap::define_default_copy_init<sf::FloatRect>(mrb, ruby_floatrect_class);

	MrbWrap::wrap_getter<MRBW_FUNC(sf::FloatRect, sf::FloatRect::width)>(mrb, ruby_floatrect_class, "width");
	MrbWrap::wrap_setter<MRBW_FUNC(sf::FloatRect, sf::FloatRect::width), float>(mrb, ruby_floatrect_class, "width=");

	MrbWrap::wrap_getter<MRBW_FUNC(sf::FloatRect, sf::FloatRect::height)>(mrb, ruby_floatrect_class, "height");
	MrbWrap::wrap_setter<MRBW_FUNC(sf::FloatRect, sf::FloatRect::height), float>(mrb, ruby_floatrect_class, "height=");

	MrbWrap::wrap_getter<MRBW_FUNC(sf::FloatRect, sf::FloatRect::left)>(mrb, ruby_floatrect_class, "left");
	MrbWrap::wrap_setter<MRBW_FUNC(sf::FloatRect, sf::FloatRect::left), float>(mrb, ruby_floatrect_class, "left=");

	MrbWrap::wrap_getter<MRBW_FUNC(sf::FloatRect, sf::FloatRect::top)>(mrb, ruby_floatrect_class, "top");
	MrbWrap::wrap_setter<MRBW_FUNC(sf::FloatRect, sf::FloatRect::top), float>(mrb, ruby_floatrect_class, "top=");

}