#include "Music.h"

void setup_ruby_class_music(mrb_state* mrb, RClass* ruby_module) {

	auto ruby_music_class = MrbWrap::define_data_class_under(mrb, "Music", ruby_module);

	MrbWrap::wrap_class_under<sf::Music>(mrb, "Music", ruby_module);

	MrbWrap::wrap_constructor<sf::Music>(mrb);

	MrbWrap::wrap_member_function<sf::Music, &sf::Music::play>(mrb, "play");
	MrbWrap::wrap_member_function<sf::Music, &sf::Music::stop>(mrb, "stop");
	MrbWrap::wrap_member_function<sf::Music, &sf::Music::pause>(mrb, "pause");

	//! Different name to clarify meaning
	MrbWrap::wrap_getter<sf::Music, &sf::Music::getLoop>(mrb, "looping");
	MrbWrap::wrap_setter<sf::Music, &sf::Music::setLoop, bool>(mrb, "looping=");

	MrbWrap::wrap_getter<sf::Music, &sf::Music::getPitch>(mrb, "pitch");
	MrbWrap::wrap_setter<sf::Music, &sf::Music::setPitch, float>(mrb, "pitch=");

	MrbWrap::wrap_getter<sf::Music, &sf::Music::getVolume>(mrb, "volume");
	MrbWrap::wrap_setter<sf::Music, &sf::Music::setVolume, float>(mrb, "volume=");

	MrbWrap::wrap_member_function<sf::Music, &sf::Music::openFromFile, MRBW_FILE>(mrb, "open_from_file");

	// TODO: Loops like music->setLoopPoints(sf::Music::Span(sf::milliseconds(2 * 1000 * 4), sf::milliseconds(2 * 1000 * 4)));

}