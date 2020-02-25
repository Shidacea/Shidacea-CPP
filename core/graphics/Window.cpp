#include "Window.h"

void draw_object(sf::RenderWindow* window, sf::RenderStates& render_states, mrb_state* mrb, mrb_value& draw_object) {

	if (MrbWrap::check_for_type<sf::Sprite>(mrb, draw_object)) {

		auto sprite = MrbWrap::convert_from_object<sf::Sprite>(mrb, draw_object);
		window->draw(*sprite, render_states);

	} else if (MrbWrap::check_for_type<MapLayer>(mrb, draw_object)) {

		auto map_layer = MrbWrap::convert_from_object<MapLayer>(mrb, draw_object);
		window->draw(*map_layer, render_states);

	} else if (MrbWrap::check_for_type<sf::Text>(mrb, draw_object)) {

		auto text = MrbWrap::convert_from_object<sf::Text>(mrb, draw_object);
		auto font = MrbWrap::convert_from_instance_variable<sf::Font>(mrb, draw_object, "@_font");
		text->setFont(*font);
		window->draw(*text, render_states);

	} else {

		//! TODO: Error message

	}

}

void setup_ruby_class_window(mrb_state* mrb, RClass* ruby_module) {

	window_ruby_module = ruby_module;

	MrbWrap::wrap_class_under<sf::RenderWindow>(mrb, "Window", ruby_module);

	auto ruby_window_class = MrbWrap::define_data_class_under(mrb, "Window", ruby_module);

	MrbWrap::define_mruby_function(mrb, ruby_window_class, "initialize", MRUBY_FUNC {

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

		ImGui::SFML::Init(*window);

		return self;

	}, MRB_ARGS_ARG(3, 1));

	MrbWrap::define_mruby_function(mrb, ruby_window_class, "clear", MRUBY_FUNC {

		auto window = MrbWrap::convert_from_object<sf::RenderWindow>(mrb, self);
		window->clear();

		return mrb_nil_value();

	}, MRB_ARGS_NONE());

	MrbWrap::define_mruby_function(mrb, ruby_window_class, "display", MRUBY_FUNC {

		auto window = MrbWrap::convert_from_object<sf::RenderWindow>(mrb, self);

		ImGui::SFML::Render(*window);

		window->display();

		return mrb_nil_value();

	}, MRB_ARGS_NONE());

	MrbWrap::define_mruby_function(mrb, ruby_window_class, "imgui_update", MRUBY_FUNC {

		auto window = MrbWrap::convert_from_object<sf::RenderWindow>(mrb, self);
		auto clock = MrbWrap::convert_from_instance_variable<sf::Clock>(mrb, self, "@_clock");

		ImGui::SFML::Update(*window, clock->restart());

		return mrb_nil_value();

	}, MRB_ARGS_NONE());

	MrbWrap::define_mruby_function(mrb, ruby_window_class, "set_imgui_scale", MRUBY_FUNC {

		auto args = MrbWrap::get_converted_args<float>(mrb);
		auto scale = std::get<0>(args);

		ImGui::GetIO().FontGlobalScale = scale;

		return mrb_nil_value();

	}, MRB_ARGS_REQ(1));

	MrbWrap::wrap_setter<sf::RenderWindow, &sf::RenderWindow::setVerticalSyncEnabled, bool>(mrb, "vertical_sync_enabled=");

	MrbWrap::wrap_getter<sf::RenderWindow, &sf::RenderWindow::isOpen>(mrb, "is_open?");

	MrbWrap::define_mruby_function(mrb, ruby_window_class, "close", MRUBY_FUNC {

		auto window = MrbWrap::convert_from_object<sf::RenderWindow>(mrb, self);
		window->close();

		ImGui::SFML::Shutdown();

		return mrb_nil_value();

	}, MRB_ARGS_NONE());

	MrbWrap::wrap_member_function<sf::RenderWindow, &sf::RenderWindow::setView, sf::View>(mrb, "set_view");

	MrbWrap::define_mruby_function(mrb, ruby_window_class, "use_view", MRUBY_FUNC {

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

	MrbWrap::define_mruby_function(mrb, ruby_window_class, "poll_event", MRUBY_FUNC {

		auto window = MrbWrap::convert_from_object<sf::RenderWindow>(mrb, self);

		static auto event_class = mrb_class_get_under(mrb, window_ruby_module, "Event");
		auto new_event = mrb_obj_new(mrb, event_class, 0, NULL);

		auto event = MrbWrap::convert_from_object<sf::Event>(mrb, new_event);

		auto success = window->pollEvent(*event);

		if (success) {

			ImGui::SFML::ProcessEvent(*event);
			return new_event;

		} else {

			return mrb_nil_value();

		}

	}, MRB_ARGS_NONE());

	MrbWrap::define_mruby_function(mrb, ruby_window_class, "draw", MRUBY_FUNC {

		mrb_value ruby_draw_object;
		mrb_value ruby_render_states = mrb_nil_value();

		mrb_get_args(mrb, "o|o", &ruby_draw_object, &ruby_render_states);

		auto window = MrbWrap::convert_from_object<sf::RenderWindow>(mrb, self);

		sf::RenderStates render_states = sf::RenderStates::Default;
		if (!mrb_nil_p(ruby_render_states)) render_states = *MrbWrap::convert_from_object<sf::RenderStates>(mrb, ruby_render_states);

		draw_object(window, render_states, mrb, ruby_draw_object);

		return mrb_true_value();

	}, MRB_ARGS_ARG(1, 1));

	MrbWrap::define_mruby_function(mrb, ruby_window_class, "draw_translated", MRUBY_FUNC {

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

}