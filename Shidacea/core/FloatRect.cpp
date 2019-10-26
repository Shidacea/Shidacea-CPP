#include "FloatRect.h"

mrb_value ruby_floatrect_init(mrb_state* mrb, mrb_value self) {

	mrb_float left = 0.0;
	mrb_float top = 0.0;
	mrb_float width = 0.0;
	mrb_float height = 0.0;

	mrb_get_args(mrb, "|ffff", &left, &top, &width, &height);

	MrbWrap::convert_to_object<sf::FloatRect>(mrb, self, left, top, width, height);

	return self;
}

void setup_ruby_class_floatrect(mrb_state* mrb) {

	auto ruby_floatrect_class = MrbWrap::define_data_class(mrb, "FloatRect");

	mrb_define_method(mrb, ruby_floatrect_class, "initialize", ruby_floatrect_init, MRB_ARGS_OPT(4));
	MrbWrap::define_default_copy_init<sf::FloatRect>(mrb, ruby_floatrect_class);

}