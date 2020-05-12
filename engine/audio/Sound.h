#pragma once

#include "MrbWrap.h"

#include <SFML/Audio.hpp>

void setup_ruby_class_sound(mrb_state* mrb, RClass* ruby_module);
