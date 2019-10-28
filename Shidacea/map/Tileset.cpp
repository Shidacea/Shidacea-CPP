#include "Tileset.h"

Tileset::Tileset(size_t size) {

	allocate_tiles(size);

}

void Tileset::set_texture(const sf::Texture& new_texture) {

	texture = &new_texture;

}

const sf::Texture* Tileset::get_texture() {

	return texture;

}

Tile& Tileset::get_tile(unsigned int identification) {

	return tiles[identification];

}

void Tileset::allocate_tiles(unsigned int number) {

	tiles.resize(number);

}

size_t Tileset::size() {

	return tiles.size();

}

mrb_value ruby_tileset_init(mrb_state* mrb, mrb_value self) {

	//! TODO: Obtain size from texture
	MrbWrap::convert_to_object<Tileset>(mrb, self, 8);

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

void setup_ruby_class_tileset(mrb_state* mrb) {

	auto ruby_tileset_class = MrbWrap::define_data_class(mrb, "Tileset");

	mrb_define_method(mrb, ruby_tileset_class, "initialize", ruby_tileset_init, MRB_ARGS_NONE());
	mrb_define_method(mrb, ruby_tileset_class, "link_texture", ruby_tileset_link_texture, MRB_ARGS_REQ(1));
	mrb_define_method(mrb, ruby_tileset_class, "size", ruby_tileset_size, MRB_ARGS_NONE());

}