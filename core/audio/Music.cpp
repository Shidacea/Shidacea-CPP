#include "Music.h"

void setup_ruby_class_music(mrb_state* mrb, RClass* ruby_module) {

	auto ruby_music_class = MrbWrap::define_data_class_under(mrb, "Music", ruby_module);

	MrbWrap::wrap_constructor<sf::Music>(mrb, ruby_music_class);

	MrbWrap::wrap_function<sf::Music, decltype(&sf::Music::play), &sf::Music::play>(mrb, ruby_music_class, "play");
	MrbWrap::wrap_function<sf::Music, decltype(&sf::Music::stop), &sf::Music::stop>(mrb, ruby_music_class, "stop");
	MrbWrap::wrap_function<sf::Music, decltype(&sf::Music::pause), &sf::Music::pause>(mrb, ruby_music_class, "pause");

	MrbWrap::wrap_getter<sf::Music, decltype(&sf::Music::getLoop), &sf::Music::getLoop>(mrb, ruby_music_class, "looping?");
	MrbWrap::wrap_setter<sf::Music, decltype(&sf::Music::setLoop), &sf::Music::setLoop, bool>(mrb, ruby_music_class, "looping=");

	MrbWrap::wrap_getter<sf::Music, decltype(&sf::Music::getPitch), &sf::Music::getPitch>(mrb, ruby_music_class, "pitch");
	MrbWrap::wrap_setter<sf::Music, decltype(&sf::Music::setPitch), &sf::Music::setPitch, float>(mrb, ruby_music_class, "pitch=");

	MrbWrap::wrap_getter<sf::Music, decltype(&sf::Music::getVolume), &sf::Music::getVolume>(mrb, ruby_music_class, "volume");
	MrbWrap::wrap_setter<sf::Music, decltype(&sf::Music::setVolume), &sf::Music::setVolume, float>(mrb, ruby_music_class, "volume=");

	MrbWrap::wrap_function<sf::Music, decltype(&sf::Music::openFromFile), &sf::Music::openFromFile, std::string>(mrb, ruby_music_class, "open_from_file");

}