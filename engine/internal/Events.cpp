#include "Events.h"

void setup_ruby_events(mrb_state* mrb, RClass* ruby_module) {

	// @@@ M_MODULE EventType
	// Module for different event types
	auto module_type = mrb_define_module_under(mrb, ruby_module, "EventType");

	// @@@ M_CONSTANT EventType Closed 0
	REGISTER_TYPE(mrb, module_type, Closed);

	// @@@ M_CONSTANT EventType Resized 1
	REGISTER_TYPE(mrb, module_type, Resized);

	// @@@ M_CONSTANT EventType LostFocus 2
	REGISTER_TYPE(mrb, module_type, LostFocus);

	// @@@ M_CONSTANT EventType GainedFocus 3
	REGISTER_TYPE(mrb, module_type, GainedFocus);

	// @@@ M_CONSTANT EventType TextEntered 4
	REGISTER_TYPE(mrb, module_type, TextEntered);

	// @@@ M_CONSTANT EventType KeyPressed 5
	REGISTER_TYPE(mrb, module_type, KeyPressed);

	// @@@ M_CONSTANT EventType KeyReleased 6
	REGISTER_TYPE(mrb, module_type, KeyReleased);

	// @@@ M_CONSTANT EventType MouseWheelMoved 7
	REGISTER_TYPE(mrb, module_type, MouseWheelMoved);

	// @@@ M_CONSTANT EventType MouseWheelScrolled 8
	REGISTER_TYPE(mrb, module_type, MouseWheelScrolled);

	// @@@ M_CONSTANT EventType MouseButtonPressed 9
	REGISTER_TYPE(mrb, module_type, MouseButtonPressed);

	// @@@ M_CONSTANT EventType MouseButtonReleased 10
	REGISTER_TYPE(mrb, module_type, MouseButtonReleased);

	// @@@ M_CONSTANT EventType MouseMoved 11
	REGISTER_TYPE(mrb, module_type, MouseMoved);

	// @@@ M_CONSTANT EventType MouseEntered 12
	REGISTER_TYPE(mrb, module_type, MouseEntered);

	// @@@ M_CONSTANT EventType MouseLeft 13
	REGISTER_TYPE(mrb, module_type, MouseLeft);

	// @@@ M_CONSTANT EventType JoystickButtonPressed 14
	REGISTER_TYPE(mrb, module_type, JoystickButtonPressed);

	// @@@ M_CONSTANT EventType JoystickButtonReleased 15
	REGISTER_TYPE(mrb, module_type, JoystickButtonReleased);

	// @@@ M_CONSTANT EventType JoystickMoved 16
	REGISTER_TYPE(mrb, module_type, JoystickMoved);

	// @@@ M_CONSTANT EventType JoystickConnected 17
	REGISTER_TYPE(mrb, module_type, JoystickConnected);

	// @@@ M_CONSTANT EventType JoystickDisconnected 18
	REGISTER_TYPE(mrb, module_type, JoystickDisconnected);

	// @@@ M_CONSTANT EventType TouchBegan 19
	REGISTER_TYPE(mrb, module_type, TouchBegan);

	// @@@ M_CONSTANT EventType TouchMoved 20
	REGISTER_TYPE(mrb, module_type, TouchMoved);

	// @@@ M_CONSTANT EventType TouchEnded 21
	REGISTER_TYPE(mrb, module_type, TouchEnded);

	// @@@ M_CONSTANT EventType SensorChanged 22
	REGISTER_TYPE(mrb, module_type, SensorChanged);

	// @@@ M_MODULE EventKey
	// Module for different key press values
	auto module_key = mrb_define_module_under(mrb, ruby_module, "EventKey");

	// @@@ M_CONSTANT EventKey Unknown -1
	REGISTER_KEY(mrb, module_key, Unknown);

	// @@@ M_CONSTANT EventKey A 0
	REGISTER_KEY(mrb, module_key, A);

	// @@@ M_CONSTANT EventKey B 1
	REGISTER_KEY(mrb, module_key, B);

	// @@@ M_CONSTANT EventKey C 2
	REGISTER_KEY(mrb, module_key, C);

	// @@@ M_CONSTANT EventKey D 3
	REGISTER_KEY(mrb, module_key, D);

	// @@@ M_CONSTANT EventKey E 4
	REGISTER_KEY(mrb, module_key, E);

	// @@@ M_CONSTANT EventKey F 5
	REGISTER_KEY(mrb, module_key, F);

	// @@@ M_CONSTANT EventKey G 6
	REGISTER_KEY(mrb, module_key, G);

	// @@@ M_CONSTANT EventKey H 7
	REGISTER_KEY(mrb, module_key, H);

	// @@@ M_CONSTANT EventKey I 8
	REGISTER_KEY(mrb, module_key, I);

	// @@@ M_CONSTANT EventKey J 9
	REGISTER_KEY(mrb, module_key, J);

	// @@@ M_CONSTANT EventKey K 10
	REGISTER_KEY(mrb, module_key, K);

	// @@@ M_CONSTANT EventKey L 11
	REGISTER_KEY(mrb, module_key, L);

	// @@@ M_CONSTANT EventKey M 12
	REGISTER_KEY(mrb, module_key, M);

	// @@@ M_CONSTANT EventKey N 13
	REGISTER_KEY(mrb, module_key, N);

	// @@@ M_CONSTANT EventKey O 14
	REGISTER_KEY(mrb, module_key, O);

	// @@@ M_CONSTANT EventKey P 15
	REGISTER_KEY(mrb, module_key, P);

	// @@@ M_CONSTANT EventKey Q 16
	REGISTER_KEY(mrb, module_key, Q);

	// @@@ M_CONSTANT EventKey R 17
	REGISTER_KEY(mrb, module_key, R);

	// @@@ M_CONSTANT EventKey S 18
	REGISTER_KEY(mrb, module_key, S);

	// @@@ M_CONSTANT EventKey T 19
	REGISTER_KEY(mrb, module_key, T);

	// @@@ M_CONSTANT EventKey U 20
	REGISTER_KEY(mrb, module_key, U);

	// @@@ M_CONSTANT EventKey V 21
	REGISTER_KEY(mrb, module_key, V);

	// @@@ M_CONSTANT EventKey W 22
	REGISTER_KEY(mrb, module_key, W);

	// @@@ M_CONSTANT EventKey X 23
	REGISTER_KEY(mrb, module_key, X);

	// @@@ M_CONSTANT EventKey Y 24
	REGISTER_KEY(mrb, module_key, Y);

	// @@@ M_CONSTANT EventKey Z 25
	REGISTER_KEY(mrb, module_key, Z);

	// @@@ M_CONSTANT EventKey Num0 26
	REGISTER_KEY(mrb, module_key, Num0);

	// @@@ M_CONSTANT EventKey Num1 27
	REGISTER_KEY(mrb, module_key, Num1);

	// @@@ M_CONSTANT EventKey Num2 28
	REGISTER_KEY(mrb, module_key, Num2);

	// @@@ M_CONSTANT EventKey Num3 29
	REGISTER_KEY(mrb, module_key, Num3);

	// @@@ M_CONSTANT EventKey Num4 30
	REGISTER_KEY(mrb, module_key, Num4);

	// @@@ M_CONSTANT EventKey Num5 31
	REGISTER_KEY(mrb, module_key, Num5);

	// @@@ M_CONSTANT EventKey Num6 32
	REGISTER_KEY(mrb, module_key, Num6);

	// @@@ M_CONSTANT EventKey Num7 33
	REGISTER_KEY(mrb, module_key, Num7);

	// @@@ M_CONSTANT EventKey Num8 34
	REGISTER_KEY(mrb, module_key, Num8);

	// @@@ M_CONSTANT EventKey Num9 35
	REGISTER_KEY(mrb, module_key, Num9);

	// @@@ M_CONSTANT EventKey Escape 36
	REGISTER_KEY(mrb, module_key, Escape);

	// @@@ M_CONSTANT EventKey LControl 37
	REGISTER_KEY(mrb, module_key, LControl);

	// @@@ M_CONSTANT EventKey LShift 38
	REGISTER_KEY(mrb, module_key, LShift);

	// @@@ M_CONSTANT EventKey LAlt 39
	REGISTER_KEY(mrb, module_key, LAlt);

	// @@@ M_CONSTANT EventKey LSystem 40
	REGISTER_KEY(mrb, module_key, LSystem);

	// @@@ M_CONSTANT EventKey RControl 41
	REGISTER_KEY(mrb, module_key, RControl);

	// @@@ M_CONSTANT EventKey RShift 42
	REGISTER_KEY(mrb, module_key, RShift);

	// @@@ M_CONSTANT EventKey RAlt 43
	REGISTER_KEY(mrb, module_key, RAlt);

	// @@@ M_CONSTANT EventKey RSystem 44
	REGISTER_KEY(mrb, module_key, RSystem);

	// @@@ M_CONSTANT EventKey Menu 45
	REGISTER_KEY(mrb, module_key, Menu);

	// @@@ M_CONSTANT EventKey LBracket 46
	REGISTER_KEY(mrb, module_key, LBracket);

	// @@@ M_CONSTANT EventKey RBracket 47
	REGISTER_KEY(mrb, module_key, RBracket);

	// @@@ M_CONSTANT EventKey Semicolon 48
	REGISTER_KEY(mrb, module_key, Semicolon);

	// @@@ M_CONSTANT EventKey Comma 49
	REGISTER_KEY(mrb, module_key, Comma);

	// @@@ M_CONSTANT EventKey Period 50
	REGISTER_KEY(mrb, module_key, Period);

	// @@@ M_CONSTANT EventKey Quote 51
	REGISTER_KEY(mrb, module_key, Quote);

	// @@@ M_CONSTANT EventKey Slash 52
	REGISTER_KEY(mrb, module_key, Slash);

	// @@@ M_CONSTANT EventKey Backslash 53
	REGISTER_KEY(mrb, module_key, Backslash);

	// @@@ M_CONSTANT EventKey Tilde 54
	REGISTER_KEY(mrb, module_key, Tilde);

	// @@@ M_CONSTANT EventKey Equal 55
	REGISTER_KEY(mrb, module_key, Equal);

	// @@@ M_CONSTANT EventKey Hyphen 56
	REGISTER_KEY(mrb, module_key, Hyphen);

	// @@@ M_CONSTANT EventKey Space 57
	REGISTER_KEY(mrb, module_key, Space);

	// @@@ M_CONSTANT EventKey Enter 58
	REGISTER_KEY(mrb, module_key, Enter);

	// @@@ M_CONSTANT EventKey Backspace 59
	REGISTER_KEY(mrb, module_key, Backspace);

	// @@@ M_CONSTANT EventKey Tab 60
	REGISTER_KEY(mrb, module_key, Tab);

	// @@@ M_CONSTANT EventKey PageUp 61
	REGISTER_KEY(mrb, module_key, PageUp);

	// @@@ M_CONSTANT EventKey PageDown 62
	REGISTER_KEY(mrb, module_key, PageDown);

	// @@@ M_CONSTANT EventKey End 63
	REGISTER_KEY(mrb, module_key, End);

	// @@@ M_CONSTANT EventKey Home 64
	REGISTER_KEY(mrb, module_key, Home);

	// @@@ M_CONSTANT EventKey Insert 65
	REGISTER_KEY(mrb, module_key, Insert);

	// @@@ M_CONSTANT EventKey Delete 66
	REGISTER_KEY(mrb, module_key, Delete);

	// @@@ M_CONSTANT EventKey Add 67
	REGISTER_KEY(mrb, module_key, Add);

	// @@@ M_CONSTANT EventKey Subtract 68
	REGISTER_KEY(mrb, module_key, Subtract);

	// @@@ M_CONSTANT EventKey Multiply 69
	REGISTER_KEY(mrb, module_key, Multiply);

	// @@@ M_CONSTANT EventKey Divide 70
	REGISTER_KEY(mrb, module_key, Divide);

	// @@@ M_CONSTANT EventKey Left 71
	REGISTER_KEY(mrb, module_key, Left);

	// @@@ M_CONSTANT EventKey Right 72
	REGISTER_KEY(mrb, module_key, Right);

	// @@@ M_CONSTANT EventKey Up 73
	REGISTER_KEY(mrb, module_key, Up);

	// @@@ M_CONSTANT EventKey Down 74
	REGISTER_KEY(mrb, module_key, Down);

	// @@@ M_CONSTANT EventKey Numpad0 75
	REGISTER_KEY(mrb, module_key, Numpad0);

	// @@@ M_CONSTANT EventKey Numpad1 76
	REGISTER_KEY(mrb, module_key, Numpad1);

	// @@@ M_CONSTANT EventKey Numpad2 77
	REGISTER_KEY(mrb, module_key, Numpad2);

	// @@@ M_CONSTANT EventKey Numpad3 78
	REGISTER_KEY(mrb, module_key, Numpad3);

	// @@@ M_CONSTANT EventKey Numpad4 79
	REGISTER_KEY(mrb, module_key, Numpad4);

	// @@@ M_CONSTANT EventKey Numpad5 80
	REGISTER_KEY(mrb, module_key, Numpad5);

	// @@@ M_CONSTANT EventKey Numpad6 81
	REGISTER_KEY(mrb, module_key, Numpad6);

	// @@@ M_CONSTANT EventKey Numpad7 82
	REGISTER_KEY(mrb, module_key, Numpad7);

	// @@@ M_CONSTANT EventKey Numpad8 83
	REGISTER_KEY(mrb, module_key, Numpad8);

	// @@@ M_CONSTANT EventKey Numpad9 84
	REGISTER_KEY(mrb, module_key, Numpad9);

	// @@@ M_CONSTANT EventKey F1 85
	REGISTER_KEY(mrb, module_key, F1);

	// @@@ M_CONSTANT EventKey F2 86
	REGISTER_KEY(mrb, module_key, F2);

	// @@@ M_CONSTANT EventKey F3 87
	REGISTER_KEY(mrb, module_key, F3);

	// @@@ M_CONSTANT EventKey F4 88
	REGISTER_KEY(mrb, module_key, F4);

	// @@@ M_CONSTANT EventKey F5 89
	REGISTER_KEY(mrb, module_key, F5);

	// @@@ M_CONSTANT EventKey F6 90
	REGISTER_KEY(mrb, module_key, F6);

	// @@@ M_CONSTANT EventKey F7 91
	REGISTER_KEY(mrb, module_key, F7);

	// @@@ M_CONSTANT EventKey F8 92
	REGISTER_KEY(mrb, module_key, F8);

	// @@@ M_CONSTANT EventKey F9 93
	REGISTER_KEY(mrb, module_key, F9);

	// @@@ M_CONSTANT EventKey F10 94
	REGISTER_KEY(mrb, module_key, F10);

	// @@@ M_CONSTANT EventKey F11 95
	REGISTER_KEY(mrb, module_key, F11);

	// @@@ M_CONSTANT EventKey F12 96
	REGISTER_KEY(mrb, module_key, F12);

	// @@@ M_CONSTANT EventKey F13 97
	REGISTER_KEY(mrb, module_key, F13);

	// @@@ M_CONSTANT EventKey F14 98
	REGISTER_KEY(mrb, module_key, F14);

	// @@@ M_CONSTANT EventKey F15 99
	REGISTER_KEY(mrb, module_key, F15);

	// @@@ M_CONSTANT EventKey Pause 100
	REGISTER_KEY(mrb, module_key, Pause);

	// @@@ M_METHOD EventKey is_pressed? key_value
	// @return [Boolean]
	// @param key_value [Integer]
	// Checks whether the key with the given value is pressed
	// @see EventKey
	MrbWrap::define_module_function(mrb, module_key, "is_pressed?", MRUBY_FUNC {

		auto args = MrbWrap::get_converted_args<int>(mrb);
		auto key_value = std::get<0>(args);

		return mrb_bool_value(sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(key_value)));
		
	}, MRB_ARGS_REQ(1));

	// @@@ M_MODULE EventMouse
	// Module for different mouse button press values
	auto module_mouse = mrb_define_module_under(mrb, ruby_module, "EventMouse");

	// @@@ M_METHOD EventMouse get_position window=nil
	// @return [Array<Integer>]
	// @param window [Window|nil]
	// Gets the pixel position of the mouse, either absolute or relative to a given window
	MrbWrap::define_module_function(mrb, module_mouse, "get_position", MRUBY_FUNC {
		
		mrb_value ruby_window = mrb_nil_value();

		mrb_get_args(mrb, "|o", &ruby_window);

		sf::Vector2i mouse_position;

		if (mrb_nil_p(ruby_window)) {

			mouse_position = sf::Mouse::getPosition();

		} else {

			auto window = MrbWrap::convert_from_object<RenderQueueWindow>(mrb, ruby_window);

			mouse_position = sf::Mouse::getPosition(window->get_window_reference());

		}

		auto position_array = mrb_assoc_new(mrb, mrb_fixnum_value(mouse_position.x), mrb_fixnum_value(mouse_position.y));

		return position_array;

	}, MRB_ARGS_OPT(1));

	// @@@ M_METHOD EventMouse get_coordinates window
	// @return [Coordinates]
	// @param window [Window]
	// Gets the coordinates of the mouse, relative to the given window
	MrbWrap::define_module_function(mrb, module_mouse, "get_coordinates", MRUBY_FUNC{

		mrb_value ruby_window;

		mrb_get_args(mrb, "o", &ruby_window);

		auto window = MrbWrap::convert_from_object<RenderQueueWindow>(mrb, ruby_window);

		auto coords = window->get_window_reference().mapPixelToCoords(sf::Mouse::getPosition(window->get_window_reference()));

		auto ruby_coordinates_class = MrbWrap::get_class_info_ptr<sf::Vector2f>();

		auto ruby_coords = mrb_obj_new(mrb, ruby_coordinates_class, 0, NULL);
		auto converted_coords = MrbWrap::convert_from_object<sf::Vector2f>(mrb, ruby_coords);

		*converted_coords = coords;

		return ruby_coords;

	}, MRB_ARGS_REQ(1));

	// @@@ M_METHOD EventMouse is_button_pressed? button_value
	// @return [Boolean]
	// @param button_value [Integer]
	// Checks whether the mouse button with the given value is pressed
	// @see EventMouse
	MrbWrap::define_module_function(mrb, module_mouse, "is_button_pressed?", MRUBY_FUNC {

		auto args = MrbWrap::get_converted_args<int>(mrb);
		auto button_value = std::get<0>(args);

		return mrb_bool_value(sf::Mouse::isButtonPressed(static_cast<sf::Mouse::Button>(button_value)));

	}, MRB_ARGS_REQ(1));

	// @@@ M_METHOD EventMouse set_position position window=nil
	// @return [nil]
	// @param position [Array<Integer>]
	// @param window [Window|nil]
	// Sets the pixel position of the mouse, either absolute or relative to a given window
	MrbWrap::define_module_function(mrb, module_mouse, "set_position", MRUBY_FUNC {

		mrb_value val;
		mrb_value ruby_window = mrb_nil_value();

		mrb_get_args(mrb, "A|o", &val, &ruby_window);

		//! TODO: Check array boundaries, if needed

		auto x = mrb_fixnum(mrb_ary_entry(val, 0));
		auto y = mrb_fixnum(mrb_ary_entry(val, 1));

		auto new_position = sf::Vector2i(static_cast<int>(x), static_cast<int>(y));

		if (mrb_nil_p(ruby_window)) {

			sf::Mouse::setPosition(new_position);

		} else {

			auto window = MrbWrap::convert_from_object<RenderQueueWindow>(mrb, ruby_window);

			sf::Mouse::setPosition(new_position, window->get_window_reference());

		}

		return mrb_nil_value();

	}, MRB_ARGS_ARG(1, 1));

	//! TODO: Function to set mouse coordinates

	// @@@ M_CONSTANT EventMouse Left 0
	REGISTER_BUTTON(mrb, module_mouse, Left);

	// @@@ M_CONSTANT EventMouse Right 1
	REGISTER_BUTTON(mrb, module_mouse, Right);

	// @@@ M_CONSTANT EventMouse Middle 2
	REGISTER_BUTTON(mrb, module_mouse, Middle);

	// @@@ M_CONSTANT EventMouse XButton1 3
	REGISTER_BUTTON(mrb, module_mouse, XButton1);

	// @@@ M_CONSTANT EventMouse XButton2 4
	REGISTER_BUTTON(mrb, module_mouse, XButton2);

	// @@@ M_CONSTANT EventMouse VerticalWheel 5
	REGISTER_WHEEL(mrb, module_mouse, VerticalWheel);

	// @@@ M_CONSTANT EventMouse HorizontalWheel 6
	REGISTER_WHEEL(mrb, module_mouse, HorizontalWheel);

}

void setup_ruby_class_event(mrb_state* mrb, RClass* ruby_module) {

	// @@@ M_CLASS Event
	// Event container class
	MrbWrap::wrap_class_under<sf::Event>(mrb, "Event", ruby_module);
	auto ruby_event_class = MrbWrap::get_class_info_ptr<sf::Event>();

	// @@@ M_IM Event initialize
	// @return [Event]
	// Creates an empty event object
	MrbWrap::wrap_constructor<sf::Event>(mrb);

	// @@@ M_ATTR Event type Integer r
	// Type of the event
	// @see EventType
	MrbWrap::define_member_function(mrb, ruby_event_class, "type", MRUBY_FUNC {

		auto event = MrbWrap::convert_from_object<sf::Event>(mrb, self);

		return mrb_fixnum_value(static_cast<int>(event->type));

	}, MRB_ARGS_NONE());

	// @@@ M_ATTR Event key_code Integer r
	// Key value of the event if it is a key press
	// @see EventKey
	MrbWrap::define_member_function(mrb, ruby_event_class, "key_code", MRUBY_FUNC {

		auto event = MrbWrap::convert_from_object<sf::Event>(mrb, self);

		return mrb_fixnum_value(static_cast<int>(event->key.code));

	}, MRB_ARGS_NONE());

	// @@@ M_IM Event key_alt?
	// @return [Boolean]
	// Returns true if an alt key is pressed
	MrbWrap::define_member_function(mrb, ruby_event_class, "key_alt?", MRUBY_FUNC {

		auto event = MrbWrap::convert_from_object<sf::Event>(mrb, self);

		return mrb_bool_value(event->key.alt);

	}, MRB_ARGS_NONE());

	// @@@ M_IM Event key_control?
	// @return [Boolean]
	// Returns true if a ctrl key is pressed
	MrbWrap::define_member_function(mrb, ruby_event_class, "key_control?", MRUBY_FUNC {

		auto event = MrbWrap::convert_from_object<sf::Event>(mrb, self);

		return mrb_bool_value(event->key.control);

	}, MRB_ARGS_NONE());

	// @@@ M_IM Event key_shift?
	// @return [Boolean]
	// Returns true if a shift key is pressed
	MrbWrap::define_member_function(mrb, ruby_event_class, "key_shift?", MRUBY_FUNC {

		auto event = MrbWrap::convert_from_object<sf::Event>(mrb, self);

		return mrb_bool_value(event->key.shift);

	}, MRB_ARGS_NONE());

	// @@@ M_IM Event key_system?
	// @return [Boolean]
	// Returns true if a system key is pressed
	MrbWrap::define_member_function(mrb, ruby_event_class, "key_system?", MRUBY_FUNC {

		auto event = MrbWrap::convert_from_object<sf::Event>(mrb, self);

		return mrb_bool_value(event->key.system);

	}, MRB_ARGS_NONE());

	// @@@ M_ATTR Event mouse_button_code Integer r
	// Mouse button value of the event if it is a mouse button press
	// @see EventMouse
	MrbWrap::define_member_function(mrb, ruby_event_class, "mouse_button_code", MRUBY_FUNC {

		auto event = MrbWrap::convert_from_object<sf::Event>(mrb, self);

		return mrb_fixnum_value(static_cast<int>(event->mouseButton.button));

	}, MRB_ARGS_NONE());

	// @@@ M_ATTR Event mouse_button_x Integer r
	// Mouse x coordinate in pixels, relative to the owning window, when a button was pressed
	MrbWrap::define_member_function(mrb, ruby_event_class, "mouse_button_x", MRUBY_FUNC {

		auto event = MrbWrap::convert_from_object<sf::Event>(mrb, self);

		return mrb_fixnum_value(event->mouseButton.x);

	}, MRB_ARGS_NONE());

	// @@@ M_ATTR Event mouse_button_y Integer r
	// Mouse y coordinate in pixels, relative to the owning window, when a button was pressed
	MrbWrap::define_member_function(mrb, ruby_event_class, "mouse_button_y", MRUBY_FUNC {

		auto event = MrbWrap::convert_from_object<sf::Event>(mrb, self);

		return mrb_fixnum_value(event->mouseButton.y);

	}, MRB_ARGS_NONE());

	// @@@ M_ATTR Event mouse_move_x Integer r
	// Mouse x coordinate in pixels, relative to the owning window, when the mouse was moved
	MrbWrap::define_member_function(mrb, ruby_event_class, "mouse_move_x", MRUBY_FUNC {

		auto event = MrbWrap::convert_from_object<sf::Event>(mrb, self);

		return mrb_fixnum_value(event->mouseMove.x);

	}, MRB_ARGS_NONE());

	// @@@ M_ATTR Event mouse_move_y Integer r
	// Mouse y coordinate in pixels, relative to the owning window, when the mouse was moved
	MrbWrap::define_member_function(mrb, ruby_event_class, "mouse_move_y", MRUBY_FUNC {

		auto event = MrbWrap::convert_from_object<sf::Event>(mrb, self);

		return mrb_fixnum_value(event->mouseMove.y);

	}, MRB_ARGS_NONE());

	// @@@ M_ATTR Event mouse_scroll_wheel Integer r
	// Mouse wheel scrolled if a mouse scrolling event was triggered (0 for vertical, 1 for horizontal)
	MrbWrap::define_member_function(mrb, ruby_event_class, "mouse_scroll_wheel", MRUBY_FUNC {

		auto event = MrbWrap::convert_from_object<sf::Event>(mrb, self);

		return mrb_fixnum_value(static_cast<mrb_int>(event->mouseWheelScroll.wheel));

	}, MRB_ARGS_NONE());

	// @@@ M_ATTR Event mouse_scroll_delta Float r
	// Mouse wheel scrolling distance
	MrbWrap::define_member_function(mrb, ruby_event_class, "mouse_scroll_delta", MRUBY_FUNC {

		auto event = MrbWrap::convert_from_object<sf::Event>(mrb, self);

		return mrb_float_value(mrb, event->mouseWheelScroll.delta);

	}, MRB_ARGS_NONE());

	// @@@ M_ATTR Event mouse_scroll_x Integer r
	// Mouse x motion in pixels, relative to the owning window, when a wheel was scrolled
	MrbWrap::define_member_function(mrb, ruby_event_class, "mouse_scroll_x", MRUBY_FUNC {

		auto event = MrbWrap::convert_from_object<sf::Event>(mrb, self);

		return mrb_fixnum_value(event->mouseWheelScroll.x);

	}, MRB_ARGS_NONE());

	// @@@ M_ATTR Event mouse_scroll_y Integer r
	// Mouse y motion in pixels, relative to the owning window, when a wheel was scrolled
	MrbWrap::define_member_function(mrb, ruby_event_class, "mouse_scroll_y", MRUBY_FUNC {

		auto event = MrbWrap::convert_from_object<sf::Event>(mrb, self);

		return mrb_fixnum_value(event->mouseWheelScroll.y);

	}, MRB_ARGS_NONE());

	// @@@ M_ATTR Event text_unicode String r
	// Inputted text if an input happened
	MrbWrap::define_member_function(mrb, ruby_event_class, "text_unicode", MRUBY_FUNC {

		auto event = MrbWrap::convert_from_object<sf::Event>(mrb, self);

		return mrb_fixnum_value(static_cast<mrb_int>(event->text.unicode));

	}, MRB_ARGS_NONE());

}