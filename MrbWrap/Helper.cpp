#include "Helper.h"

RClass* MrbWrap::define_data_class(mrb_state* mrb, const char* name, RClass* super_class) {

	if (!super_class) super_class = mrb->object_class;

	auto ruby_class = mrb_define_class(mrb, name, super_class);
	MRB_SET_INSTANCE_TT(ruby_class, MRB_TT_DATA);

	return ruby_class;

}

RClass* MrbWrap::define_data_class_under(mrb_state* mrb, const char* name, RClass* ruby_module, RClass* super_class) {

	if (!super_class) super_class = mrb->object_class;

	auto ruby_class = mrb_define_class_under(mrb, ruby_module, name, super_class);
	MRB_SET_INSTANCE_TT(ruby_class, MRB_TT_DATA);

	return ruby_class;

}

void MrbWrap::define_member_function(mrb_state* mrb, RClass* ruby_class, const char* name, mrb_value(*func)(mrb_state* mrb, mrb_value self) noexcept, mrb_aspec aspec) {

	mrb_define_method(mrb, ruby_class, name, func, aspec);

}

void MrbWrap::define_module_function(mrb_state* mrb, RClass* ruby_module, const char* name, mrb_value(*func)(mrb_state* mrb, mrb_value self) noexcept, mrb_aspec aspec) {

	mrb_define_module_function(mrb, ruby_module, name, func, aspec);

}