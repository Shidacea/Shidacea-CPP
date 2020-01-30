#include "IntRect.h"

void setup_ruby_class_intrect(mrb_state* mrb, RClass* ruby_module) {

	auto ruby_intrect_class = MrbWrap::define_data_class_under(mrb, "IntRect", ruby_module);

	MrbWrap::wrap_constructor<MrbIntRect, MRBW_OPT<int, 0>, MRBW_OPT<int, 0>, MRBW_OPT<int, 0>, MRBW_OPT<int, 0>>(mrb, ruby_intrect_class);
	MrbWrap::define_default_copy_init<MrbIntRect>(mrb, ruby_intrect_class);

}