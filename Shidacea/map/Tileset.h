#pragma once

#include "Helper.h"

#include <SFML/Graphics.hpp>

#include "Tile.h"

class Tileset {

public:

	Tileset();
	void set_texture(const sf::Texture& new_texture);
	const sf::Texture* get_texture();
	Tile* get_tile(unsigned int identification);
	size_t size();
	void add_tile(Tile* tile);

private:

	const sf::Texture* texture = nullptr;
	std::vector<Tile*> tiles;

};

void setup_ruby_class_tileset(mrb_state* mrb, RClass* ruby_module);
