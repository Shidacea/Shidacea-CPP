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

mrb_value ruby_tileset_init(mrb_state* mrb, mrb_value self) {

	MrbWrap::convert_to_object<Tileset>(mrb, self);

	static auto tile_array_sym = mrb_intern_static(mrb, "@_tiles", strlen("@_tiles"));
	auto new_array = mrb_ary_new(mrb);
	mrb_iv_set(mrb, self, tile_array_sym, new_array);

	return self;

}

mrb_value ruby_tileset_link_texture(mrb_state* mrb, mrb_value self) {

	mrb_value ruby_texture;

	mrb_get_args(mrb, "o", &ruby_texture);

	auto tileset = MrbWrap::convert_from_object<Tileset>(mrb, self);
	auto texture = MrbWrap::convert_from_object<sf::Texture>(mrb, ruby_texture);

	tileset->set_texture(*texture);

	return mrb_true_value();

}

mrb_value ruby_tileset_size(mrb_state* mrb, mrb_value self) {

	auto tileset = MrbWrap::convert_from_object<Tileset>(mrb, self);
	return mrb_fixnum_value(tileset->size());

}

mrb_value ruby_tileset_add_tile(mrb_state* mrb, mrb_value self) {

	mrb_value ruby_tile;

	mrb_get_args(mrb, "o", &ruby_tile);

	auto tileset = MrbWrap::convert_from_object<Tileset>(mrb, self);
	auto tile = MrbWrap::convert_from_object<Tile>(mrb, ruby_tile);

	static auto tile_array_sym = mrb_intern_static(mrb, "@_tiles", strlen("@_tiles"));
	auto ruby_tile_array = mrb_iv_get(mrb, self, tile_array_sym);

	mrb_ary_push(mrb, ruby_tile_array, ruby_tile);

	tileset->add_tile(tile);

	return mrb_true_value();

}

void setup_ruby_class_tileset(mrb_state* mrb) {

	auto ruby_tileset_class = MrbWrap::define_data_class(mrb, "Tileset");

	mrb_define_method(mrb, ruby_tileset_class, "initialize", ruby_tileset_init, MRB_ARGS_NONE());
	mrb_define_method(mrb, ruby_tileset_class, "link_texture", ruby_tileset_link_texture, MRB_ARGS_REQ(1));
	mrb_define_method(mrb, ruby_tileset_class, "size", ruby_tileset_size, MRB_ARGS_NONE());
	mrb_define_method(mrb, ruby_tileset_class, "add_tile", ruby_tileset_add_tile, MRB_ARGS_REQ(1));

}