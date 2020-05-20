#pragma once

#include "MrbWrap.h"

#include <SFML/Graphics.hpp>

#include "RenderQueueWindow.h"

#define REGISTER_TYPE(mrb, module_key, name) mrb_define_const(mrb, module_key, "" #name "", mrb_fixnum_value(static_cast<int>(sf::Event::EventType::name )))
#define REGISTER_KEY(mrb, module_key, name) mrb_define_const(mrb, module_key, "" #name "", mrb_fixnum_value(static_cast<int>(sf::Keyboard::Key::name )))
#define REGISTER_BUTTON(mrb, module_key, name) mrb_define_const(mrb, module_key, "" #name "", mrb_fixnum_value(static_cast<int>(sf::Mouse::Button::name )))
#define REGISTER_WHEEL(mrb, module_key, name) mrb_define_const(mrb, module_key, "" #name "", mrb_fixnum_value(static_cast<int>(sf::Mouse::Wheel::name )))

void setup_ruby_events(mrb_state* mrb, RClass* ruby_module);

mrb_value ruby_event_key_is_pressed(mrb_state* mrb, mrb_value self);

mrb_value ruby_event_mouse_get_position(mrb_state* mrb, mrb_value self);
mrb_value ruby_event_mouse_is_button_pressed(mrb_state* mrb, mrb_value self);
mrb_value ruby_event_mouse_set_position(mrb_state* mrb, mrb_value self);

void setup_ruby_class_event(mrb_state* mrb, RClass* ruby_module);