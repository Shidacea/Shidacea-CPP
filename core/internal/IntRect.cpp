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

mrb_value ruby_intrect_inspect(mrb_state* mrb, mrb_value self) {

	auto content = MrbWrap::convert_from_object<MrbIntRect>(mrb, self);

	char buffer[64];
	snprintf(buffer, 64, "(%u %u) > (%u %u)", content->left, content->top, content->width, content->height);

	return mrb_str_new_cstr(mrb, buffer);

}

void setup_ruby_class_intrect(mrb_state* mrb, RClass* ruby_module) {

	auto ruby_intrect_class = MrbWrap::define_data_class_under(mrb, "IntRect", ruby_module);

	mrb_define_method(mrb, ruby_intrect_class, "initialize", ruby_intrect_init, MRB_ARGS_OPT(4));
	MrbWrap::define_default_copy_init<MrbIntRect>(mrb, ruby_intrect_class);

	mrb_define_method(mrb, ruby_intrect_class, "inspect", ruby_intrect_inspect, MRB_ARGS_NONE());

}