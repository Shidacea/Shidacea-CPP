#include "RenderStates.h"

void setup_ruby_class_render_states(mrb_state* mrb, RClass* ruby_module) {

	// @@@ M_CLASS RenderStates
	// Class for applying render states to drawable objects
	MrbWrap::wrap_class_under<sf::RenderStates>(mrb, "RenderStates", ruby_module);

	// @@@ M_IM RenderStates initialize
	// @return [RenderStates]
	// Creates an empty render states object
	MrbWrap::wrap_constructor<sf::RenderStates>(mrb);

}