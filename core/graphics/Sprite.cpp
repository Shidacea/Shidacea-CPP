#include "Sprite.h"

void setup_ruby_class_sprite(mrb_state* mrb, RClass* ruby_module) {

	sprite_ruby_module = ruby_module;

	auto ruby_sprite_class = MrbWrap::define_data_class_under(mrb, "Sprite", ruby_module);

	MrbWrap::wrap_constructor<sf::Sprite>(mrb, ruby_sprite_class);

	MrbWrap::define_mruby_function(mrb, ruby_sprite_class, "link_texture", MRUBY_FUNC {

		auto args = MrbWrap::get_args<sf::Vector2f>(mrb);
		auto ruby_texture = std::get<0>(args);

		auto sprite = MrbWrap::convert_from_object<sf::Sprite>(mrb, self);
		auto texture = MrbWrap::convert_from_object<sf::Texture>(mrb, ruby_texture);

		sprite->setTexture(*texture);

		return mrb_true_value();

	});

	MrbWrap::define_mruby_function(mrb, ruby_sprite_class, "position", MRUBY_FUNC {

		auto sprite = MrbWrap::convert_from_object<sf::Sprite>(mrb, self);

		static auto coordinates_class = mrb_class_get_under(mrb, sprite_ruby_module, "Coordinates");

		auto new_coordinates = mrb_obj_new(mrb, coordinates_class, 0, NULL);
		auto new_vector = MrbWrap::convert_from_object<sf::Vector2f>(mrb, new_coordinates);

		*new_vector = sprite->getPosition();

		return new_coordinates;

	});

	MrbWrap::define_mruby_function(mrb, ruby_sprite_class, "position=", MRUBY_FUNC {

		auto args = MrbWrap::get_args<sf::Vector2f>(mrb);
		auto ruby_coordinates = std::get<0>(args);

		auto sprite = MrbWrap::convert_from_object<sf::Sprite>(mrb, self);
		auto coordinates = MrbWrap::convert_from_object<sf::Vector2f>(mrb, ruby_coordinates);

		sprite->setPosition(*coordinates);

		return ruby_coordinates;

	});

	MrbWrap::define_mruby_function(mrb, ruby_sprite_class, "scale", MRUBY_FUNC {

		auto sprite = MrbWrap::convert_from_object<sf::Sprite>(mrb, self);

		static auto coordinates_class = mrb_class_get_under(mrb, sprite_ruby_module, "Coordinates");

		auto new_coordinates = mrb_obj_new(mrb, coordinates_class, 0, NULL);
		auto new_vector = MrbWrap::convert_from_object<sf::Vector2f>(mrb, new_coordinates);

		*new_vector = sprite->getScale();

		return new_coordinates;

	});

	MrbWrap::define_mruby_function(mrb, ruby_sprite_class, "scale=", MRUBY_FUNC {

		auto args = MrbWrap::get_args<sf::Vector2f>(mrb);
		auto factors = std::get<0>(args);

		auto sprite = MrbWrap::convert_from_object<sf::Sprite>(mrb, self);

		auto factor_vector = MrbWrap::convert_from_object<sf::Vector2f>(mrb, factors);
		sprite->setScale(*factor_vector);

		return factors;

	});

	MrbWrap::define_mruby_function(mrb, ruby_sprite_class, "texture_rect", MRUBY_FUNC {

		auto sprite = MrbWrap::convert_from_object<sf::Sprite>(mrb, self);

		static auto int_rect_class = mrb_class_get_under(mrb, sprite_ruby_module, "IntRect");

		auto new_texture_rect = mrb_obj_new(mrb, int_rect_class, 0, NULL);
		auto new_rect = MrbWrap::convert_from_object<sf::IntRect>(mrb, new_texture_rect);

		*new_rect = static_cast<sf::IntRect>(sprite->getTextureRect());

		return new_texture_rect;

	});

	MrbWrap::define_mruby_function(mrb, ruby_sprite_class, "texture_rect=", MRUBY_FUNC {

		auto args = MrbWrap::get_args<sf::IntRect>(mrb);
		auto ruby_rect = std::get<0>(args);

		auto sprite = MrbWrap::convert_from_object<sf::Sprite>(mrb, self);
		auto rect = MrbWrap::convert_from_object<sf::IntRect>(mrb, ruby_rect);

		sprite->setTextureRect(static_cast<sf::IntRect>(*rect));

		return ruby_rect;

	});

	//! TODO: Consider implementing origin methods (e.g. 25.0, 25.0 for the example object for scaling)

}