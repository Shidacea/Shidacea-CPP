#pragma once

#include "Helper.h"

#include <SFML/Audio.hpp>

mrb_value ruby_music_init(mrb_state* mrb, mrb_value self);
mrb_value ruby_music_open_from_file(mrb_state* mrb, mrb_value self);
mrb_value ruby_music_play(mrb_state* mrb, mrb_value self);
mrb_value ruby_music_stop(mrb_state* mrb, mrb_value self);
mrb_value ruby_music_looping(mrb_state* mrb, mrb_value self);
mrb_value ruby_music_looping_equals(mrb_state* mrb, mrb_value self);

void setup_ruby_class_music(mrb_state* mrb);