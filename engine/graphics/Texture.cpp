#include "Texture.h"

void setup_ruby_class_texture(mrb_state* mrb, RClass* ruby_module) {

	auto ruby_texture_class = MrbWrap::define_data_class_under(mrb, "Texture", ruby_module);

	MrbWrap::wrap_class_under<sf::Texture>(mrb, "Texture", ruby_module);

	MrbWrap::wrap_constructor<sf::Texture>(mrb);

	MrbWrap::define_member_function(mrb, ruby_texture_class, "size", MRUBY_FUNC {

		auto texture = MrbWrap::convert_from_object<sf::Texture>(mrb, self);

		auto size = static_cast<sf::Vector2f>(texture->getSize());

		auto ivec_class = MrbWrap::get_class_info_ptr<sf::Vector2f>();
		auto new_mruby_size = mrb_obj_new(mrb, ivec_class, 0, NULL);

		auto ruby_size = MrbWrap::convert_from_object<sf::Vector2f>(mrb, new_mruby_size);
		*ruby_size = size;

		return new_mruby_size;

	});

	MrbWrap::define_member_function(mrb, ruby_texture_class, "load_from_file", MRUBY_FUNC {

		char* filename;
		mrb_value intrect = mrb_nil_value();

		mrb_get_args(mrb, "z|o", &filename, &intrect);

		auto texture = MrbWrap::convert_from_object<sf::Texture>(mrb, self);

		//! TODO: Simplifiy

		auto script_module = mrb_module_get_under(mrb, mrb_module_get(mrb, "SDC"), "Script");
		auto path = mrb_mod_cv_get(mrb, script_module, mrb_intern_static(mrb, "@@_path", strlen("@@_path")));

		auto path_file_name = std::string(mrb_string_cstr(mrb, path)) + std::string("/") + std::string(filename);

		//! TODO: Check for missing files, so that tilesets don't yield div by zero errors, for example

		if (mrb_nil_p(intrect)) {

			texture->loadFromFile(path_file_name);	//! TODO: Find out why this yields a warning

		} else {

			auto intrect_value = MrbWrap::convert_from_object<sf::IntRect>(mrb, intrect);
			texture->loadFromFile(path_file_name, static_cast<sf::IntRect>(*intrect_value));	//! May not work everywhere, test it!

		}

		return self;

	}, MRB_ARGS_ARG(1, 1));

}