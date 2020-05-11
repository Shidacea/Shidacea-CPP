#pragma once

#include "Helper.h"

#include <SFML/Graphics.hpp>

#include <codecvt>
#include <locale>

sf::String convert_byte_to_utf8(const char* str);

void setup_ruby_class_text(mrb_state* mrb, RClass* ruby_module);