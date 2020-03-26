#include "Events.h"

void setup_ruby_events(mrb_state* mrb, RClass* ruby_module) {

	auto module_type = mrb_define_module_under(mrb, ruby_module, "EventType");

	REGISTER_TYPE(mrb, module_type, Closed);
	REGISTER_TYPE(mrb, module_type, Resized);
	REGISTER_TYPE(mrb, module_type, LostFocus);
	REGISTER_TYPE(mrb, module_type, GainedFocus);
	REGISTER_TYPE(mrb, module_type, TextEntered);
	REGISTER_TYPE(mrb, module_type, KeyPressed);
	REGISTER_TYPE(mrb, module_type, KeyReleased);
	REGISTER_TYPE(mrb, module_type, MouseWheelMoved);
	REGISTER_TYPE(mrb, module_type, MouseWheelScrolled);
	REGISTER_TYPE(mrb, module_type, MouseButtonPressed);
	REGISTER_TYPE(mrb, module_type, MouseButtonReleased);
	REGISTER_TYPE(mrb, module_type, MouseMoved);
	REGISTER_TYPE(mrb, module_type, MouseEntered);
	REGISTER_TYPE(mrb, module_type, MouseLeft);
	REGISTER_TYPE(mrb, module_type, JoystickButtonPressed);
	REGISTER_TYPE(mrb, module_type, JoystickButtonReleased);
	REGISTER_TYPE(mrb, module_type, JoystickMoved);
	REGISTER_TYPE(mrb, module_type, JoystickConnected);
	REGISTER_TYPE(mrb, module_type, JoystickDisconnected);
	REGISTER_TYPE(mrb, module_type, TouchBegan);
	REGISTER_TYPE(mrb, module_type, TouchMoved);
	REGISTER_TYPE(mrb, module_type, TouchEnded);
	REGISTER_TYPE(mrb, module_type, SensorChanged);

	auto module_key = mrb_define_module_under(mrb, ruby_module, "EventKey");

	REGISTER_KEY(mrb, module_key, Unknown);

	REGISTER_KEY(mrb, module_key, A);
	REGISTER_KEY(mrb, module_key, B);
	REGISTER_KEY(mrb, module_key, C);
	REGISTER_KEY(mrb, module_key, D);
	REGISTER_KEY(mrb, module_key, E);
	REGISTER_KEY(mrb, module_key, F);
	REGISTER_KEY(mrb, module_key, G);
	REGISTER_KEY(mrb, module_key, H);
	REGISTER_KEY(mrb, module_key, I);
	REGISTER_KEY(mrb, module_key, J);
	REGISTER_KEY(mrb, module_key, K);
	REGISTER_KEY(mrb, module_key, L);
	REGISTER_KEY(mrb, module_key, M);
	REGISTER_KEY(mrb, module_key, N);
	REGISTER_KEY(mrb, module_key, O);
	REGISTER_KEY(mrb, module_key, P);
	REGISTER_KEY(mrb, module_key, Q);
	REGISTER_KEY(mrb, module_key, R);
	REGISTER_KEY(mrb, module_key, S);
	REGISTER_KEY(mrb, module_key, T);
	REGISTER_KEY(mrb, module_key, U);
	REGISTER_KEY(mrb, module_key, V);
	REGISTER_KEY(mrb, module_key, W);
	REGISTER_KEY(mrb, module_key, X);
	REGISTER_KEY(mrb, module_key, Y);
	REGISTER_KEY(mrb, module_key, Z);

	REGISTER_KEY(mrb, module_key, Num0);
	REGISTER_KEY(mrb, module_key, Num1);
	REGISTER_KEY(mrb, module_key, Num2);
	REGISTER_KEY(mrb, module_key, Num3);
	REGISTER_KEY(mrb, module_key, Num4);
	REGISTER_KEY(mrb, module_key, Num5);
	REGISTER_KEY(mrb, module_key, Num6);
	REGISTER_KEY(mrb, module_key, Num7);
	REGISTER_KEY(mrb, module_key, Num8);
	REGISTER_KEY(mrb, module_key, Num9);

	REGISTER_KEY(mrb, module_key, Escape);
	REGISTER_KEY(mrb, module_key, LControl);
	REGISTER_KEY(mrb, module_key, LShift);
	REGISTER_KEY(mrb, module_key, LAlt);
	REGISTER_KEY(mrb, module_key, LSystem);
	REGISTER_KEY(mrb, module_key, RControl);
	REGISTER_KEY(mrb, module_key, RShift);
	REGISTER_KEY(mrb, module_key, RAlt);
	REGISTER_KEY(mrb, module_key, RSystem);
	REGISTER_KEY(mrb, module_key, Menu);

	REGISTER_KEY(mrb, module_key, LBracket);
	REGISTER_KEY(mrb, module_key, RBracket);
	REGISTER_KEY(mrb, module_key, Semicolon);
	REGISTER_KEY(mrb, module_key, Comma);
	REGISTER_KEY(mrb, module_key, Period);
	REGISTER_KEY(mrb, module_key, Quote);
	REGISTER_KEY(mrb, module_key, Slash);
	REGISTER_KEY(mrb, module_key, Backslash);
	REGISTER_KEY(mrb, module_key, Tilde);
	REGISTER_KEY(mrb, module_key, Equal);
	REGISTER_KEY(mrb, module_key, Hyphen);

	REGISTER_KEY(mrb, module_key, Space);
	REGISTER_KEY(mrb, module_key, Enter);
	REGISTER_KEY(mrb, module_key, Backspace);
	REGISTER_KEY(mrb, module_key, Tab);

	REGISTER_KEY(mrb, module_key, PageUp);
	REGISTER_KEY(mrb, module_key, PageDown);
	REGISTER_KEY(mrb, module_key, End);
	REGISTER_KEY(mrb, module_key, Home);
	REGISTER_KEY(mrb, module_key, Insert);
	REGISTER_KEY(mrb, module_key, Delete);

	REGISTER_KEY(mrb, module_key, Add);
	REGISTER_KEY(mrb, module_key, Subtract);
	REGISTER_KEY(mrb, module_key, Multiply);
	REGISTER_KEY(mrb, module_key, Divide);

	REGISTER_KEY(mrb, module_key, Left);
	REGISTER_KEY(mrb, module_key, Right);
	REGISTER_KEY(mrb, module_key, Up);
	REGISTER_KEY(mrb, module_key, Down);

	REGISTER_KEY(mrb, module_key, Numpad0);
	REGISTER_KEY(mrb, module_key, Numpad1);
	REGISTER_KEY(mrb, module_key, Numpad2);
	REGISTER_KEY(mrb, module_key, Numpad3);
	REGISTER_KEY(mrb, module_key, Numpad4);
	REGISTER_KEY(mrb, module_key, Numpad5);
	REGISTER_KEY(mrb, module_key, Numpad6);
	REGISTER_KEY(mrb, module_key, Numpad7);
	REGISTER_KEY(mrb, module_key, Numpad8);
	REGISTER_KEY(mrb, module_key, Numpad9);

	REGISTER_KEY(mrb, module_key, F1);
	REGISTER_KEY(mrb, module_key, F2);
	REGISTER_KEY(mrb, module_key, F3);
	REGISTER_KEY(mrb, module_key, F4);
	REGISTER_KEY(mrb, module_key, F5);
	REGISTER_KEY(mrb, module_key, F6);
	REGISTER_KEY(mrb, module_key, F7);
	REGISTER_KEY(mrb, module_key, F8);
	REGISTER_KEY(mrb, module_key, F9);
	REGISTER_KEY(mrb, module_key, F10);
	REGISTER_KEY(mrb, module_key, F11);
	REGISTER_KEY(mrb, module_key, F12);
	REGISTER_KEY(mrb, module_key, F13);
	REGISTER_KEY(mrb, module_key, F14);
	REGISTER_KEY(mrb, module_key, F15);

	REGISTER_KEY(mrb, module_key, Pause);

	mrb_define_module_function(mrb, module_key, "is_pressed?", MRUBY_FUNC {

		auto args = MrbWrap::get_converted_args<int>(mrb);
		auto key_value = std::get<0>(args);

		return mrb_bool_value(sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(key_value)));
		
	}, MRB_ARGS_REQ(1));

	auto module_mouse = mrb_define_module_under(mrb, ruby_module, "EventMouse");

	mrb_define_module_function(mrb, module_mouse, "get_position", MRUBY_FUNC {
		
		mrb_value ruby_window = mrb_nil_value();

		mrb_get_args(mrb, "|o", &ruby_window);

		sf::Vector2i mouse_position;

		if (mrb_nil_p(ruby_window)) {

			mouse_position = sf::Mouse::getPosition();

		} else {

			auto window = MrbWrap::convert_from_object<sf::RenderWindow>(mrb, ruby_window);

			mouse_position = sf::Mouse::getPosition(*window);

		}

		auto position_array = mrb_assoc_new(mrb, mrb_fixnum_value(mouse_position.x), mrb_fixnum_value(mouse_position.y));

		return position_array;

	}, MRB_ARGS_OPT(1));

	mrb_define_module_function(mrb, module_mouse, "get_coordinates", MRUBY_FUNC{

		mrb_value ruby_window;

		mrb_get_args(mrb, "o", &ruby_window);

		auto window = MrbWrap::convert_from_object<sf::RenderWindow>(mrb, ruby_window);

		auto coords = window->mapPixelToCoords(sf::Mouse::getPosition(*window));

		auto ruby_coordinates_class = MrbWrap::get_class_info_ptr<sf::Vector2f>();

		auto ruby_coords = mrb_obj_new(mrb, ruby_coordinates_class, 0, NULL);
		auto converted_coords = MrbWrap::convert_from_object<sf::Vector2f>(mrb, ruby_coords);

		*converted_coords = coords;

		return ruby_coords;

	}, MRB_ARGS_REQ(1));

	mrb_define_module_function(mrb, module_mouse, "is_button_pressed?", MRUBY_FUNC {

		auto args = MrbWrap::get_converted_args<int>(mrb);
		auto button_value = std::get<0>(args);

		return mrb_bool_value(sf::Mouse::isButtonPressed(static_cast<sf::Mouse::Button>(button_value)));

	}, MRB_ARGS_REQ(1));

	mrb_define_module_function(mrb, module_mouse, "set_position", MRUBY_FUNC {

		mrb_value val;
		mrb_value ruby_window = mrb_nil_value();

		mrb_get_args(mrb, "A|o", &val, &ruby_window);

		auto x = mrb_fixnum(mrb_ary_entry(val, 0));
		auto y = mrb_fixnum(mrb_ary_entry(val, 1));

		auto new_position = sf::Vector2i(static_cast<int>(x), static_cast<int>(y));

		if (mrb_nil_p(ruby_window)) {

			sf::Mouse::setPosition(new_position);

		} else {

			auto window = MrbWrap::convert_from_object<sf::RenderWindow>(mrb, ruby_window);

			sf::Mouse::setPosition(new_position, *window);

		}

		return mrb_nil_value();

	}, MRB_ARGS_ARG(1, 1));

	REGISTER_BUTTON(mrb, module_mouse, Left);
	REGISTER_BUTTON(mrb, module_mouse, Right);
	REGISTER_BUTTON(mrb, module_mouse, Middle);

	REGISTER_BUTTON(mrb, module_mouse, XButton1);
	REGISTER_BUTTON(mrb, module_mouse, XButton2);

	REGISTER_WHEEL(mrb, module_mouse, VerticalWheel);
	REGISTER_WHEEL(mrb, module_mouse, HorizontalWheel);

}

void setup_ruby_class_event(mrb_state* mrb, RClass* ruby_module) {

	auto ruby_event_class = MrbWrap::define_data_class_under(mrb, "Event", ruby_module);

	MrbWrap::wrap_class_under<sf::Event>(mrb, "Event", ruby_module);

	MrbWrap::wrap_constructor<sf::Event>(mrb);

	MrbWrap::define_mruby_function(mrb, ruby_event_class, "type", MRUBY_FUNC {

		auto event = MrbWrap::convert_from_object<sf::Event>(mrb, self);

		return mrb_fixnum_value(static_cast<int>(event->type));

	}, MRB_ARGS_NONE());

	MrbWrap::define_mruby_function(mrb, ruby_event_class, "key_code", MRUBY_FUNC {

		auto event = MrbWrap::convert_from_object<sf::Event>(mrb, self);

		return mrb_fixnum_value(static_cast<int>(event->key.code));

	}, MRB_ARGS_NONE());

	MrbWrap::define_mruby_function(mrb, ruby_event_class, "key_alt?", MRUBY_FUNC {

		auto event = MrbWrap::convert_from_object<sf::Event>(mrb, self);

		return mrb_bool_value(event->key.alt);

	}, MRB_ARGS_NONE());

	MrbWrap::define_mruby_function(mrb, ruby_event_class, "key_control?", MRUBY_FUNC {

		auto event = MrbWrap::convert_from_object<sf::Event>(mrb, self);

		return mrb_bool_value(event->key.control);

	}, MRB_ARGS_NONE());

	MrbWrap::define_mruby_function(mrb, ruby_event_class, "key_shift?", MRUBY_FUNC {

		auto event = MrbWrap::convert_from_object<sf::Event>(mrb, self);

		return mrb_bool_value(event->key.shift);

	}, MRB_ARGS_NONE());

	MrbWrap::define_mruby_function(mrb, ruby_event_class, "key_system?", MRUBY_FUNC {

		auto event = MrbWrap::convert_from_object<sf::Event>(mrb, self);

		return mrb_bool_value(event->key.system);

	}, MRB_ARGS_NONE());

	MrbWrap::define_mruby_function(mrb, ruby_event_class, "mouse_button_code", MRUBY_FUNC {

		auto event = MrbWrap::convert_from_object<sf::Event>(mrb, self);

		return mrb_fixnum_value(static_cast<int>(event->mouseButton.button));

	}, MRB_ARGS_NONE());

	MrbWrap::define_mruby_function(mrb, ruby_event_class, "mouse_button_x", MRUBY_FUNC {

		auto event = MrbWrap::convert_from_object<sf::Event>(mrb, self);

		return mrb_fixnum_value(event->mouseButton.x);

	}, MRB_ARGS_NONE());

	MrbWrap::define_mruby_function(mrb, ruby_event_class, "mouse_button_y", MRUBY_FUNC {

		auto event = MrbWrap::convert_from_object<sf::Event>(mrb, self);

		return mrb_fixnum_value(event->mouseButton.y);

	}, MRB_ARGS_NONE());

	MrbWrap::define_mruby_function(mrb, ruby_event_class, "mouse_move_x", MRUBY_FUNC {

		auto event = MrbWrap::convert_from_object<sf::Event>(mrb, self);

		return mrb_fixnum_value(event->mouseMove.x);

	}, MRB_ARGS_NONE());

	MrbWrap::define_mruby_function(mrb, ruby_event_class, "mouse_move_y", MRUBY_FUNC {

		auto event = MrbWrap::convert_from_object<sf::Event>(mrb, self);

		return mrb_fixnum_value(event->mouseMove.y);

	}, MRB_ARGS_NONE());

	MrbWrap::define_mruby_function(mrb, ruby_event_class, "mouse_scroll_wheel", MRUBY_FUNC {

		auto event = MrbWrap::convert_from_object<sf::Event>(mrb, self);

		return mrb_fixnum_value(static_cast<mrb_int>(event->mouseWheelScroll.wheel));

	}, MRB_ARGS_NONE());

	MrbWrap::define_mruby_function(mrb, ruby_event_class, "mouse_scroll_delta", MRUBY_FUNC {

		auto event = MrbWrap::convert_from_object<sf::Event>(mrb, self);

		return mrb_float_value(mrb, event->mouseWheelScroll.delta);

	}, MRB_ARGS_NONE());

	MrbWrap::define_mruby_function(mrb, ruby_event_class, "mouse_scroll_x", MRUBY_FUNC {

		auto event = MrbWrap::convert_from_object<sf::Event>(mrb, self);

		return mrb_fixnum_value(event->mouseWheelScroll.x);

	}, MRB_ARGS_NONE());

	MrbWrap::define_mruby_function(mrb, ruby_event_class, "mouse_scroll_y", MRUBY_FUNC {

		auto event = MrbWrap::convert_from_object<sf::Event>(mrb, self);

		return mrb_fixnum_value(event->mouseWheelScroll.y);

	}, MRB_ARGS_NONE());

}