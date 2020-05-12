#pragma once

#include "MrbWrap.h"

#include <SFML/Graphics.hpp>

sf::String convert_byte_to_utf8(const char* str);

void setup_ruby_class_text(mrb_state* mrb, RClass* ruby_module);