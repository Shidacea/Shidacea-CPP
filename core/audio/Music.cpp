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

	//! TODO: Doesn't work yet
	//MrbWrap::wrap_function<sf::Music, decltype(&sf::Music::openFromFile), &sf::Music::openFromFile, std::string>(mrb, ruby_music_class, "open_from_file");

	MrbWrap::define_mruby_function(mrb, ruby_music_class, "open_from_file", MRUBY_FUNC {

		char* filename;

		mrb_get_args(mrb, "z", &filename);

		auto music = MrbWrap::convert_from_object<sf::Music>(mrb, self);

		auto return_value = music->openFromFile(std::string(filename));

		//! TODO: Convert this to a ruby function
		music->setLoopPoints(sf::Music::Span(sf::milliseconds(2 * 1000 * 4), sf::milliseconds(2 * 1000 * 4)));

		return mrb_bool_value(return_value);

	}, MRB_ARGS_REQ(1));

}