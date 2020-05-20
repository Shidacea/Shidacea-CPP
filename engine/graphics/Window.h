#pragma once

#include "MrbWrap.h"

#include <SFML/Graphics.hpp>

#include "RenderQueueWindow.h"

void setup_ruby_class_window(mrb_state* mrb, RClass* ruby_module);

static RClass* window_ruby_module;