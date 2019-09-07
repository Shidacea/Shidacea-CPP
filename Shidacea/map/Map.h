#pragma once

#include "Helper.h"

#include <SFML/Graphics.hpp>

#include "MapLayer.h"

#include <array>

class Map : public sf::Drawable, public sf::Transformable {

public:

	void load(unsigned int width, unsigned int height, unsigned int view_width, unsigned int view_height);

	void reload_layers(float actor_x, float actor_y);

	void update();

private:

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	unsigned int width = 0;
	unsigned int height = 0;

	//! Layers: 0 - Ground, 1 - Ground Decoration, 2 - Objects
	std::array<MapLayer, 3> map_layers;

};

mrb_value ruby_map_init(mrb_state* mrb, mrb_value self);
mrb_value ruby_map_reload(mrb_state* mrb, mrb_value self);

void setup_ruby_class_map(mrb_state* mrb);