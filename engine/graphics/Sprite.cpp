#include "Sprite.h"

void setup_ruby_class_sprite(mrb_state* mrb, RClass* ruby_module) {

	// @@@ M_CLASS Sprite
	// A sprite class to serve as a wrapper for linked textures with more properties
	MrbWrap::wrap_class_under<sf::Sprite>(mrb, "Sprite", ruby_module);

	// @@@ M_IM Sprite initialize
	// @return [Sprite]
	// Creates an empty sprite object
	MrbWrap::wrap_constructor<sf::Sprite>(mrb);

	// @@@ M_IM Sprite link_texture texture
	// @return [true]
	// @param texture [Texture]
	// Links a texture to this sprite
	MrbWrap::define_member_function(mrb, MrbWrap::get_class_info_ptr<sf::Sprite>(), "link_texture", MRUBY_FUNC {

		auto args = MrbWrap::get_raw_args<sf::Texture>(mrb);
		auto ruby_texture = std::get<0>(args);

		auto sprite = MrbWrap::convert_from_object<sf::Sprite>(mrb, self);
		auto texture = MrbWrap::convert_from_object<sf::Texture>(mrb, ruby_texture);

		sprite->setTexture(*texture);

		return mrb_true_value();

	}, MRB_ARGS_REQ(1));

	// @@@ M_ATTR Sprite position Coordinates rw
	// Position of the sprite
	MrbWrap::wrap_getter<sf::Sprite, &sf::Sprite::getPosition>(mrb, "position");
	MrbWrap::wrap_setter<sf::Sprite, MrbWrap::specify<sf::Transformable, void, const sf::Vector2f&>(&sf::Sprite::setPosition), sf::Vector2f>(mrb, "position=");

	// @@@ M_ATTR Sprite scale Coordinates rw
	// Scale vector of the sprite
	MrbWrap::wrap_getter<sf::Sprite, &sf::Sprite::getScale>(mrb, "scale");
	MrbWrap::wrap_setter<sf::Sprite, MrbWrap::specify<sf::Transformable, void, const sf::Vector2f&>(&sf::Sprite::setScale), sf::Vector2f>(mrb, "scale=");

	// @@@ M_ATTR Sprite texture_rect IntRect rw
	// Texture rectangle of the sprite
	MrbWrap::wrap_getter<sf::Sprite, &sf::Sprite::getTextureRect>(mrb, "texture_rect");
	MrbWrap::wrap_setter<sf::Sprite, &sf::Sprite::setTextureRect, sf::IntRect>(mrb, "texture_rect=");

	// @@@ M_IM Sprite move difference
	// @return [nil]
	// @param difference [Coordinates]
	// Moves the sprite by the given difference
	MrbWrap::wrap_member_function<sf::Sprite, MrbWrap::specify<sf::Transformable, void, const sf::Vector2f&>(&sf::Sprite::move), sf::Vector2f>(mrb, "move");

	// @@@ M_ATTR Sprite rotation Float rw
	// Rotation angle of the sprite in degrees
	MrbWrap::wrap_getter<sf::Sprite, &sf::Sprite::getRotation>(mrb, "rotation");
	MrbWrap::wrap_setter<sf::Sprite, &sf::Sprite::setRotation, float>(mrb, "rotation=");

	// @@@ M_ATTR Sprite origin Coordinates rw
	// Origin vector of the sprite
	MrbWrap::wrap_getter<sf::Sprite, &sf::Sprite::getOrigin>(mrb, "origin");
	MrbWrap::wrap_setter<sf::Sprite, MrbWrap::specify<sf::Transformable, void, const sf::Vector2f&>(&sf::Sprite::setOrigin), sf::Vector2f>(mrb, "origin=");

	// @@@ M_ATTR Sprite color Color rw
	// Color hue of the sprite
	MrbWrap::wrap_getter<sf::Sprite, &sf::Sprite::getColor>(mrb, "color");
	MrbWrap::wrap_setter<sf::Sprite, &sf::Sprite::setColor, sf::Color>(mrb, "color=");

}