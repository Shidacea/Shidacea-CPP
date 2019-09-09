#include "MapLayer.h"

#include <iostream>

MapLayer::MapLayer(unsigned int width, unsigned int height, unsigned int view_width, unsigned int view_height) {

	this->width = width;
	this->height = height;
	this->view_width = view_width;
	this->view_height = view_height;

	vertices.setPrimitiveType(sf::Quads);
	vertices.resize(static_cast<size_t>(view_width) * view_height * 4);	//! 4 Vertices per quad

}

void MapLayer::reload(float cam_x, float cam_y) {

	//! The mesh will be aligned to the camera position
	//! Only the tiles touching the mesh will be drawn

	auto exact_shift_x = cam_x - (view_width - 1) * 30 - 1;
	auto exact_shift_y = cam_y - (view_height - 1) * 30 - 1;

	auto shift_x = static_cast<int>(std::floor(exact_shift_x)) / 60;
	auto shift_y = static_cast<int>(std::floor(exact_shift_y)) / 60;

	auto tileset_size = tileset.getSize();
	auto n_tiles_x = tileset_size.x / 60;
	auto n_tiles_y = tileset_size.y / 60;

	for (unsigned int x = 0; x < view_width; x++) {
		for (unsigned int y = 0; y < view_height; y++) {

			//! The following values are the actual tile coordinates on the map

			auto exact_actual_x = static_cast<float>(x) + exact_shift_x / 60;
			auto exact_actual_y = static_cast<float>(y) + exact_shift_y / 60;

			int actual_x = static_cast<int>(std::floor(exact_actual_x));
			int actual_y = static_cast<int>(std::floor(exact_actual_y));

			//! TODO: Fix the black bar! Or try something else

			//! Filter invalid tile coordinates and assign them a default background tile

			unsigned int tile_id;

			if (actual_x < 0 || static_cast<unsigned int>(actual_x) >= width || actual_y < 0 || static_cast<unsigned int>(actual_y) >= height) {

				tile_id = background_tile;

			} else {

				tile_id = tiles[actual_x][actual_y];

			}

			auto actual_tile_id = tile_id;

			auto tile_info = tile_data[tile_id];
			if (tile_info.is_animation_frame()) {

				actual_tile_id = tile_info.get_animation_frame(frame_counter);

			}

			//! The tile ID indicates the position on the tileset

			auto tx = actual_tile_id % n_tiles_x;
			auto ty = actual_tile_id / n_tiles_x;

			for (unsigned int c = 0; c < 4; c++) {

				//! Some magic which will ensure that the vertices of a quad won't be cross-iterated but along the quad border

				unsigned int dx = (c == 1 || c == 2);
				unsigned int dy = (c == 2 || c == 3);

				auto& vertex = vertices[(static_cast<size_t>(x) * view_height + y) * 4 + c];

				//! Set the position of the mesh vertices

				auto vx = static_cast<float>((actual_x + static_cast<int>(dx)) * 60); //! TODO: Generalize for arbitrary resolutions and tile size
				auto vy = static_cast<float>((actual_y + static_cast<int>(dy)) * 60);

				vertex.position = sf::Vector2f(vx, vy);

				//! Apply the texture coordinates obtained from the tile ID to the vertices

				auto vtx = static_cast<float>((tx + dx) * 60);
				auto vty = static_cast<float>((ty + dy) * 60);

				vertex.texCoords = sf::Vector2f(vtx, vty);

			}

		}
	}

	frame_counter++;

}

void MapLayer::load_test_map() {

	//! TODO: Don't load this file more than ONE SINGLE TIME
	if (!tileset.loadFromFile("assets/graphics/maptest/Tileset.png")) {

		exit(-1);
		//! TODO: Error handling
	}

	//! TODO: Put tileset declarations in other file or so
	auto tileset_size = tileset.getSize();
	auto n_tiles_x = tileset_size.x / 60;
	auto n_tiles_y = tileset_size.y / 60;
	auto n_tiles = n_tiles_x * n_tiles_y;

	tile_data.resize(n_tiles);

	tile_data[2].set_animation(2, 3, 2, 60);
	
	tile_data[2].set_as_solid();
	tile_data[3].set_as_solid();
	tile_data[4].set_as_solid();
	tile_data[5].set_as_solid();

	background_tile = 2;

	unsigned int debug_counter = 0;

	tiles.resize(this->width);
	for (auto& column : tiles) {

		column.resize(this->height);
		for (auto& tile : column) {

			tile = debug_counter % 3;
			if (tile == 2) tile = 0;
			debug_counter *= 7;
			debug_counter += 3;

		}

	}

}

void MapLayer::set_tile(unsigned int x, unsigned int y, unsigned int tile_id) {

	tiles[x][y] = tile_id;

}

void MapLayer::draw(sf::RenderTarget& target, sf::RenderStates states) const {

	states.transform *= getTransform();
	states.texture = &tileset;
	target.draw(vertices, states);

}

mrb_value ruby_map_layer_init(mrb_state* mrb, mrb_value self) {

	mrb_int width;
	mrb_int height;
	mrb_int view_width;
	mrb_int view_height;
	
	mrb_get_args(mrb, "iiii", &width, &height, &view_width, &view_height);

	auto map_layer = MrbWrap::convert_to_object<MapLayer>(mrb, self, 
		static_cast<unsigned int>(width), static_cast<unsigned int>(height), 
		static_cast<unsigned int>(view_width), static_cast<unsigned int>(view_height));

	return self;

}

mrb_value ruby_map_layer_reload(mrb_state* mrb, mrb_value self) {

	mrb_value ruby_coordinates;

	mrb_get_args(mrb, "o", &ruby_coordinates);

	auto coordinates = MrbWrap::convert_from_object<sf::Vector2f>(mrb, ruby_coordinates);

	auto map_layer = MrbWrap::convert_from_object<MapLayer>(mrb, self);
	map_layer->reload(coordinates->x, coordinates->y);

	return mrb_true_value();

}

mrb_value ruby_map_layer_load_test_map(mrb_state* mrb, mrb_value self) {

	auto map_layer = MrbWrap::convert_from_object<MapLayer>(mrb, self);
	map_layer->load_test_map();

	return mrb_nil_value();
}

void setup_ruby_class_map_layer(mrb_state* mrb) {

	auto ruby_map_layer_class = MrbWrap::define_data_class(mrb, "MapLayer");

	mrb_define_method(mrb, ruby_map_layer_class, "initialize", ruby_map_layer_init, MRB_ARGS_REQ(4));
	mrb_define_method(mrb, ruby_map_layer_class, "reload", ruby_map_layer_reload, MRB_ARGS_REQ(1));
	mrb_define_method(mrb, ruby_map_layer_class, "load_test_map", ruby_map_layer_load_test_map, MRB_ARGS_NONE());

}