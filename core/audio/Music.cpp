#include "Music.h"

void setup_ruby_class_music(mrb_state* mrb, RClass* ruby_module) {

	auto ruby_music_class = MrbWrap::define_data_class_under(mrb, "Music", ruby_module);

	MrbWrap::wrap_constructor<sf::Music>(mrb, ruby_music_class);

	MrbWrap::wrap_function<MRBW_FUNC(sf::Music, sf::Music::play)>(mrb, ruby_music_class, "play");
	MrbWrap::wrap_function<MRBW_FUNC(sf::Music, sf::Music::stop)>(mrb, ruby_music_class, "stop");
	MrbWrap::wrap_function<MRBW_FUNC(sf::Music, sf::Music::pause)>(mrb, ruby_music_class, "pause");

	//! Different name to clarify meaning
	MrbWrap::wrap_getter<MRBW_FUNC(sf::Music, sf::Music::getLoop)>(mrb, ruby_music_class, "looping");
	MrbWrap::wrap_setter<MRBW_FUNC(sf::Music, sf::Music::setLoop), bool>(mrb, ruby_music_class, "looping=");

	MrbWrap::wrap_getter<MRBW_FUNC(sf::Music, sf::Music::getPitch)>(mrb, ruby_music_class, "pitch");
	MrbWrap::wrap_setter<MRBW_FUNC(sf::Music, sf::Music::setPitch), float>(mrb, ruby_music_class, "pitch=");

	MrbWrap::wrap_getter<MRBW_FUNC(sf::Music, sf::Music::getVolume)>(mrb, ruby_music_class, "volume");
	MrbWrap::wrap_setter<MRBW_FUNC(sf::Music, sf::Music::setVolume), float>(mrb, ruby_music_class, "volume=");

	MrbWrap::wrap_function<MRBW_FUNC(sf::Music, sf::Music::openFromFile), std::string>(mrb, ruby_music_class, "open_from_file");

	// TODO: Loops like music->setLoopPoints(sf::Music::Span(sf::milliseconds(2 * 1000 * 4), sf::milliseconds(2 * 1000 * 4)));

}