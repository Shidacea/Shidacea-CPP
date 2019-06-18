#pragma once

#include "Helper.h"

#include <SFML/Graphics.hpp>

#include "imgui.h"
#include "imgui-SFML.h"

mrb_value ruby_imgui_begin(mrb_state* mrb, mrb_value self);
mrb_value ruby_imgui_button(mrb_state* mrb, mrb_value self);
mrb_value ruby_imgui_text(mrb_state* mrb, mrb_value self);
mrb_value ruby_imgui_begin_child(mrb_state* mrb, mrb_value self);
mrb_value ruby_imgui_same_line(mrb_state* mrb, mrb_value self);
mrb_value ruby_imgui_new_line(mrb_state* mrb, mrb_value self);
mrb_value ruby_imgui_input_int(mrb_state* mrb, mrb_value self);
mrb_value ruby_imgui_input_instance_variable_int(mrb_state* mrb, mrb_value self);

void setup_ruby_imgui(mrb_state* mrb);