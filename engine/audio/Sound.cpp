#include "Sound.h"

void setup_ruby_class_sound(mrb_state* mrb, RClass* ruby_module) {

	MrbWrap::wrap_class_under<sf::Sound>(mrb, "Sound", ruby_module);

	MrbWrap::wrap_constructor<sf::Sound>(mrb);

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
	MrbWrap::wrap_member_function<sf::Sound, &sf::Sound::pause>(mrb, "pause");
	MrbWrap::wrap_member_function<sf::Sound, &sf::Sound::stop>(mrb, "stop");

	MrbWrap::wrap_getter<sf::Sound, &sf::Sound::getVolume>(mrb, "volume");
	MrbWrap::wrap_setter<sf::Sound, &sf::Sound::setVolume, float>(mrb, "volume=");

	MrbWrap::wrap_getter<sf::Sound, &sf::Sound::getPitch>(mrb, "pitch");
	MrbWrap::wrap_setter<sf::Sound, &sf::Sound::setPitch, float>(mrb, "pitch=");

}