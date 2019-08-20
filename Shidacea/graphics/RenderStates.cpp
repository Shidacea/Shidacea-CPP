#include "RenderStates.h"

mrb_value ruby_render_states_init(mrb_state* mrb, mrb_value self) {

	auto render_states = MrbWrap::convert_to_object<sf::RenderStates>(mrb, self);

	return self;

}

void setup_ruby_class_render_states(mrb_state* mrb) {

	auto ruby_render_state_class = MrbWrap::define_data_class(mrb, "RenderStates");

	mrb_define_method(mrb, ruby_render_state_class, "initialize", ruby_render_states_init, MRB_ARGS_NONE());

}