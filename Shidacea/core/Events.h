#pragma once

#include "Helper.h"

#include <SFML/Graphics.hpp>

#define REGISTER_KEY(mrb, module_key, name) mrb_define_const(mrb, module_key, "" #name "", mrb_fixnum_value(sf::Keyboard::Key:: ##name ))
#define REGISTER_BUTTON(mrb, module_key, name) mrb_define_const(mrb, module_key, "" #name "", mrb_fixnum_value(sf::Mouse::Button:: ##name ))
#define REGISTER_WHEEL(mrb, module_key, name) mrb_define_const(mrb, module_key, "" #name "", mrb_fixnum_value(sf::Mouse::Wheel:: ##name ))

void setup_ruby_events(mrb_state* mrb);