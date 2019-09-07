#pragma once

//! TODO: Implement more than a dummy constructor

#include "Helper.h"
#include "ResourceManager.h"

#include <SFML/Graphics.hpp>

mrb_value ruby_render_states_init(mrb_state* mrb, mrb_value self);

void setup_ruby_class_render_states(mrb_state* mrb);