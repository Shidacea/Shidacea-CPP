#include "RenderQueue.h"

bool operator<(const RenderCall& first, const RenderCall& second) {

	return first.z < second.z;

}

size_t RenderQueue::get_z_group(float z) {

	size_t return_value;

	//! Group 0
	if (z < 0.0) return_value = 0;
	else {

		//! Group max_z_group - 1
		auto int_z = static_cast<size_t>(z);
		if (int_z >= max_z_group - 1) return_value = max_z_group - 1;

		//! Group 1 to max_z_group - 2
		else return_value = int_z + 1;

	}

	if (return_value > max_z_used) max_z_used = return_value;
	return return_value;

}

void RenderQueue::push(sf::Drawable* obj, sf::RenderStates states, sf::View view, float z) {

	auto z_group = get_z_group(z);

	queue[z_group][element_count[z_group]++] = { obj, states, view, z };

}

void RenderQueue::sort(size_t z_group) {

	if(element_count[z_group] > 1) std::stable_sort(queue[z_group].begin(), queue[z_group].begin() + element_count[z_group]);

}

void RenderQueue::reset(size_t z_group) {

	element_count[z_group] = 0;

}

RenderCall& RenderQueue::get_render_call(size_t z_group, size_t element) {

	return queue[z_group][element];

}

void RenderQueue::draw_to(sf::RenderWindow* window) {

	for (size_t z = 0; z <= max_z_used; z++) {

		//! Do exact z-ordering in each z group
		sort(z);

		for (size_t i = 0; i < element_count[z]; i++) {

			auto& render_call = get_render_call(z, i);

			window->setView(render_call.view);

			window->draw(*(render_call.obj), render_call.states);

		}

		//! Reset counters to zero
		reset(z);
	
	}

}