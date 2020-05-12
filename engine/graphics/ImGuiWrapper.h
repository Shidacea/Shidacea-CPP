#pragma once

#include "MrbWrap.h"

#include <SFML/Graphics.hpp>

#include "imgui.h"
#include "imgui-SFML.h"

void setup_ruby_imgui(mrb_state* mrb, RClass* ruby_module);