#include "View.h"

void setup_ruby_class_view(mrb_state* mrb, RClass* ruby_module) {

	auto ruby_view_class = MrbWrap::define_data_class_under(mrb, "View", ruby_module);

	MrbWrap::define_mruby_function(mrb, ruby_view_class, "initialize", MRUBY_FUNC{

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

	});

	MrbWrap::wrap_function<MRBW_FUNC(sf::View, sf::View::setViewport), sf::FloatRect>(mrb, ruby_view_class, "set_viewport");

}