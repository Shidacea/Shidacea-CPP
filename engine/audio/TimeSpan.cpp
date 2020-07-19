#include "Music.h"

void setup_ruby_class_timespan(mrb_state* mrb, RClass* ruby_module) {

	// @@@ M_CLASS TimeSpan
	// Time span class for music tracks
	MrbWrap::wrap_class_under<sf::Music::TimeSpan>(mrb, "TimeSpan", ruby_module);

	// @@@ M_IM TimeSpan initialize offset length
	// @return [TimeSpan]
	// @param offset [Time]
	// @param length [Time]
	// Defines a time span with beginning offset and length
	MrbWrap::wrap_constructor<sf::Music::TimeSpan, sf::Time, sf::Time>(mrb);

}