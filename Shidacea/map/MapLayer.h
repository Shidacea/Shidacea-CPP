#pragma once

#include <cmath>

#include "Helper.h"

#include <SFML/Graphics.hpp>

#include "Tile.h"

class MapLayer : public sf::Drawable, public sf::Transformable {

public:

	MapLayer(unsigned int width, unsigned int height, unsigned int view_width, unsigned int view_height);

	void reload(float cam_x, float cam_y);
	void load_test_map();

	void set_tile(unsigned int x, unsigned int y, unsigned int tile_id);

private:

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	unsigned int width = 0;
	unsigned int height = 0;

	unsigned int view_width = 0;
	unsigned int view_height = 0;

	unsigned int background_tile = 0;

	std::vector<std::vector<unsigned int>> tiles;
	sf::VertexArray vertices;

	sf::Texture tileset;
	std::vector<Tile> tile_data;

	unsigned int frame_counter = 0;

};

mrb_value ruby_map_layer_init(mrb_state* mrb, mrb_value self);
mrb_value ruby_map_layer_reload(mrb_state* mrb, mrb_value self);
mrb_value ruby_map_layer_load_test_map(mrb_state* mrb, mrb_value self);

void setup_ruby_class_map_layer(mrb_state* mrb);