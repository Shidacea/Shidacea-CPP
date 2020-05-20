#pragma once

#include "MrbWrap.h"

#include <SFML/Graphics.hpp>

#ifndef SHIDACEA_EXCLUDE_IMGUI

#include "imgui.h"
#include "imgui-SFML.h"

#endif

#include "Sprite.h"
#include "MapLayer.h"
#include "DrawShape.h"
#include "RenderQueue.h"

//! Special class combining a render window and a render queue

class RenderQueueWindow {

public:

	RenderQueueWindow() = default;
	~RenderQueueWindow() = default;

	void init(sf::VideoMode mode, const sf::String& title, sf::Uint32 style = sf::Style::Default, const sf::ContextSettings& settings = sf::ContextSettings());
	void draw_object(sf::RenderStates render_states, mrb_state* mrb, mrb_value& draw_object, float z);

	void init_imgui_if_available();
	void render_imgui_if_available();
	void update_imgui_if_available(sf::Clock* clock);
	void shutdown_imgui_if_available();

	void clear();
	void display();

	bool is_open();

	bool has_focus();
	void set_visible(bool value);
	
	void set_vsync(bool value);

	void set_view(const sf::View& view);
	const sf::View& get_view();

	bool poll_event(sf::Event& event);

	void close();

	void render();

	sf::RenderWindow& get_window_reference();

private:

	std::unique_ptr<sf::RenderWindow> window = nullptr;
	RenderQueue render_queue;

};