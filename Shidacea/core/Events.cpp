#include "Events.h"

void setup_ruby_events(mrb_state* mrb) {

	auto module_type = mrb_define_module(mrb, "EventType");

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

	auto module_key = mrb_define_module(mrb, "EventKey");

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

	mrb_define_module_function(mrb, module_key, "is_pressed?", ruby_event_key_is_pressed, MRB_ARGS_REQ(1));

	auto module_mouse = mrb_define_module(mrb, "EventMouse");

	mrb_define_module_function(mrb, module_mouse, "get_position", ruby_event_mouse_get_position, MRB_ARGS_OPT(1));
	mrb_define_module_function(mrb, module_mouse, "is_button_pressed?", ruby_event_mouse_is_button_pressed, MRB_ARGS_REQ(1));
	mrb_define_module_function(mrb, module_mouse, "set_position", ruby_event_mouse_set_position, MRB_ARGS_ARG(1, 1));

	REGISTER_BUTTON(mrb, module_mouse, Left);
	REGISTER_BUTTON(mrb, module_mouse, Right);
	REGISTER_BUTTON(mrb, module_mouse, Middle);

	REGISTER_BUTTON(mrb, module_mouse, XButton1);
	REGISTER_BUTTON(mrb, module_mouse, XButton2);

	REGISTER_WHEEL(mrb, module_mouse, VerticalWheel);
	REGISTER_WHEEL(mrb, module_mouse, HorizontalWheel);

}

mrb_value ruby_event_key_is_pressed(mrb_state* mrb, mrb_value self) {

	int key_value;

	mrb_get_args(mrb, "i", &key_value);

	return mrb_bool_value(sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(key_value)));

}

mrb_value ruby_event_mouse_get_position(mrb_state* mrb, mrb_value self) {

	mrb_value ruby_window = mrb_nil_value();

	mrb_get_args(mrb, "|o", &ruby_window);

	sf::Vector2i mouse_position;

	if(mrb_nil_p(ruby_window)) {

		mouse_position = sf::Mouse::getPosition();

	} else {

		auto window = MrbWrap::convert_from_object<sf::RenderWindow>(mrb, ruby_window);

		mouse_position = sf::Mouse::getPosition(*window);

	}

	auto position_array = mrb_assoc_new(mrb, mrb_fixnum_value(mouse_position.x), mrb_fixnum_value(mouse_position.y));

	return position_array;

}

mrb_value ruby_event_mouse_is_button_pressed(mrb_state* mrb, mrb_value self) {

	int button_value;

	mrb_get_args(mrb, "i", &button_value);

	return mrb_bool_value(sf::Mouse::isButtonPressed(static_cast<sf::Mouse::Button>(button_value)));

}

mrb_value ruby_event_mouse_set_position(mrb_state* mrb, mrb_value self) {

	mrb_value val;
	mrb_value ruby_window = mrb_nil_value();

	mrb_get_args(mrb, "A|o", &val, &ruby_window);

	auto x = mrb_fixnum(mrb_ary_entry(val, 0));
	auto y = mrb_fixnum(mrb_ary_entry(val, 1));

	auto new_position = sf::Vector2i(x, y);

	if(mrb_nil_p(ruby_window)) {

		sf::Mouse::setPosition(new_position);

	} else {

		auto window = MrbWrap::convert_from_object<sf::RenderWindow>(mrb, ruby_window);

		sf::Mouse::setPosition(new_position, *window);

	}

	return mrb_nil_value();

}

mrb_value ruby_event_init(mrb_state* mrb, mrb_value self) {

	MrbWrap::convert_to_object<sf::Event>(mrb, self);

	return self;

}

mrb_value ruby_event_type(mrb_state* mrb, mrb_value self) {

	auto event = MrbWrap::convert_from_object<sf::Event>(mrb, self);

	return mrb_fixnum_value(static_cast<int>(event->type));

}

mrb_value ruby_event_key_code(mrb_state* mrb, mrb_value self) {

	auto event = MrbWrap::convert_from_object<sf::Event>(mrb, self);

	return mrb_fixnum_value(static_cast<int>(event->key.code));

}

mrb_value ruby_event_key_alt(mrb_state* mrb, mrb_value self) {

	auto event = MrbWrap::convert_from_object<sf::Event>(mrb, self);

	return mrb_bool_value(event->key.alt);

}

mrb_value ruby_event_key_control(mrb_state* mrb, mrb_value self) {

	auto event = MrbWrap::convert_from_object<sf::Event>(mrb, self);

	return mrb_bool_value(event->key.control);

}

mrb_value ruby_event_key_shift(mrb_state* mrb, mrb_value self) {

	auto event = MrbWrap::convert_from_object<sf::Event>(mrb, self);

	return mrb_bool_value(event->key.shift);

}

mrb_value ruby_event_key_system(mrb_state* mrb, mrb_value self) {

	auto event = MrbWrap::convert_from_object<sf::Event>(mrb, self);

	return mrb_bool_value(event->key.system);

}

mrb_value ruby_event_mouse_button_code(mrb_state* mrb, mrb_value self) {

	auto event = MrbWrap::convert_from_object<sf::Event>(mrb, self);

	return mrb_fixnum_value(static_cast<int>(event->mouseButton.button));

}

mrb_value ruby_event_mouse_button_x(mrb_state* mrb, mrb_value self) {

	auto event = MrbWrap::convert_from_object<sf::Event>(mrb, self);

	return mrb_fixnum_value(event->mouseButton.x);

}

mrb_value ruby_event_mouse_button_y(mrb_state* mrb, mrb_value self) {

	auto event = MrbWrap::convert_from_object<sf::Event>(mrb, self);

	return mrb_fixnum_value(event->mouseButton.y);

}

mrb_value ruby_event_mouse_move_x(mrb_state* mrb, mrb_value self) {

	auto event = MrbWrap::convert_from_object<sf::Event>(mrb, self);

	return mrb_fixnum_value(event->mouseMove.x);

}

mrb_value ruby_event_mouse_move_y(mrb_state* mrb, mrb_value self) {

	auto event = MrbWrap::convert_from_object<sf::Event>(mrb, self);

	return mrb_fixnum_value(event->mouseMove.y);

}

mrb_value ruby_event_mouse_scroll_wheel(mrb_state* mrb, mrb_value self) {

	auto event = MrbWrap::convert_from_object<sf::Event>(mrb, self);

	return mrb_fixnum_value(static_cast<int>(event->mouseWheelScroll.wheel));

}

mrb_value ruby_event_mouse_scroll_delta(mrb_state* mrb, mrb_value self) {

	auto event = MrbWrap::convert_from_object<sf::Event>(mrb, self);

	return mrb_float_value(mrb, event->mouseWheelScroll.delta);

}

mrb_value ruby_event_mouse_scroll_x(mrb_state* mrb, mrb_value self) {

	auto event = MrbWrap::convert_from_object<sf::Event>(mrb, self);

	return mrb_fixnum_value(event->mouseWheelScroll.x);

}

mrb_value ruby_event_mouse_scroll_y(mrb_state* mrb, mrb_value self) {

	auto event = MrbWrap::convert_from_object<sf::Event>(mrb, self);

	return mrb_fixnum_value(event->mouseWheelScroll.y);

}

void setup_ruby_class_event(mrb_state* mrb) {

	auto ruby_event_class = MrbWrap::define_data_class(mrb, "Event");

	mrb_define_method(mrb, ruby_event_class, "initialize", ruby_event_init, MRB_ARGS_NONE());

	mrb_define_method(mrb, ruby_event_class, "type", ruby_event_type, MRB_ARGS_NONE());

	mrb_define_method(mrb, ruby_event_class, "key_code", ruby_event_key_code, MRB_ARGS_NONE());
	mrb_define_method(mrb, ruby_event_class, "key_alt?", ruby_event_key_alt, MRB_ARGS_NONE());
	mrb_define_method(mrb, ruby_event_class, "key_control?", ruby_event_key_control, MRB_ARGS_NONE());
	mrb_define_method(mrb, ruby_event_class, "key_shift?", ruby_event_key_shift, MRB_ARGS_NONE());
	mrb_define_method(mrb, ruby_event_class, "key_system?", ruby_event_key_system, MRB_ARGS_NONE());

	mrb_define_method(mrb, ruby_event_class, "mouse_button_code", ruby_event_mouse_button_code, MRB_ARGS_NONE());
	mrb_define_method(mrb, ruby_event_class, "mouse_button_x", ruby_event_mouse_button_x, MRB_ARGS_NONE());
	mrb_define_method(mrb, ruby_event_class, "mouse_button_y", ruby_event_mouse_button_y, MRB_ARGS_NONE());

	mrb_define_method(mrb, ruby_event_class, "mouse_move_x", ruby_event_mouse_move_x, MRB_ARGS_NONE());
	mrb_define_method(mrb, ruby_event_class, "mouse_move_y", ruby_event_mouse_move_y, MRB_ARGS_NONE());

	mrb_define_method(mrb, ruby_event_class, "mouse_scroll_wheel", ruby_event_mouse_scroll_wheel, MRB_ARGS_NONE());
	mrb_define_method(mrb, ruby_event_class, "mouse_scroll_delta", ruby_event_mouse_scroll_delta, MRB_ARGS_NONE());
	mrb_define_method(mrb, ruby_event_class, "mouse_scroll_x", ruby_event_mouse_scroll_x, MRB_ARGS_NONE());
	mrb_define_method(mrb, ruby_event_class, "mouse_scroll_y", ruby_event_mouse_scroll_y, MRB_ARGS_NONE());

}