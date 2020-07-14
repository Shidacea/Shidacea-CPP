#include "Music.h"

void setup_ruby_class_music(mrb_state* mrb, RClass* ruby_module) {

	// @@@ MRBWRAPDOC_CLASS Music
	// Music track class
	MrbWrap::wrap_class_under<sf::Music>(mrb, "Music", ruby_module);

	// @@@ MRBWRAPDOC_IM Music initialize
	// @return [Music]
	// Creates a music track (without content)
	MrbWrap::wrap_constructor<sf::Music>(mrb);

	// @@@ MRBWRAPDOC_IM Music play
	// @return [nil]
	// Plays the music track from the beginning or resumes it if paused
	MrbWrap::wrap_member_function<sf::Music, &sf::Music::play>(mrb, "play");

	// @@@ MRBWRAPDOC_IM Music stop
	// @return [nil]
	// Stops the music track if running
	MrbWrap::wrap_member_function<sf::Music, &sf::Music::stop>(mrb, "stop");

	// @@@ MRBWRAPDOC_IM Music pause
	// @return [nil]
	// Pauses the music track if running
	MrbWrap::wrap_member_function<sf::Music, &sf::Music::pause>(mrb, "pause");

	//! Different name for getLoop to clarify meaning

	// @@@ MRBWRAPDOC_ATTR Music looping Boolean rw
	// Looping property of the music track
	MrbWrap::wrap_getter<sf::Music, &sf::Music::getLoop>(mrb, "looping");
	MrbWrap::wrap_setter<sf::Music, &sf::Music::setLoop, bool>(mrb, "looping=");

	// @@@ MRBWRAPDOC_ATTR Music pitch Float rw
	// Pitch of the music track, with default 1.0
	MrbWrap::wrap_getter<sf::Music, &sf::Music::getPitch>(mrb, "pitch");
	MrbWrap::wrap_setter<sf::Music, &sf::Music::setPitch, float>(mrb, "pitch=");

	// @@@ MRBWRAPDOC_ATTR Music volume Float rw
	// Volume of the music track, ranging from 0 to 100 (default)
	MrbWrap::wrap_getter<sf::Music, &sf::Music::getVolume>(mrb, "volume");
	MrbWrap::wrap_setter<sf::Music, &sf::Music::setVolume, float>(mrb, "volume=");

	// @@@ MRBWRAPDOC_IM Music open_from_file filename
	// @return [Boolean]
	// @param filename [String]
	// Loads the music track from file, returning true if loading was successful, else false.
	MrbWrap::wrap_member_function<sf::Music, &sf::Music::openFromFile, MRBW_FILE>(mrb, "open_from_file");

	// TODO: Loops like music->setLoopPoints(sf::Music::Span(sf::milliseconds(2 * 1000 * 4), sf::milliseconds(2 * 1000 * 4)));

}