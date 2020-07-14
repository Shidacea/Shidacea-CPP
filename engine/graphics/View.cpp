#include "View.h"

void setup_ruby_class_view(mrb_state* mrb, RClass* ruby_module) {

	// @@@ MRBWRAPDOC_CLASS View
	// A view class capable of giving a transformed view of drawable contents
	MrbWrap::wrap_class_under<sf::View>(mrb, "View", ruby_module);
	auto ruby_view_class = MrbWrap::get_class_info_ptr<sf::View>();

	// @@@ MRBWRAPDOC_IM View initialize arg_1=nil arg_2=nil
	// @return [View]
	// @param arg_1 [FloatRect|Coordinates|nil]
	// @param arg_2 [Coordinates|nil]
	// Creates a view object with either a rectangle or a center and a size given as arguments
	MrbWrap::define_member_function(mrb, ruby_view_class, "initialize", MRUBY_FUNC {

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

	}, MRB_ARGS_OPT(2));

	// @@@ MRBWRAPDOC_IM View set_viewport rectangle
	// @return [nil]
	// @param rectangle FloatRect
	// Sets the rectangle of the view to the given rectangle
	MrbWrap::wrap_member_function<sf::View, &sf::View::setViewport, sf::FloatRect>(mrb, "set_viewport");

}