#include "Tileset.h"

Tileset::Tileset() {

	tiles.reserve(1000);

}

void Tileset::set_texture(const sf::Texture& new_texture) {

	texture = &new_texture;

}

const sf::Texture* Tileset::get_texture() {

	return texture;

}

Tile* Tileset::get_tile(unsigned int identification) {

	return tiles[identification];

}

size_t Tileset::size() {

	return tiles.size();

}

void Tileset::add_tile(Tile* tile) {

	tiles.push_back(tile);

}

void setup_ruby_class_tileset(mrb_state* mrb, RClass* ruby_module) {

	// @@@ MRBWRAPDOC_CLASS Tileset
	// Map tileset class
	MrbWrap::wrap_class_under<Tileset>(mrb, "Tileset", ruby_module);
	auto ruby_tileset_class = MrbWrap::get_class_info_ptr<Tileset>();

	// @@@ MRBWRAPDOC_IM Tileset initialize
	// @return [Tileset]
	// Creates an empty tileset
	MrbWrap::define_member_function(mrb, ruby_tileset_class, "initialize", MRUBY_FUNC {

		MrbWrap::convert_to_object<Tileset>(mrb, self);

		static auto tile_array_sym = mrb_intern_static(mrb, "@tiles", strlen("@tiles"));
		auto new_array = mrb_ary_new(mrb);
		mrb_iv_set(mrb, self, tile_array_sym, new_array);

		return self;

	}, MRB_ARGS_NONE());

	// @@@ MRBWRAPDOC_IM Tileset link_texture texture
	// @return [true]
	// @param texture [Texture]
	// Links the given tileset texture to the tileset
	MrbWrap::define_member_function(mrb, ruby_tileset_class, "link_texture", MRUBY_FUNC {

		auto args = MrbWrap::get_raw_args<sf::Texture>(mrb);
		auto ruby_texture = std::get<0>(args);

		auto tileset = MrbWrap::convert_from_object<Tileset>(mrb, self);
		auto texture = MrbWrap::convert_from_object<sf::Texture>(mrb, ruby_texture);

		tileset->set_texture(*texture);

		return mrb_true_value();

	}, MRB_ARGS_REQ(1));

	// @@@ MRBWRAPDOC_ATTR Tileset size Integer r
	// Total number of tiles in the tileset
	MrbWrap::wrap_getter<Tileset, &Tileset::size>(mrb, "size");

	// @@@ MRBWRAPDOC_IM Tileset add_tile tile
	// @return [true]
	// @param tile [Tile]
	// Adds a tile to the tileset
	MrbWrap::define_member_function(mrb, ruby_tileset_class, "add_tile", MRUBY_FUNC {

		//! TODO: Return index of the new tile

		auto args = MrbWrap::get_raw_args<Tile>(mrb);
		auto ruby_tile = std::get<0>(args);

		auto tileset = MrbWrap::convert_from_object<Tileset>(mrb, self);
		auto tile = MrbWrap::convert_from_object<Tile>(mrb, ruby_tile);

		static auto tile_array_sym = mrb_intern_static(mrb, "@tiles", strlen("@tiles"));
		auto ruby_tile_array = mrb_iv_get(mrb, self, tile_array_sym);

		mrb_ary_push(mrb, ruby_tile_array, ruby_tile);

		tileset->add_tile(tile);

		return mrb_true_value();

	}, MRB_ARGS_REQ(1));

	// @@@ MRBWRAPDOC_ATTR Tileset tiles Array<Tile> r
	// Returns an array of the tiles
	MrbWrap::define_member_function(mrb, ruby_tileset_class, "tiles", MRUBY_FUNC {

		static auto tile_array_sym = mrb_intern_static(mrb, "@tiles", strlen("@tiles"));
		auto ruby_tile_array = mrb_iv_get(mrb, self, tile_array_sym);

		return ruby_tile_array;

	}, MRB_ARGS_NONE());

}