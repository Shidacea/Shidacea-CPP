#include "View.h"

mrb_value ruby_view_init(mrb_state* mrb, mrb_value self) {

	mrb_value first_arg = mrb_nil_value();
	mrb_value second_arg = mrb_nil_value();

	mrb_get_args(mrb, "|oo", &first_arg, &second_arg);

	if (!mrb_nil_p(second_arg)) {

		auto center = MrbWrap::convert_from_object<sf::Vector2f>(mrb, first_arg);
		auto size = MrbWrap::convert_from_object<sf::Vector2f>(mrb, second_arg);

		MrbWrap::convert_to_object<sf::View>(mrb, self, *center, *size);

	} else if (!mrb_nil_p(first_arg)) {

		auto rect = MrbWrap::convert_from_object<sf::FloatRect>(mrb, first_arg);

		MrbWrap::convert_to_object<sf::View>(mrb, self, *rect);

	} else {

		MrbWrap::convert_to_object<sf::View>(mrb, self);

	}

	return self;

}

mrb_value ruby_view_set_viewport(mrb_state* mrb, mrb_value self) {

	mrb_value ruby_viewport;

	mrb_get_args(mrb, "o", &ruby_viewport);

	auto viewport = MrbWrap::convert_from_object<sf::FloatRect>(mrb, ruby_viewport);
	auto view = MrbWrap::convert_from_object<sf::View>(mrb, self);

	view->setViewport(*viewport);

	return mrb_nil_value();

}

void setup_ruby_class_view(mrb_state* mrb, RClass* ruby_module) {

	auto ruby_view_class = MrbWrap::define_data_class_under(mrb, "View", ruby_module);

	mrb_define_method(mrb, ruby_view_class, "initialize", ruby_view_init, MRB_ARGS_ARG(0, 2));
	mrb_define_method(mrb, ruby_view_class, "set_viewport", ruby_view_set_viewport, MRB_ARGS_REQ(1));

}