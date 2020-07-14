#include "Window.h"

void setup_ruby_class_window(mrb_state* mrb, RClass* ruby_module) {

	window_ruby_module = ruby_module;

	// @@@ MRBWRAPDOC_CLASS Window
	// The basic window class everything gets drawn on
	MrbWrap::wrap_class_under<RenderQueueWindow>(mrb, "Window", ruby_module);

	// @@@ MRBWRAPDOC_IM Window initialize title width height fullscreen=false
	// @return [Window]
	// @param title [String]
	// @param width [Integer]
	// @param height [Integer]
	// @param fullscreen [Boolean]
	// Creates a window with the given properties
	MrbWrap::define_member_function(mrb, MrbWrap::get_class_info_ptr<RenderQueueWindow>(), "initialize", MRUBY_FUNC {

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

		window->init_imgui();

		return self;

	}, MRB_ARGS_ARG(3, 1));

	// @@@ MRBWRAPDOC_ATTR Window width Integer r
	// The width of the window
	MrbWrap::wrap_getter<RenderQueueWindow, &RenderQueueWindow::width>(mrb, "width");

	// @@@ MRBWRAPDOC_ATTR Window height Integer r
	// The height of the window
	MrbWrap::wrap_getter<RenderQueueWindow, &RenderQueueWindow::height>(mrb, "height");

	// @@@ MRBWRAPDOC_IM Window clear
	// @return [nil]
	// Clears all content on the window
	MrbWrap::wrap_member_function<RenderQueueWindow, &RenderQueueWindow::clear>(mrb, "clear");

	// @@@ MRBWRAPDOC_IM Window render_and_display
	// @return [nil]
	// Applies the render queue and displays the window
	MrbWrap::wrap_member_function<RenderQueueWindow, &RenderQueueWindow::render_and_display>(mrb, "render_and_display");

	// @@@ MRBWRAPDOC_IM Window imgui_defined?
	// @return [Boolean]
	// Returns true if imgui is active
	MrbWrap::wrap_getter<RenderQueueWindow, &RenderQueueWindow::is_imgui_defined>(mrb, "imgui_defined?");

	// @@@ MRBWRAPDOC_IM Window update_imgui
	// @return [nil]
	// Updates imgui drawing routines
	MrbWrap::wrap_member_function<RenderQueueWindow, &RenderQueueWindow::update_imgui>(mrb, "imgui_update");

	// @@@ MRBWRAPDOC_IM Window set_imgui_scale scale
	// @return [nil]
	// @param scale [Float]
	// Sets the global imgui scale (default 1.0)
	MrbWrap::wrap_setter<RenderQueueWindow, &RenderQueueWindow::set_imgui_scale, float>(mrb, "set_imgui_scale");

	// @@@ MRBWRAPDOC_ATTR Window vertical_sync_enabled Boolean w
	// Uses VSync to display frames at a stable framerate (disabled by default)
	MrbWrap::wrap_setter<RenderQueueWindow, &RenderQueueWindow::set_vsync, bool>(mrb, "vertical_sync_enabled=");

	// @@@ MRBWRAPDOC_IM Window is_open?
	// @return [Boolean]
	// Returns true if the window is open
	MrbWrap::wrap_getter<RenderQueueWindow, &RenderQueueWindow::is_open>(mrb, "is_open?");

	// @@@ MRBWRAPDOC_IM Window close
	// @return [nil]
	// Closes the window
	MrbWrap::wrap_member_function<RenderQueueWindow, &RenderQueueWindow::close>(mrb, "close");

	// @@@ MRBWRAPDOC_IM Window set_view view
	// @return [nil]
	// @param view [View]
	// Sets the current view of the window
	MrbWrap::wrap_member_function<RenderQueueWindow, &RenderQueueWindow::set_view, sf::View>(mrb, "set_view");

	// @@@ MRBWRAPDOC_IM Window has_focus?
	// @return [Boolean]
	// Returns true if the window is focussed
	MrbWrap::wrap_getter<RenderQueueWindow, &RenderQueueWindow::has_focus>(mrb, "has_focus?");

	// @@@ MRBWRAPDOC_ATTR Window visible Boolean w
	// Sets the visibility of the window
	MrbWrap::wrap_setter<RenderQueueWindow, &RenderQueueWindow::set_visible, bool>(mrb, "visible=");

	// @@@ MRBWRAPDOC_IM Window use_view view
	// @return [nil]
	// @param view [View]
	// @yield nil
	// Sets the window view to the given value for the given block
	MrbWrap::define_member_function(mrb, MrbWrap::get_class_info_ptr<RenderQueueWindow>(), "use_view", MRUBY_FUNC {

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

	// @@@ MRBWRAPDOC_IM Window poll_event
	// @return [Event|nil]
	// Polls for an event in the event queue and returns nil otherwise
	MrbWrap::define_member_function(mrb, MrbWrap::get_class_info_ptr<RenderQueueWindow>(), "poll_event", MRUBY_FUNC {

		auto window = MrbWrap::convert_from_object<RenderQueueWindow>(mrb, self);

		static auto event_class = mrb_class_get_under(mrb, window_ruby_module, "Event");
		auto new_event = mrb_obj_new(mrb, event_class, 0, NULL);

		auto event = MrbWrap::convert_from_object<sf::Event>(mrb, new_event);

		auto success = window->poll_event(*event);

		if (success) {

			window->process_imgui_event(event);

			return new_event;

		} else {

			return mrb_nil_value();

		}

	}, MRB_ARGS_NONE());

	// @@@ MRBWRAPDOC_IM Window draw object z render_states=nil
	// @return [true]
	// @param object [Sprite|Text|DrawShape|MapLayer]
	// @param z Float
	// @param render_states [RenderStates|nil]
	// Draws the given object to the window at the given z position
	MrbWrap::define_member_function(mrb, MrbWrap::get_class_info_ptr<RenderQueueWindow>(), "draw", MRUBY_FUNC {

		mrb_value ruby_draw_object;
		mrb_float z_value;
		mrb_value ruby_render_states = mrb_nil_value();

		mrb_get_args(mrb, "of|o", &ruby_draw_object, &z_value, &ruby_render_states);

		auto window = MrbWrap::convert_from_object<RenderQueueWindow>(mrb, self);

		sf::RenderStates render_states = sf::RenderStates::Default;
		if (!mrb_nil_p(ruby_render_states)) render_states = *MrbWrap::convert_from_object<sf::RenderStates>(mrb, ruby_render_states);

		window->draw_object(render_states, mrb, ruby_draw_object, z_value);

		return mrb_true_value();

	}, MRB_ARGS_ARG(2, 1));

	// @@@ MRBWRAPDOC_IM Window draw_translated object z offset render_states=nil
	// @return [true]
	// @param object [Sprite|Text|DrawShape|MapLayer]
	// @param z Float
	// @param offset Coordinates
	// @param render_states [RenderStates|nil]
	// Draws the given object to the window at the given z position with the given offset
	MrbWrap::define_member_function(mrb, MrbWrap::get_class_info_ptr<RenderQueueWindow>(), "draw_translated", MRUBY_FUNC {

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

	}, MRB_ARGS_ARG(3, 1));

}