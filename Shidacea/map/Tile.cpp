#include "Tile.h"

bool Tile::is_solid() {

	return solid;

}

bool Tile::is_animation_frame() {

	return animation_frame;

}

void Tile::set_as_solid() {

	solid = true;

}

void Tile::set_animation(unsigned int index_of_first_animation_frame, 
	unsigned int index_of_first_other_animation_frame,
	unsigned int number_of_animation_frames,
	unsigned int time_per_animation_frame) {

	animation_frame = true;

	this->index_of_first_animation_frame = index_of_first_animation_frame;
	this->index_of_first_other_animation_frame = index_of_first_other_animation_frame;
	this->number_of_animation_frames = number_of_animation_frames;
	this->time_per_animation_frame = time_per_animation_frame;

}

unsigned int Tile::get_animation_frame(unsigned int frame_counter) {

	auto animation_cycle = number_of_animation_frames * time_per_animation_frame;
	auto animation_time = frame_counter % animation_cycle;
	auto animation_index = animation_time / time_per_animation_frame;

	if (animation_index == 0) {

		return index_of_first_animation_frame;

	} else {

		//! -1 since animation_index can't be lower than 1 in this case
		return index_of_first_other_animation_frame + animation_index - 1;

	}

}

mrb_value ruby_tile_init(mrb_state* mrb, mrb_value self) {

	MrbWrap::convert_to_object<Tile>(mrb, self);

	return self;

}

void setup_ruby_class_tile(mrb_state* mrb) {

	auto ruby_tileset_class = MrbWrap::define_data_class(mrb, "Tile");

	mrb_define_method(mrb, ruby_tileset_class, "initialize", ruby_tile_init, MRB_ARGS_NONE());

}