#include "Sprite.h"

mrb_value ruby_sprite_init(mrb_state* mrb, mrb_value self) {

	auto a = MrbWrap::convert_to_object<sf::Sprite>(mrb, self);

	return self;

}

mrb_value ruby_sprite_link_texture(mrb_state* mrb, mrb_value self) {

	mrb_value ruby_texture;

	mrb_get_args(mrb, "o", &ruby_texture);

	auto sprite = MrbWrap::convert_from_object<sf::Sprite>(mrb, self);
	auto texture = MrbWrap::convert_from_object<sf::Texture>(mrb, ruby_texture);

	sprite->setTexture(*texture);

	return mrb_true_value();

}

mrb_value ruby_sprite_position(mrb_state* mrb, mrb_value self) {

	auto sprite = MrbWrap::convert_from_object<sf::Sprite>(mrb, self);

	static auto coordinates_class = mrb_class_get_under(mrb, sprite_ruby_module, "Coordinates");

	auto new_coordinates = mrb_obj_new(mrb, coordinates_class, 0, NULL);
	auto new_vector = MrbWrap::convert_from_object<sf::Vector2f>(mrb, new_coordinates);

	*new_vector = sprite->getPosition();

	return new_coordinates;

}

mrb_value ruby_sprite_position_equals(mrb_state* mrb, mrb_value self) {

	mrb_value ruby_coordinates;

	mrb_get_args(mrb, "o", &ruby_coordinates);

	auto sprite = MrbWrap::convert_from_object<sf::Sprite>(mrb, self);
	auto coordinates = MrbWrap::convert_from_object<sf::Vector2f>(mrb, ruby_coordinates);

	sprite->setPosition(*coordinates);

	return ruby_coordinates;

}

mrb_value ruby_sprite_scale(mrb_state* mrb, mrb_value self) {

	auto sprite = MrbWrap::convert_from_object<sf::Sprite>(mrb, self);

	static auto coordinates_class = mrb_class_get_under(mrb, sprite_ruby_module, "Coordinates");

	auto new_coordinates = mrb_obj_new(mrb, coordinates_class, 0, NULL);
	auto new_vector = MrbWrap::convert_from_object<sf::Vector2f>(mrb, new_coordinates);

	*new_vector = sprite->getScale();

	return new_coordinates;

}

mrb_value ruby_sprite_scale_equals(mrb_state* mrb, mrb_value self) {

	mrb_value factors;

	mrb_get_args(mrb, "o", &factors);

	auto sprite = MrbWrap::convert_from_object<sf::Sprite>(mrb, self);

	auto factor_vector = MrbWrap::convert_from_object<sf::Vector2f>(mrb, factors);
	sprite->setScale(*factor_vector);

	return factors;

}

void setup_ruby_class_sprite(mrb_state* mrb, RClass* ruby_module) {

	sprite_ruby_module = ruby_module;

	auto ruby_sprite_class = MrbWrap::define_data_class_under(mrb, "Sprite", ruby_module);

	mrb_define_method(mrb, ruby_sprite_class, "initialize", ruby_sprite_init, MRB_ARGS_NONE());
	
	mrb_define_method(mrb, ruby_sprite_class, "link_texture", ruby_sprite_link_texture, MRB_ARGS_REQ(1));

	mrb_define_method(mrb, ruby_sprite_class, "position", ruby_sprite_position, MRB_ARGS_NONE());
	mrb_define_method(mrb, ruby_sprite_class, "position=", ruby_sprite_position_equals, MRB_ARGS_REQ(1));

	mrb_define_method(mrb, ruby_sprite_class, "scale", ruby_sprite_scale, MRB_ARGS_NONE());
	mrb_define_method(mrb, ruby_sprite_class, "scale=", ruby_sprite_scale_equals, MRB_ARGS_REQ(1));

	//! TODO: Consider implementing origin methods (e.g. 25.0, 25.0 for the example object for scaling)

}