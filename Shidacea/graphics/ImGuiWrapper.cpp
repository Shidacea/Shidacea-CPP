#include "ImGuiWrapper.h"

mrb_value ruby_imgui_begin(mrb_state* mrb, mrb_value self) {

	char* name;
	mrb_value block;

	mrb_get_args(mrb, "z&", &name, &block);

	ImGui::Begin(name);

	mrb_yield(mrb, block, mrb_nil_value());	//! TODO: Check whether this will yield any problems... ha, ha.

	ImGui::End();

	return mrb_nil_value();

}

mrb_value ruby_imgui_button(mrb_state* mrb, mrb_value self) {

	char* label;

	mrb_get_args(mrb, "z", &label);	//! TODO: More arguments

	auto return_value = ImGui::Button(label);

	return mrb_bool_value(return_value);

}

mrb_value ruby_imgui_text(mrb_state* mrb, mrb_value self) {

	char* text;

	mrb_get_args(mrb, "z", &text);

	//! We don't need the formatted text anymore in Ruby, so just change it
	//! Maybe this will change back to formatted text at some time
	ImGui::TextUnformatted(text);

	return mrb_nil_value();

}

mrb_value ruby_imgui_begin_child(mrb_state* mrb, mrb_value self) {

	char* str_id;
	mrb_value block;

	mrb_get_args(mrb, "z&", &str_id, &block);

	ImGui::BeginChild(str_id);

	mrb_yield(mrb, block, mrb_nil_value());

	ImGui::EndChild();

	return mrb_nil_value();

}

mrb_value ruby_imgui_same_line(mrb_state* mrb, mrb_value self) {

	ImGui::SameLine();

	return mrb_nil_value();

}

void setup_ruby_imgui(mrb_state* mrb) {

	auto ruby_imgui_module = mrb_define_module(mrb, "ImGui");

	mrb_define_module_function(mrb, ruby_imgui_module, "begin", ruby_imgui_begin, MRB_ARGS_REQ(1));
	mrb_define_module_function(mrb, ruby_imgui_module, "button", ruby_imgui_button, MRB_ARGS_REQ(1));
	mrb_define_module_function(mrb, ruby_imgui_module, "text", ruby_imgui_text, MRB_ARGS_REQ(1));
	mrb_define_module_function(mrb, ruby_imgui_module, "begin_child", ruby_imgui_begin_child, MRB_ARGS_REQ(1));
	mrb_define_module_function(mrb, ruby_imgui_module, "same_line", ruby_imgui_same_line, MRB_ARGS_NONE());

}
