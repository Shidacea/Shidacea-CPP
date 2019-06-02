#include "Events.h"

void setup_ruby_events(mrb_state* mrb) {

	auto module_key = mrb_define_module(mrb, "Key");

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

	auto module_mouse = mrb_define_module(mrb, "Mouse");

	REGISTER_BUTTON(mrb, module_mouse, Left);
	REGISTER_BUTTON(mrb, module_mouse, Right);
	REGISTER_BUTTON(mrb, module_mouse, Middle);

	REGISTER_BUTTON(mrb, module_mouse, XButton1);
	REGISTER_BUTTON(mrb, module_mouse, XButton2);

	REGISTER_WHEEL(mrb, module_mouse, VerticalWheel);
	REGISTER_WHEEL(mrb, module_mouse, HorizontalWheel);

}