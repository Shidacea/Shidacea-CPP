#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "Helper.h"

#include "ResourceContainer.h"

class ResourceManager {

public:

	ResourceContainer<sf::Sprite> sprites;

private:

};

void setup_ruby_class_resource_manager(mrb_state* mrb, RClass* ruby_module);