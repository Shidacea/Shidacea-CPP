#pragma once

#include "Helper.h"

#include <SFML/Graphics.hpp>

mrb_value ruby_intrect_init(mrb_state* mrb, mrb_value self);

void setup_ruby_class_intrect(mrb_state* mrb);