#pragma once

#include "Helper.h"

#include <SFML/Graphics.hpp>

#include "Tile.h"

class Tileset {

public:

	Tileset(size_t size);
	void set_texture(const sf::Texture& new_texture);
	const sf::Texture* get_texture();
	Tile& Tileset::get_tile(unsigned int identification);
	void Tileset::allocate_tiles(unsigned int number);
	size_t size();

private:

	const sf::Texture* texture = nullptr;
	std::vector<Tile> tiles;

};

void setup_ruby_class_tileset(mrb_state* mrb);