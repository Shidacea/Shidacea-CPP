#pragma once

#include "Helper.h"

#include <SFML/Graphics.hpp>

#define REGISTER_TYPE(mrb, module_key, name) mrb_define_const(mrb, module_key, "" #name "", mrb_fixnum_value(static_cast<int>(sf::Event::EventType:: ##name )))
#define REGISTER_KEY(mrb, module_key, name) mrb_define_const(mrb, module_key, "" #name "", mrb_fixnum_value(static_cast<int>(sf::Keyboard::Key:: ##name )))
#define REGISTER_BUTTON(mrb, module_key, name) mrb_define_const(mrb, module_key, "" #name "", mrb_fixnum_value(static_cast<int>(sf::Mouse::Button:: ##name )))
#define REGISTER_WHEEL(mrb, module_key, name) mrb_define_const(mrb, module_key, "" #name "", mrb_fixnum_value(static_cast<int>(sf::Mouse::Wheel:: ##name )))

void setup_ruby_events(mrb_state* mrb);

mrb_value ruby_event_key_is_pressed(mrb_state* mrb, mrb_value self);

mrb_value ruby_event_mouse_get_position(mrb_state* mrb, mrb_value self);
mrb_value ruby_event_mouse_is_button_pressed(mrb_state* mrb, mrb_value self);
mrb_value ruby_event_mouse_set_position(mrb_state* mrb, mrb_value self);

mrb_value ruby_event_init(mrb_state* mrb, mrb_value self);

mrb_value ruby_event_type(mrb_state* mrb, mrb_value self);

mrb_value ruby_event_key_code(mrb_state* mrb, mrb_value self);
mrb_value ruby_event_key_alt(mrb_state* mrb, mrb_value self);
mrb_value ruby_event_key_control(mrb_state* mrb, mrb_value self);
mrb_value ruby_event_key_shift(mrb_state* mrb, mrb_value self);
mrb_value ruby_event_key_system(mrb_state* mrb, mrb_value self);

mrb_value ruby_event_mouse_button_code(mrb_state* mrb, mrb_value self);
mrb_value ruby_event_mouse_button_x(mrb_state* mrb, mrb_value self);
mrb_value ruby_event_mouse_button_y(mrb_state* mrb, mrb_value self);

mrb_value ruby_event_mouse_move_x(mrb_state* mrb, mrb_value self);
mrb_value ruby_event_mouse_move_y(mrb_state* mrb, mrb_value self);

mrb_value ruby_event_mouse_scroll_wheel(mrb_state* mrb, mrb_value self);
mrb_value ruby_event_mouse_scroll_delta(mrb_state* mrb, mrb_value self);
mrb_value ruby_event_mouse_scroll_x(mrb_state* mrb, mrb_value self);
mrb_value ruby_event_mouse_scroll_y(mrb_state* mrb, mrb_value self);

void setup_ruby_class_event(mrb_state* mrb);