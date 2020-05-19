#include "DrawShape.h"

void setup_ruby_class_draw_shape(mrb_state* mrb, RClass* ruby_module) {

	MrbWrap::wrap_class_under<sf::RectangleShape>(mrb, "DrawShapeRectangle", ruby_module);

	MrbWrap::wrap_constructor<sf::RectangleShape>(mrb);

	MrbWrap::define_member_function(mrb, MrbWrap::get_class_info_ptr<sf::RectangleShape>(), "mimick", MRUBY_FUNC {

		auto args = MrbWrap::get_converted_args<ShapeBox>(mrb);
		auto box = std::get<0>(args);

		auto rectangle = MrbWrap::convert_from_object<sf::RectangleShape>(mrb, self);

		rectangle->setSize(box.size);
		rectangle->setPosition(box.getPosition());
		rectangle->setScale(box.getScale());
		rectangle->setOrigin(box.getOrigin());

		return mrb_nil_value();

	}, MRB_ARGS_REQ(1));

}