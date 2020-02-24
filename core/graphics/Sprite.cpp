#include "Sprite.h"

void setup_ruby_class_sprite(mrb_state* mrb, RClass* ruby_module) {

	sprite_ruby_module = ruby_module;

	MrbWrap::wrap_class_under<sf::Sprite>(mrb, "Sprite", ruby_module);

	MrbWrap::wrap_constructor<sf::Sprite>(mrb);

	MrbWrap::define_mruby_function(mrb, MrbWrap::get_class_info_ptr<sf::Sprite>(), "link_texture", MRUBY_FUNC {

		auto args = MrbWrap::get_raw_args<sf::Vector2f>(mrb);
		auto ruby_texture = std::get<0>(args);

		auto sprite = MrbWrap::convert_from_object<sf::Sprite>(mrb, self);
		auto texture = MrbWrap::convert_from_object<sf::Texture>(mrb, ruby_texture);

		sprite->setTexture(*texture);

		return mrb_true_value();

	});

	MrbWrap::wrap_getter<sf::Sprite, &sf::Sprite::getPosition>(mrb, "position");
	MrbWrap::wrap_setter<sf::Sprite, MrbWrap::specify<sf::Transformable, void, const sf::Vector2f&>(&sf::Sprite::setPosition), sf::Vector2f>(mrb, "position=");

	MrbWrap::wrap_getter<sf::Sprite, &sf::Sprite::getScale>(mrb, "scale");
	MrbWrap::wrap_setter<sf::Sprite, MrbWrap::specify<sf::Transformable, void, const sf::Vector2f&>(&sf::Sprite::setScale), sf::Vector2f>(mrb, "scale=");

	MrbWrap::wrap_getter<sf::Sprite, &sf::Sprite::getTextureRect>(mrb, "texture_rect");
	MrbWrap::wrap_setter<sf::Sprite, &sf::Sprite::setTextureRect, sf::IntRect>(mrb, "texture_rect=");

	//! TODO: Consider implementing origin methods (e.g. 25.0, 25.0 for the example object for scaling)

}