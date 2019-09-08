#include "IntRect.h"

mrb_value ruby_intrect_init(mrb_state* mrb, mrb_value self) {

	mrb_int left = 0;
	mrb_int top = 0;
	mrb_int width = 0;
	mrb_int height = 0;

	mrb_get_args(mrb, "|iiii", &left, &top, &width, &height);

	MrbWrap::convert_to_object<MrbIntRect>(mrb, self, left, top, width, height);

	return self;
}

void setup_ruby_class_intrect(mrb_state* mrb) {

	auto ruby_intrect_class = MrbWrap::define_data_class(mrb, "IntRect");

	mrb_define_method(mrb, ruby_intrect_class, "initialize", ruby_intrect_init, MRB_ARGS_OPT(4));
	MrbWrap::define_default_copy_init<MrbIntRect>(mrb, ruby_intrect_class);

}