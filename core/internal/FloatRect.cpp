#include "FloatRect.h"

void setup_ruby_class_floatrect(mrb_state* mrb, RClass* ruby_module) {

	auto ruby_floatrect_class = MrbWrap::define_data_class_under(mrb, "FloatRect", ruby_module);

	MrbWrap::wrap_class_under<sf::FloatRect>(mrb, "FloatRect", ruby_module);

	MrbWrap::wrap_constructor<sf::FloatRect, MRBW_RAT_OPT<float, 0>, MRBW_RAT_OPT<float, 0>, MRBW_RAT_OPT<float, 0>, MRBW_RAT_OPT<float, 0>>(mrb);
	MrbWrap::define_default_copy_init<sf::FloatRect>(mrb);

	MrbWrap::wrap_getter<sf::FloatRect, &sf::FloatRect::width>(mrb, "width");
	MrbWrap::wrap_setter<sf::FloatRect, &sf::FloatRect::width, float>(mrb, "width=");

	MrbWrap::wrap_getter<sf::FloatRect, &sf::FloatRect::height>(mrb, "height");
	MrbWrap::wrap_setter<sf::FloatRect, &sf::FloatRect::height, float>(mrb, "height=");

	MrbWrap::wrap_getter<sf::FloatRect, &sf::FloatRect::left>(mrb, "left");
	MrbWrap::wrap_setter<sf::FloatRect, &sf::FloatRect::left, float>(mrb, "left=");

	MrbWrap::wrap_getter<sf::FloatRect, &sf::FloatRect::top>(mrb, "top");
	MrbWrap::wrap_setter<sf::FloatRect, &sf::FloatRect::top, float>(mrb, "top=");

}