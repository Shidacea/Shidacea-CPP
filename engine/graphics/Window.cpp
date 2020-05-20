#include "Window.h"

//! TODO: Deglobalize this

#include <array>
#include <algorithm>

struct RenderCall {

	sf::Drawable* obj;
	sf::RenderStates states;
	sf::View view;
	float z;

};

constexpr size_t max_z_group = 64;
constexpr size_t max_items_per_group = 16384;

std::array<std::array<RenderCall, max_items_per_group>, max_z_group> queue;
std::array<size_t, max_z_group> idx;
size_t max_z_used = 0;

bool operator<(const RenderCall& first, const RenderCall& second) {

	return first.z < second.z;

}

size_t group_z(float z) {

	//! Group 0
	if (z < 0.0) return 0;
	
	//! Group max_z_group - 1
	auto int_z = static_cast<size_t>(z);
	if (int_z >= max_z_group - 1) return max_z_group - 1;

	//! Group 1 to max_z_group - 2
	return int_z + 1;

}

void draw_object(sf::RenderWindow* window, sf::RenderStates render_states, mrb_state* mrb, mrb_value& draw_object) {

	if (MrbWrap::check_for_type<sf::Sprite>(mrb, draw_object)) {

		auto float_z = 0.0f;
		auto z = group_z(float_z);
		auto sprite = MrbWrap::convert_from_object<sf::Sprite>(mrb, draw_object);
		queue[z][idx[z]++] = { sprite, render_states, window->getView(), float_z };
		if (z > max_z_used) max_z_used = z;

	} else if (MrbWrap::check_for_type<MapLayer>(mrb, draw_object)) {

		auto float_z = 0.0f;
		auto z = group_z(float_z);
		auto map_layer = MrbWrap::convert_from_object<MapLayer>(mrb, draw_object);
		queue[z][idx[z]++] = { map_layer, render_states, window->getView(), float_z };
		if (z > max_z_used) max_z_used = z;

	} else if (MrbWrap::check_for_type<sf::Text>(mrb, draw_object)) {

		auto float_z = 0.0f;
		auto z = group_z(float_z);
		auto text = MrbWrap::convert_from_object<sf::Text>(mrb, draw_object);
		queue[z][idx[z]++] = { text, render_states, window->getView(), float_z };
		if (z > max_z_used) max_z_used = z;

	} else if (MrbWrap::check_for_type<sf::RectangleShape>(mrb, draw_object)) {

		auto float_z = 0.0f;
		auto z = group_z(float_z);
		auto shape = MrbWrap::convert_from_object<sf::RectangleShape>(mrb, draw_object);
		queue[z][idx[z]++] = { shape, render_states, window->getView(), float_z };
		if (z > max_z_used) max_z_used = z;

	} else {

		//! TODO: Error message

	}

}

void setup_ruby_class_window(mrb_state* mrb, RClass* ruby_module) {

	window_ruby_module = ruby_module;

	MrbWrap::wrap_class_under<sf::RenderWindow>(mrb, "Window", ruby_module);

	auto ruby_window_class = MrbWrap::define_data_class_under(mrb, "Window", ruby_module);

	MrbWrap::define_member_function(mrb, ruby_window_class, "initialize", MRUBY_FUNC {

		auto args = MrbWrap::get_converted_args<std::string, unsigned int, unsigned int, MRBW_OPT<bool, false>>(mrb);
		auto title = std::get<0>(args);
		auto width = std::get<1>(args);
		auto height = std::get<2>(args);
		auto fullscreen = std::get<3>(args);

		sf::RenderWindow* window;

		if (fullscreen) {

			window = MrbWrap::convert_to_object<sf::RenderWindow>(mrb, self, sf::VideoMode(width, height), title, sf::Style::Fullscreen);

		} else {

			window = MrbWrap::convert_to_object<sf::RenderWindow>(mrb, self, sf::VideoMode(width, height), title);

		}

		MrbWrap::convert_to_instance_variable<sf::Clock>(mrb, self, "@_clock");

#ifndef SHIDACEA_EXCLUDE_IMGUI

		ImGui::SFML::Init(*window);

#endif

		return self;

	}, MRB_ARGS_ARG(3, 1));

	MrbWrap::define_member_function(mrb, ruby_window_class, "clear", MRUBY_FUNC {

		auto window = MrbWrap::convert_from_object<sf::RenderWindow>(mrb, self);
		window->clear();

		return mrb_nil_value();

	}, MRB_ARGS_NONE());

	MrbWrap::define_member_function(mrb, ruby_window_class, "display", MRUBY_FUNC {

		auto window = MrbWrap::convert_from_object<sf::RenderWindow>(mrb, self);

		for (size_t z = 0; z <= max_z_used; z++) {

			//! Do exact z-ordering in each z group
			if(idx[z] > 1) std::stable_sort(queue[z].begin(), queue[z].begin() + idx[z]);

			for (size_t i = 0; i < idx[z]; i++) {

				auto& render_call = queue[z][i];

				window->setView(render_call.view);

				window->draw(*(render_call.obj), render_call.states);

			}

			idx[z] = 0;
		}

#ifndef SHIDACEA_EXCLUDE_IMGUI

		ImGui::SFML::Render(*window);

#endif

		window->display();

		return mrb_nil_value();

	}, MRB_ARGS_NONE());

	MrbWrap::define_member_function(mrb, ruby_window_class, "imgui_update", MRUBY_FUNC {

		auto window = MrbWrap::convert_from_object<sf::RenderWindow>(mrb, self);
		auto clock = MrbWrap::convert_from_instance_variable<sf::Clock>(mrb, self, "@_clock");

#ifndef SHIDACEA_EXCLUDE_IMGUI

		ImGui::SFML::Update(*window, clock->restart());

#endif

		return mrb_nil_value();

	}, MRB_ARGS_NONE());

	MrbWrap::define_member_function(mrb, ruby_window_class, "set_imgui_scale", MRUBY_FUNC {

		auto args = MrbWrap::get_converted_args<float>(mrb);
		auto scale = std::get<0>(args);

#ifndef SHIDACEA_EXCLUDE_IMGUI

		ImGui::GetIO().FontGlobalScale = scale;

#endif

		return mrb_nil_value();

	}, MRB_ARGS_REQ(1));

	MrbWrap::wrap_setter<sf::RenderWindow, &sf::RenderWindow::setVerticalSyncEnabled, bool>(mrb, "vertical_sync_enabled=");

	MrbWrap::wrap_getter<sf::RenderWindow, &sf::RenderWindow::isOpen>(mrb, "is_open?");

	MrbWrap::define_member_function(mrb, ruby_window_class, "close", MRUBY_FUNC {

		auto window = MrbWrap::convert_from_object<sf::RenderWindow>(mrb, self);
		window->close();

#ifndef SHIDACEA_EXCLUDE_IMGUI

		ImGui::SFML::Shutdown();

#endif

		return mrb_nil_value();

	}, MRB_ARGS_NONE());

	MrbWrap::wrap_member_function<sf::RenderWindow, &sf::RenderWindow::setView, sf::View>(mrb, "set_view");

	MrbWrap::define_member_function(mrb, ruby_window_class, "use_view", MRUBY_FUNC {

		mrb_value ruby_view;
		mrb_value block = mrb_nil_value();

		mrb_get_args(mrb, "o&", &ruby_view, &block);

		auto window = MrbWrap::convert_from_object<sf::RenderWindow>(mrb, self);
		auto view = MrbWrap::convert_from_object<sf::View>(mrb, ruby_view);

		auto old_view = window->getView();
		window->setView(*view);
		mrb_yield(mrb, block, mrb_nil_value());
		window->setView(old_view);

		return mrb_nil_value();

	}, MRB_ARGS_REQ(2));

	MrbWrap::define_member_function(mrb, ruby_window_class, "poll_event", MRUBY_FUNC {

		auto window = MrbWrap::convert_from_object<sf::RenderWindow>(mrb, self);

		static auto event_class = mrb_class_get_under(mrb, window_ruby_module, "Event");
		auto new_event = mrb_obj_new(mrb, event_class, 0, NULL);

		auto event = MrbWrap::convert_from_object<sf::Event>(mrb, new_event);

		auto success = window->pollEvent(*event);

		if (success) {

#ifndef SHIDACEA_EXCLUDE_IMGUI

			ImGui::SFML::ProcessEvent(*event);
#endif

			return new_event;

		} else {

			return mrb_nil_value();

		}

	}, MRB_ARGS_NONE());

	MrbWrap::define_member_function(mrb, ruby_window_class, "draw", MRUBY_FUNC {

		mrb_value ruby_draw_object;
		mrb_value ruby_render_states = mrb_nil_value();

		mrb_get_args(mrb, "o|o", &ruby_draw_object, &ruby_render_states);

		auto window = MrbWrap::convert_from_object<sf::RenderWindow>(mrb, self);

		sf::RenderStates render_states = sf::RenderStates::Default;
		if (!mrb_nil_p(ruby_render_states)) render_states = *MrbWrap::convert_from_object<sf::RenderStates>(mrb, ruby_render_states);

		draw_object(window, render_states, mrb, ruby_draw_object);

		return mrb_true_value();

	}, MRB_ARGS_ARG(1, 1));

	MrbWrap::define_member_function(mrb, ruby_window_class, "draw_translated", MRUBY_FUNC {

		mrb_value ruby_draw_object;
		mrb_value ruby_coordinates;
		mrb_value ruby_render_states = mrb_nil_value();

		mrb_get_args(mrb, "oo|o", &ruby_draw_object, &ruby_coordinates, &ruby_render_states);

		auto window = MrbWrap::convert_from_object<sf::RenderWindow>(mrb, self);
		auto coordinates = MrbWrap::convert_from_object<sf::Vector2f>(mrb, ruby_coordinates);

		sf::RenderStates render_states = sf::RenderStates::Default;
		if (!mrb_nil_p(ruby_render_states)) render_states = *MrbWrap::convert_from_object<sf::RenderStates>(mrb, ruby_render_states);

		sf::Transform transform;
		transform.translate(*coordinates);
		render_states.transform *= transform;

		draw_object(window, render_states, mrb, ruby_draw_object);

		return mrb_true_value();

	}, MRB_ARGS_ARG(2, 1));

	MrbWrap::wrap_getter<sf::RenderWindow, &sf::RenderWindow::hasFocus>(mrb, "has_focus?");

	MrbWrap::wrap_setter<sf::RenderWindow, &sf::RenderWindow::setVisible, bool>(mrb, "visible=");

	MrbWrap::define_member_function(mrb, ruby_window_class, "imgui_defined?", MRUBY_FUNC {

#ifdef SHIDACEA_EXCLUDE_IMGUI

		return mrb_false_value();

#else

		return mrb_true_value();

#endif

	}, MRB_ARGS_NONE());

}