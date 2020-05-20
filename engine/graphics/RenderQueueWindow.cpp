#include "RenderQueueWindow.h"

void RenderQueueWindow::draw_object(sf::RenderStates render_states, mrb_state* mrb, mrb_value& draw_object, float z) {

	if (MrbWrap::check_for_type<sf::Sprite>(mrb, draw_object)) {

		auto sprite = MrbWrap::convert_from_object<sf::Sprite>(mrb, draw_object);
		render_queue.push(sprite, render_states, window->getView(), z);

	}
	else if (MrbWrap::check_for_type<MapLayer>(mrb, draw_object)) {

		auto map_layer = MrbWrap::convert_from_object<MapLayer>(mrb, draw_object);
		render_queue.push(map_layer, render_states, window->getView(), z);

	}
	else if (MrbWrap::check_for_type<sf::Text>(mrb, draw_object)) {

		auto text = MrbWrap::convert_from_object<sf::Text>(mrb, draw_object);
		render_queue.push(text, render_states, window->getView(), z);

	}
	else if (MrbWrap::check_for_type<sf::RectangleShape>(mrb, draw_object)) {

		auto shape = MrbWrap::convert_from_object<sf::RectangleShape>(mrb, draw_object);
		render_queue.push(shape, render_states, window->getView(), z);

	}
	else {

		//! TODO: Error message

	}

}

void RenderQueueWindow::init(sf::VideoMode mode, const sf::String& title, sf::Uint32 style, const sf::ContextSettings& settings) {

	this->window = std::make_unique<sf::RenderWindow>(mode, title, style, settings);

}

bool RenderQueueWindow::is_imgui_defined() {

#ifdef SHIDACEA_EXCLUDE_IMGUI

	return false;

#else

	return true;

#endif

}

void RenderQueueWindow::init_imgui() {

#ifndef SHIDACEA_EXCLUDE_IMGUI

	ImGui::SFML::Init(*window);

#endif

}

void RenderQueueWindow::set_imgui_scale(float scale) {

#ifndef SHIDACEA_EXCLUDE_IMGUI

	ImGui::GetIO().FontGlobalScale = scale;

#endif

}

void RenderQueueWindow::render_imgui() {

#ifndef SHIDACEA_EXCLUDE_IMGUI

	ImGui::SFML::Render(*window);

#endif

}

void RenderQueueWindow::update_imgui() {

#ifndef SHIDACEA_EXCLUDE_IMGUI

	ImGui::SFML::Update(*window, clock.restart());

#endif

}

void RenderQueueWindow::process_imgui_event(sf::Event* event) {

#ifndef SHIDACEA_EXCLUDE_IMGUI

	ImGui::SFML::ProcessEvent(*event);

#endif

}

void RenderQueueWindow::shutdown_imgui() {

#ifndef SHIDACEA_EXCLUDE_IMGUI

	ImGui::SFML::Shutdown();

#endif

}

void RenderQueueWindow::clear() {

	window->clear();

}

void RenderQueueWindow::display() {

	window->display();

}

bool RenderQueueWindow::is_open() {

	return window->isOpen();

}

bool RenderQueueWindow::has_focus() {

	return window->hasFocus();

}

void RenderQueueWindow::set_visible(bool value) {

	window->setVisible(value);

}

void RenderQueueWindow::set_vsync(bool value) {

	window->setVerticalSyncEnabled(value);

}

void RenderQueueWindow::set_view(const sf::View& view) {

	window->setView(view);

}

const sf::View& RenderQueueWindow::get_view() {

	return window->getView();

}

bool RenderQueueWindow::poll_event(sf::Event& event) {

	return window->pollEvent(event);

}

void RenderQueueWindow::close() {

	window->close();
	shutdown_imgui();

}

void RenderQueueWindow::render() {

	render_queue.draw_to(window.get());

}

sf::RenderWindow& RenderQueueWindow::get_window_reference() {

	return *(window.get());

}

void RenderQueueWindow::render_and_display() {

	render();
	render_imgui();
	display();

}