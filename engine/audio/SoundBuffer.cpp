#include "SoundBuffer.h"

void setup_ruby_class_sound_buffer(mrb_state* mrb, RClass* ruby_module) {

	MrbWrap::wrap_class_under<sf::SoundBuffer>(mrb, "SoundBuffer", ruby_module);

	MrbWrap::wrap_constructor<sf::SoundBuffer>(mrb);

	MrbWrap::wrap_member_function<sf::SoundBuffer, &sf::SoundBuffer::loadFromFile, MRBW_FILE>(mrb, "load_from_file");

}