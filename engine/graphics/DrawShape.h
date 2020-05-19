#pragma once

#include "MrbWrap.h"
#include "Shape.h"

#include <SFML/Graphics.hpp>

void setup_ruby_class_draw_shape(mrb_state* mrb, RClass* ruby_module);