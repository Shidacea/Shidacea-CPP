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

	auto ruby_tileset_class = MrbWrap::define_data_class_under(mrb, "Tileset", ruby_module);

	MrbWrap::define_mruby_function(mrb, ruby_tileset_class, "initialize", MRUBY_FUNC {

		MrbWrap::convert_to_object<Tileset>(mrb, self);

		static auto tile_array_sym = mrb_intern_static(mrb, "@tiles", strlen("@tiles"));
		auto new_array = mrb_ary_new(mrb);
		mrb_iv_set(mrb, self, tile_array_sym, new_array);

		return self;

	});

	MrbWrap::define_mruby_function(mrb, ruby_tileset_class, "link_texture", MRUBY_FUNC {

		auto args = MrbWrap::get_args<sf::Texture>(mrb);
		auto ruby_texture = std::get<0>(args);

		auto tileset = MrbWrap::convert_from_object<Tileset>(mrb, self);
		auto texture = MrbWrap::convert_from_object<sf::Texture>(mrb, ruby_texture);

		tileset->set_texture(*texture);

		return mrb_true_value();

	});

	MrbWrap::wrap_getter<MRBW_FUNC(Tileset, Tileset::size)>(mrb, ruby_tileset_class, "size");

	MrbWrap::define_mruby_function(mrb, ruby_tileset_class, "add_tile", MRUBY_FUNC {

		auto args = MrbWrap::get_args<Tile>(mrb);
		auto ruby_tile = std::get<0>(args);

		auto tileset = MrbWrap::convert_from_object<Tileset>(mrb, self);
		auto tile = MrbWrap::convert_from_object<Tile>(mrb, ruby_tile);

		static auto tile_array_sym = mrb_intern_static(mrb, "@tiles", strlen("@tiles"));
		auto ruby_tile_array = mrb_iv_get(mrb, self, tile_array_sym);

		mrb_ary_push(mrb, ruby_tile_array, ruby_tile);

		tileset->add_tile(tile);

		return mrb_true_value();

	});

	MrbWrap::define_mruby_function(mrb, ruby_tileset_class, "tiles", MRUBY_FUNC {

		static auto tile_array_sym = mrb_intern_static(mrb, "@tiles", strlen("@tiles"));
		auto ruby_tile_array = mrb_iv_get(mrb, self, tile_array_sym);

		return ruby_tile_array;

	});

}