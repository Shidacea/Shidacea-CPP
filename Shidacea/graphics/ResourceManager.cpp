#include "ResourceManager.h"

ResourceManager::ResourceManager() {

	//! Reserve some spots to ensure faster access
	//! 10000 should be the absolutely maximal number of sprites in the world
	contents.reserve(10000);

}

ResourceManager::~ResourceManager() {

}

int ResourceManager::add_sprite() {

	if (free_spots.empty()) {

		contents.push_back(std::make_unique<sf::Sprite>());
		return static_cast<int>(contents.size() - 1);

	} else {

		auto index = free_spots.front();
		contents[index] = std::make_unique<sf::Sprite>();
		free_spots.pop();

		return index;

	}
}

void ResourceManager::delete_sprite(int index) {

	contents[index] = nullptr;
	free_spots.push(index);

}

sf::Sprite* ResourceManager::access_sprite(int index) {

	return contents.at(index).get();

}

mrb_value ruby_resource_manager_init(mrb_state* mrb, mrb_value self) {

	MrbWrap::convert_to_object<ResourceManager>(mrb, self);

	return self;

}

void setup_ruby_class_resource_manager(mrb_state* mrb) {

	auto ruby_resource_manager_class = MrbWrap::define_data_class(mrb, "ResourceManager");

	mrb_define_method(mrb, ruby_resource_manager_class, "initialize", ruby_resource_manager_init, MRB_ARGS_NONE());

}