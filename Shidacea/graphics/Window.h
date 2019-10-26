#pragma once

#include "Helper.h"

#include <SFML/Graphics.hpp>

#include "imgui.h"
#include "imgui-SFML.h"

#include "Sprite.h"
#include "MapLayer.h"

void draw_object(sf::RenderWindow* window, sf::RenderStates& render_states, mrb_state* mrb, mrb_value& draw_object);

void setup_ruby_class_window(mrb_state* mrb);