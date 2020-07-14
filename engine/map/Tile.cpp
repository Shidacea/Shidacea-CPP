#include "Tile.h"

bool Tile::is_solid() {

	return solid;

}

bool Tile::is_animation_frame() {

	return animation_frame;

}

void Tile::set_as_solid(bool value) {

	solid = value;

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

void setup_ruby_class_tile(mrb_state* mrb, RClass* ruby_module) {

	// @@@ M_CLASS Tile
	// Map tile data class
	MrbWrap::wrap_class_under<Tile>(mrb, "Tile", ruby_module);

	// @@@ M_IM Tile initialize
	// @return [Tile]
	// Creates an empty tile
	MrbWrap::wrap_constructor<Tile>(mrb);

	// @@@ M_ATTR Tile solid Boolean rw
	// Property determining whether the tile is passable
	MrbWrap::wrap_getter<Tile, &Tile::is_solid>(mrb, "solid");
	MrbWrap::wrap_setter<Tile, &Tile::set_as_solid, bool>(mrb, "solid=");

}