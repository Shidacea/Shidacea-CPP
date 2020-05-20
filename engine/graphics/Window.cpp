#include "Window.h"

void setup_ruby_class_window(mrb_state* mrb, RClass* ruby_module) {

	window_ruby_module = ruby_module;

	MrbWrap::wrap_class_under<RenderQueueWindow>(mrb, "Window", ruby_module);

	auto ruby_window_class = MrbWrap::define_data_class_under(mrb, "Window", ruby_module);

	MrbWrap::define_member_function(mrb, ruby_window_class, "initialize", MRUBY_FUNC {

		auto args = MrbWrap::get_converted_args<std::string, unsigned int, unsigned int, MRBW_OPT<bool, false>>(mrb);
		auto title = std::get<0>(args);
		auto width = std::get<1>(args);
		auto height = std::get<2>(args);
		auto fullscreen = std::get<3>(args);

		auto window = MrbWrap::convert_to_object<RenderQueueWindow>(mrb, self);

		if (fullscreen) {

			window->init(sf::VideoMode(width, height), title, sf::Style::Fullscreen);

		} else {

			window->init(sf::VideoMode(width, height), title);

		}

		MrbWrap::convert_to_instance_variable<sf::Clock>(mrb, self, "@_clock");

		window->init_imgui_if_available();

		return self;

	}, MRB_ARGS_ARG(3, 1));

	MrbWrap::define_member_function(mrb, ruby_window_class, "clear", MRUBY_FUNC {

		auto window = MrbWrap::convert_from_object<RenderQueueWindow>(mrb, self);
		window->clear();

		return mrb_nil_value();

	}, MRB_ARGS_NONE());

	MrbWrap::define_member_function(mrb, ruby_window_class, "display", MRUBY_FUNC {

		auto window = MrbWrap::convert_from_object<RenderQueueWindow>(mrb, self);

		window->render();
		
		window->render_imgui_if_available();

		window->display();

		return mrb_nil_value();

	}, MRB_ARGS_NONE());

	MrbWrap::define_member_function(mrb, ruby_window_class, "imgui_update", MRUBY_FUNC {

		auto window = MrbWrap::convert_from_object<RenderQueueWindow>(mrb, self);
		auto clock = MrbWrap::convert_from_instance_variable<sf::Clock>(mrb, self, "@_clock");

		window->update_imgui_if_available(clock);

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

	MrbWrap::wrap_setter<RenderQueueWindow, &RenderQueueWindow::set_vsync, bool>(mrb, "vertical_sync_enabled=");

	MrbWrap::wrap_getter<RenderQueueWindow, &RenderQueueWindow::is_open>(mrb, "is_open?");

	MrbWrap::define_member_function(mrb, ruby_window_class, "close", MRUBY_FUNC {

		auto window = MrbWrap::convert_from_object<RenderQueueWindow>(mrb, self);
		window->close();

		window->shutdown_imgui_if_available();

		return mrb_nil_value();

	}, MRB_ARGS_NONE());

	MrbWrap::wrap_member_function<RenderQueueWindow, &RenderQueueWindow::set_view, sf::View>(mrb, "set_view");

	MrbWrap::define_member_function(mrb, ruby_window_class, "use_view", MRUBY_FUNC {

		mrb_value ruby_view;
		mrb_value block = mrb_nil_value();

		mrb_get_args(mrb, "o&", &ruby_view, &block);

		auto window = MrbWrap::convert_from_object<RenderQueueWindow>(mrb, self);
		auto view = MrbWrap::convert_from_object<sf::View>(mrb, ruby_view);

		auto old_view = window->get_view();
		window->set_view(*view);
		mrb_yield(mrb, block, mrb_nil_value());
		window->set_view(old_view);

		return mrb_nil_value();

	}, MRB_ARGS_REQ(2));

	MrbWrap::define_member_function(mrb, ruby_window_class, "poll_event", MRUBY_FUNC {

		auto window = MrbWrap::convert_from_object<RenderQueueWindow>(mrb, self);

		static auto event_class = mrb_class_get_under(mrb, window_ruby_module, "Event");
		auto new_event = mrb_obj_new(mrb, event_class, 0, NULL);

		auto event = MrbWrap::convert_from_object<sf::Event>(mrb, new_event);

		auto success = window->poll_event(*event);

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
		mrb_float z_value;
		mrb_value ruby_render_states = mrb_nil_value();

		mrb_get_args(mrb, "of|o", &ruby_draw_object, &z_value, &ruby_render_states);

		auto window = MrbWrap::convert_from_object<RenderQueueWindow>(mrb, self);

		sf::RenderStates render_states = sf::RenderStates::Default;
		if (!mrb_nil_p(ruby_render_states)) render_states = *MrbWrap::convert_from_object<sf::RenderStates>(mrb, ruby_render_states);

		window->draw_object(render_states, mrb, ruby_draw_object, z_value);

		return mrb_true_value();

	}, MRB_ARGS_ARG(1, 1));

	MrbWrap::define_member_function(mrb, ruby_window_class, "draw_translated", MRUBY_FUNC {

		mrb_value ruby_draw_object;
		mrb_float z_value;
		mrb_value ruby_coordinates;
		mrb_value ruby_render_states = mrb_nil_value();

		mrb_get_args(mrb, "ofo|o", &ruby_draw_object, &z_value, &ruby_coordinates, &ruby_render_states);

		auto window = MrbWrap::convert_from_object<RenderQueueWindow>(mrb, self);
		auto coordinates = MrbWrap::convert_from_object<sf::Vector2f>(mrb, ruby_coordinates);

		sf::RenderStates render_states = sf::RenderStates::Default;
		if (!mrb_nil_p(ruby_render_states)) render_states = *MrbWrap::convert_from_object<sf::RenderStates>(mrb, ruby_render_states);

		sf::Transform transform;
		transform.translate(*coordinates);
		render_states.transform *= transform;

		window->draw_object(render_states, mrb, ruby_draw_object, z_value);

		return mrb_true_value();

	}, MRB_ARGS_ARG(2, 1));

	MrbWrap::wrap_getter<RenderQueueWindow, &RenderQueueWindow::has_focus>(mrb, "has_focus?");

	MrbWrap::wrap_setter<RenderQueueWindow, &RenderQueueWindow::set_visible, bool>(mrb, "visible=");

	MrbWrap::define_member_function(mrb, ruby_window_class, "imgui_defined?", MRUBY_FUNC {

#ifdef SHIDACEA_EXCLUDE_IMGUI

		return mrb_false_value();

#else

		return mrb_true_value();

#endif

	}, MRB_ARGS_NONE());

}