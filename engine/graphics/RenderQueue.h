#pragma once

#include <array>
#include <algorithm>

#include <SFML/Graphics.hpp>

constexpr size_t max_z_group = 16;
constexpr size_t max_elements_per_group = 4096;

struct RenderCall {

	sf::Drawable* obj;
	sf::RenderStates states;
	sf::View view;
	
	sf::Vector2f origin;
	sf::Vector2f position;
	sf::Vector2f scale;
	float rotation;

	float z;

};

bool operator<(const RenderCall& first, const RenderCall& second);

class RenderQueue {

public:

	size_t get_z_group(float z);

	void push(sf::Drawable* obj, sf::RenderStates&& states, sf::View view, 
		sf::Vector2f origin, sf::Vector2f position, sf::Vector2f scale, float rotation,
		float z);

	void sort(size_t z_group);
	void reset(size_t z_group);
	RenderCall& get_render_call(size_t z_group, size_t element);

	void draw_to(sf::RenderWindow* window);

	std::array<std::array<RenderCall, max_elements_per_group>, max_z_group> queue;
	std::array<size_t, max_z_group> element_count;
	size_t max_z_used = 0;

	bool invalid = false;

};