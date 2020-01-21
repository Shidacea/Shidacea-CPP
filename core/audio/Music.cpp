#include "Music.h"

void setup_ruby_class_music(mrb_state* mrb, RClass* ruby_module) {

	auto ruby_music_class = MrbWrap::define_data_class_under(mrb, "Music", ruby_module);

	MrbWrap::wrap_constructor<sf::Music>(mrb, ruby_music_class);

	MrbWrap::wrap_function<sf::Music, void, decltype(&sf::Music::play), &sf::Music::play>(mrb, ruby_music_class, "play");
	MrbWrap::wrap_function<sf::Music, void, decltype(&sf::Music::stop), &sf::Music::stop>(mrb, ruby_music_class, "stop");
	MrbWrap::wrap_function<sf::Music, void, decltype(&sf::Music::pause), &sf::Music::pause>(mrb, ruby_music_class, "pause");

	MrbWrap::wrap_getter<sf::Music, mrb_bool, decltype(&sf::Music::getLoop), &sf::Music::getLoop>(mrb, ruby_music_class, "looping?");
	MrbWrap::wrap_setter<sf::Music, mrb_bool, bool, decltype(&sf::Music::setLoop), &sf::Music::setLoop>(mrb, ruby_music_class, "looping=");

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