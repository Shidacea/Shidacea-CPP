#include "Sound.h"

void setup_ruby_class_sound(mrb_state* mrb, RClass* ruby_module) {

	MrbWrap::wrap_class_under<sf::Sound>(mrb, "Sound", ruby_module);

	// @@@ MRBWRAPDOC_IM Sound initialize
	// @return [Sound]
	// Creates a sound (without content)
	MrbWrap::wrap_constructor<sf::Sound>(mrb);

	// @@@ MRBWRAPDOC_IM Sound link_sound_buffer sound_buffer
	// @return [true]
	// @param sound_buffer [SoundBuffer]
	// Links a sound buffer to this sound
	MrbWrap::define_member_function(mrb, MrbWrap::get_class_info_ptr<sf::Sound>(), "link_sound_buffer", MRUBY_FUNC {

		auto args = MrbWrap::get_raw_args<sf::SoundBuffer>(mrb);
		auto ruby_buffer = std::get<0>(args);

		auto sound = MrbWrap::convert_from_object<sf::Sound>(mrb, self);
		auto sound_buffer = MrbWrap::convert_from_object<sf::SoundBuffer>(mrb, ruby_buffer);

		sound->setBuffer(*sound_buffer);

		return mrb_true_value();

	}, MRB_ARGS_REQ(1));

	// @@@ MRBWRAPDOC_IM Sound play
	// @return [nil]
	// Plays the sound from the beginning or resumes it if paused
	MrbWrap::wrap_member_function<sf::Sound, &sf::Sound::play>(mrb, "play");

	// @@@ MRBWRAPDOC_IM Sound play
	// @return [nil]
	// Pauses the sound if running
	MrbWrap::wrap_member_function<sf::Sound, &sf::Sound::pause>(mrb, "pause");

	// @@@ MRBWRAPDOC_IM Sound stop
	// @return [nil]
	// Stops the sound if running
	MrbWrap::wrap_member_function<sf::Sound, &sf::Sound::stop>(mrb, "stop");

	// @@@ MRBWRAPDOC_ATTR Sound volume Float rw
	// Volume of the sound, ranging from 0 to 100 (default)
	MrbWrap::wrap_getter<sf::Sound, &sf::Sound::getVolume>(mrb, "volume");
	MrbWrap::wrap_setter<sf::Sound, &sf::Sound::setVolume, float>(mrb, "volume=");

	// @@@ MRBWRAPDOC_ATTR Sound pitch Float rw
	// Pitch of the sound, with default 1.0
	MrbWrap::wrap_getter<sf::Sound, &sf::Sound::getPitch>(mrb, "pitch");
	MrbWrap::wrap_setter<sf::Sound, &sf::Sound::setPitch, float>(mrb, "pitch=");

}