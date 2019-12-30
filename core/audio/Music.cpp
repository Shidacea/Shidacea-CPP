#include "Music.h"

mrb_value ruby_music_init(mrb_state* mrb, mrb_value self) {

	MrbWrap::convert_to_object<sf::Music>(mrb, self);

	return self;

}

mrb_value ruby_music_open_from_file(mrb_state* mrb, mrb_value self) {
	
	char* filename;

	mrb_get_args(mrb, "z", &filename);

	auto music = MrbWrap::convert_from_object<sf::Music>(mrb, self);

	auto return_value = music->openFromFile(std::string(filename));

	//! DEBUG
	music->setLoopPoints(sf::Music::Span(sf::milliseconds(2 * 1000 * 4), sf::milliseconds(2 * 1000 * 4)));

	return mrb_bool_value(return_value);

}

mrb_value ruby_music_play(mrb_state* mrb, mrb_value self) {

	auto music = MrbWrap::convert_from_object<sf::Music>(mrb, self);
	music->play();

	return mrb_nil_value();

}

mrb_value ruby_music_stop(mrb_state* mrb, mrb_value self) {

	auto music = MrbWrap::convert_from_object<sf::Music>(mrb, self);
	music->stop();

	return mrb_nil_value();

}

mrb_value ruby_music_pause(mrb_state* mrb, mrb_value self) {

	auto music = MrbWrap::convert_from_object<sf::Music>(mrb, self);
	music->pause();

	return mrb_nil_value();

}

mrb_value ruby_music_looping(mrb_state* mrb, mrb_value self) {

	auto music = MrbWrap::convert_from_object<sf::Music>(mrb, self);

	return mrb_bool_value(music->getLoop());

}

mrb_value ruby_music_looping_equals(mrb_state* mrb, mrb_value self) {

	mrb_bool should_loop;
	mrb_get_args(mrb, "b", &should_loop);

	auto music = MrbWrap::convert_from_object<sf::Music>(mrb, self);
	music->setLoop(should_loop);

	return mrb_bool_value(should_loop);

}

void setup_ruby_class_music(mrb_state* mrb, RClass* ruby_module) {

	auto ruby_music_class = MrbWrap::define_data_class_under(mrb, "Music", ruby_module);

	mrb_define_method(mrb, ruby_music_class, "initialize", ruby_music_init, MRB_ARGS_NONE());
	mrb_define_method(mrb, ruby_music_class, "open_from_file", ruby_music_open_from_file, MRB_ARGS_REQ(1));
	mrb_define_method(mrb, ruby_music_class, "play", ruby_music_play, MRB_ARGS_NONE());
	mrb_define_method(mrb, ruby_music_class, "stop", ruby_music_stop, MRB_ARGS_NONE());
	mrb_define_method(mrb, ruby_music_class, "pause", ruby_music_pause, MRB_ARGS_NONE());
	mrb_define_method(mrb, ruby_music_class, "looping?", ruby_music_looping, MRB_ARGS_NONE());
	mrb_define_method(mrb, ruby_music_class, "looping=", ruby_music_looping_equals, MRB_ARGS_REQ(1));

}