#pragma once

#include "Helper.h"

#include <SFML/Graphics.hpp>

void setup_ruby_class_coordinates(mrb_state* mrb, RClass* ruby_module);

static RClass* coordinates_ruby_module;