#pragma once

#include "Helper.h"

class Tile {

public:

	Tile() = default;
	~Tile() = default;

	bool is_solid();
	bool is_animation_frame();

	void set_as_solid(bool value = true);

	unsigned int get_animation_frame(unsigned int frame_counter);

	void set_animation(unsigned int index_of_first_animation_frame,
		unsigned int index_of_first_other_animation_frame,
		unsigned int number_of_animation_frames,
		unsigned int time_per_animation_frame);

private:

	bool solid = false;
	bool animation_frame = false;

	unsigned int index_of_first_animation_frame = 0;
	unsigned int index_of_first_other_animation_frame = 0;
	unsigned int number_of_animation_frames = 0;
	unsigned int time_per_animation_frame = 0;

};

void setup_ruby_class_tile(mrb_state* mrb, RClass* ruby_module);