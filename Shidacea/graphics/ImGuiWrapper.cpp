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

mrb_value ruby_imgui_new_line(mrb_state* mrb, mrb_value self) {

	ImGui::NewLine();

	return mrb_nil_value();

}

mrb_value ruby_imgui_input_instance_variable_int(mrb_state* mrb, mrb_value self) {

	char* label;
	mrb_value object;
	mrb_sym symbol;

	mrb_get_args(mrb, "zon", &label, &object, &symbol);

	auto int_value = mrb_iv_get(mrb, object, symbol);
	auto return_value = ImGui::InputInt(label, &mrb_fixnum(int_value));
	mrb_iv_set(mrb, object, symbol, int_value);

	return mrb_bool_value(return_value);

}

mrb_value ruby_imgui_input_instance_variable_string(mrb_state* mrb, mrb_value self) {

	char* label;
	mrb_value object;
	mrb_sym symbol;

	//! TODO: Variable buffer length, realized using malloc

	char content[100];

	mrb_get_args(mrb, "zon", &label, &object, &symbol);

	auto str_value = mrb_iv_get(mrb, object, symbol);
	strncpy(content, mrb_str_to_cstr(mrb, str_value), 100);
	auto return_value = ImGui::InputText(label, content, 100);
	mrb_iv_set(mrb, object, symbol, mrb_str_new(mrb, content, strlen(content)));

	return mrb_bool_value(return_value);

}

//! TODO: Slider

mrb_value ruby_imgui_input_int(mrb_state* mrb, mrb_value self) {

	//! TODO: Make this more usable!!!
	//! E.g.: Check the array types for errors OR introduce a new class ImGui::Link using ImGui::link(3, 2, 1) or so
	//! Also introduce some defines

	char* label;
	mrb_value* v;
	int count;

	mrb_get_args(mrb, "za", &label, &v, &count);

	bool return_value;

	if (count == 1) {

		return_value = ImGui::InputInt(label, &mrb_fixnum(v[0]));

	} else if(count == 2) {

		int values[2];

		for(unsigned int i = 0; i < 2; i++) values[i] = mrb_fixnum(v[i]);
		return_value = ImGui::InputInt2(label, values);
		for(unsigned int i = 0; i < 2; i++) mrb_fixnum(v[i]) = values[i];

	} else if(count == 3) {

		int values[3];

		for (unsigned int i = 0; i < 3; i++) values[i] = mrb_fixnum(v[i]);
		return_value = ImGui::InputInt3(label, values);
		for (unsigned int i = 0; i < 3; i++) mrb_fixnum(v[i]) = values[i];

	} else if(count == 4) {

		int values[4];

		for (unsigned int i = 0; i < 4; i++) values[i] = mrb_fixnum(v[i]);
		return_value = ImGui::InputInt4(label, values);
		for (unsigned int i = 0; i < 4; i++) mrb_fixnum(v[i]) = values[i];

	} else {

		//! TODO: Error

	}

	return mrb_bool_value(return_value);

}

void setup_ruby_imgui(mrb_state* mrb) {

	auto ruby_imgui_module = mrb_define_module(mrb, "ImGui");

	mrb_define_module_function(mrb, ruby_imgui_module, "begin", ruby_imgui_begin, MRB_ARGS_REQ(1));
	mrb_define_module_function(mrb, ruby_imgui_module, "button", ruby_imgui_button, MRB_ARGS_REQ(1));
	mrb_define_module_function(mrb, ruby_imgui_module, "text", ruby_imgui_text, MRB_ARGS_REQ(1));
	mrb_define_module_function(mrb, ruby_imgui_module, "begin_child", ruby_imgui_begin_child, MRB_ARGS_REQ(1));
	mrb_define_module_function(mrb, ruby_imgui_module, "same_line", ruby_imgui_same_line, MRB_ARGS_NONE());
	mrb_define_module_function(mrb, ruby_imgui_module, "new_line", ruby_imgui_new_line, MRB_ARGS_NONE());
	mrb_define_module_function(mrb, ruby_imgui_module, "input_int", ruby_imgui_input_int, MRB_ARGS_REQ(2));
	mrb_define_module_function(mrb, ruby_imgui_module, "input_instance_variable_int", ruby_imgui_input_instance_variable_int, MRB_ARGS_REQ(3));
	mrb_define_module_function(mrb, ruby_imgui_module, "input_instance_variable_string", ruby_imgui_input_instance_variable_string, MRB_ARGS_REQ(3));

}
