#include "RenderStates.h"

void setup_ruby_class_render_states(mrb_state* mrb, RClass* ruby_module) {

	MrbWrap::wrap_class_under<sf::RenderStates>(mrb, "RenderStates", ruby_module);

	MrbWrap::wrap_constructor<sf::RenderStates>(mrb);

}