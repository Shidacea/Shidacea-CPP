#pragma once

#include "Helper.h"

#include <SFML/Graphics.hpp>

#ifndef SHIDACEA_EXCLUDE_IMGUI

	#include "imgui.h"
	#include "imgui-SFML.h"

#endif

#include "Sprite.h"
#include "MapLayer.h"

void draw_object(sf::RenderWindow* window, sf::RenderStates& render_states, mrb_state* mrb, mrb_value& draw_object);

void setup_ruby_class_window(mrb_state* mrb, RClass* ruby_module);

static RClass* window_ruby_module;