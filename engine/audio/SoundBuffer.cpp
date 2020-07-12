#include "SoundBuffer.h"

void setup_ruby_class_sound_buffer(mrb_state* mrb, RClass* ruby_module) {

	MrbWrap::wrap_class_under<sf::SoundBuffer>(mrb, "SoundBuffer", ruby_module);

	// @@@ MRBWRAPDOC_IM SoundBuffer initialize
	// @return [Sound]
	// Creates a sound buffer (without content)
	MrbWrap::wrap_constructor<sf::SoundBuffer>(mrb);

	// @@@ MRBWRAPDOC_IM SoundBuffer load_from_file filename
	// @return [Boolean]
	// @param filename [String]
	// Loads a sound from the file, returning true if loading was successful, else false.
	MrbWrap::wrap_member_function<sf::SoundBuffer, &sf::SoundBuffer::loadFromFile, MRBW_FILE>(mrb, "load_from_file");

}