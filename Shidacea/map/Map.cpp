#include "Map.h"

void Map::load(unsigned int width, unsigned int height, unsigned int view_width, unsigned int view_height) {

	this->width = width;
	this->height = height;

	frame_counter_ptr = std::make_shared<unsigned int>(0);

	for (auto& map_layer : map_layers) {

		map_layer.load_tiles(width, height, frame_counter_ptr);
		map_layer.initialize_mesh(view_width + 1, view_height + 1);

	}

	map_layers[2].set_tile(3, 3, 4);

}

void Map::update() {

	(*frame_counter_ptr)++;

}

void Map::reload_layers(float actor_x, float actor_y) {

	for (auto& map_layer : map_layers) {

		map_layer.generate_mesh(actor_x, actor_y);

	}

}

void Map::draw(sf::RenderTarget& target, sf::RenderStates states) const {

	states.transform *= getTransform();
	for(auto& map_layer : map_layers) target.draw(map_layer, states);

}

mrb_value ruby_map_init(mrb_state* mrb, mrb_value self) {

	int width;
	int height;
	int view_width;
	int view_height;

	mrb_get_args(mrb, "iiii", &width, &height, &view_width, &view_height);

	auto map = MrbWrap::convert_to_object<Map>(mrb, self);
	map->load(width, height, view_width, view_height);

	return self;

}

mrb_value ruby_map_reload(mrb_state* mrb, mrb_value self) {

	mrb_value coordinates;

	mrb_get_args(mrb, "o", &coordinates);

	auto position = MrbWrap::convert_from_object<sf::Vector2f>(mrb, coordinates);
	auto map = MrbWrap::convert_from_object<Map>(mrb, self);

	map->reload_layers(position->x, position->y);	//! TODO: Carry over sf::Vector into this function

	return mrb_nil_value();

}

void setup_ruby_class_map(mrb_state* mrb) {

	auto ruby_map_class = MrbWrap::define_data_class(mrb, "Map");

	mrb_define_method(mrb, ruby_map_class, "initialize", ruby_map_init, MRB_ARGS_REQ(4));
	mrb_define_method(mrb, ruby_map_class, "reload", ruby_map_reload, MRB_ARGS_REQ(1));

}