#include "Music.h"

void setup_ruby_class_music(mrb_state* mrb, RClass* ruby_module) {

	auto ruby_music_class = MrbWrap::define_data_class_under(mrb, "Music", ruby_module);

	MrbWrap::define_mruby_function(mrb, ruby_music_class, "initialize", MRUBY_FUNC {

		MrbWrap::convert_to_object<sf::Music>(mrb, self);
		return self;

	});

	MrbWrap::define_mruby_function(mrb, ruby_music_class, "open_from_file", MRUBY_FUNC {

		char* filename;

		mrb_get_args(mrb, "z", &filename);

		auto music = MrbWrap::convert_from_object<sf::Music>(mrb, self);

		auto return_value = music->openFromFile(std::string(filename));

		//! DEBUG
		music->setLoopPoints(sf::Music::Span(sf::milliseconds(2 * 1000 * 4), sf::milliseconds(2 * 1000 * 4)));

		return mrb_bool_value(return_value);

	}, MRB_ARGS_REQ(1));

	MrbWrap::define_mruby_function(mrb, ruby_music_class, "play", MRUBY_FUNC {

		auto music = MrbWrap::convert_from_object<sf::Music>(mrb, self);
		music->play();

		return mrb_nil_value();

	});

	MrbWrap::define_mruby_function(mrb, ruby_music_class, "stop", MRUBY_FUNC{

		auto music = MrbWrap::convert_from_object<sf::Music>(mrb, self);
		music->stop();

		return mrb_nil_value();

	});

	MrbWrap::define_mruby_function(mrb, ruby_music_class, "pause", MRUBY_FUNC{

		auto music = MrbWrap::convert_from_object<sf::Music>(mrb, self);
		music->pause();

		return mrb_nil_value();

	});

	MrbWrap::define_mruby_function(mrb, ruby_music_class, "looping?", MRUBY_FUNC{

		auto music = MrbWrap::convert_from_object<sf::Music>(mrb, self);

		return mrb_bool_value(music->getLoop());

	});

	MrbWrap::define_mruby_function(mrb, ruby_music_class, "looping=", MRUBY_FUNC{

		mrb_bool should_loop;
		mrb_get_args(mrb, "b", &should_loop);

		auto music = MrbWrap::convert_from_object<sf::Music>(mrb, self);
		music->setLoop(should_loop);

		return mrb_bool_value(should_loop);

	}, MRB_ARGS_REQ(1));

}