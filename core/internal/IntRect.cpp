#include "IntRect.h"

void setup_ruby_class_intrect(mrb_state* mrb, RClass* ruby_module) {

	auto ruby_intrect_class = MrbWrap::define_data_class_under(mrb, "IntRect", ruby_module);

	MrbWrap::wrap_constructor<MrbIntRect, MRBW_OPT<int, 0>, MRBW_OPT<int, 0>, MRBW_OPT<int, 0>, MRBW_OPT<int, 0>>(mrb, ruby_intrect_class);
	MrbWrap::define_default_copy_init<MrbIntRect>(mrb, ruby_intrect_class);

	MrbWrap::wrap_getter<MRBW_FUNC(MrbIntRect, MrbIntRect::width)>(mrb, ruby_intrect_class, "width");
	MrbWrap::wrap_setter<MRBW_FUNC(MrbIntRect, MrbIntRect::width), mrb_int>(mrb, ruby_intrect_class, "width=");

	MrbWrap::wrap_getter<MRBW_FUNC(MrbIntRect, MrbIntRect::height)>(mrb, ruby_intrect_class, "height");
	MrbWrap::wrap_setter<MRBW_FUNC(MrbIntRect, MrbIntRect::height), mrb_int>(mrb, ruby_intrect_class, "height=");

	MrbWrap::wrap_getter<MRBW_FUNC(MrbIntRect, MrbIntRect::left)>(mrb, ruby_intrect_class, "left");
	MrbWrap::wrap_setter<MRBW_FUNC(MrbIntRect, MrbIntRect::left), mrb_int>(mrb, ruby_intrect_class, "left=");

	MrbWrap::wrap_getter<MRBW_FUNC(MrbIntRect, MrbIntRect::top)>(mrb, ruby_intrect_class, "top");
	MrbWrap::wrap_setter<MRBW_FUNC(MrbIntRect, MrbIntRect::top), mrb_int>(mrb, ruby_intrect_class, "top=");

}