#include "Texture.h"

void setup_ruby_class_texture(mrb_state* mrb, RClass* ruby_module) {

	auto ruby_texture_class = MrbWrap::define_data_class_under(mrb, "Texture", ruby_module);

	MrbWrap::wrap_class_under<sf::Texture>(mrb, "Texture", ruby_module);

	MrbWrap::wrap_constructor<sf::Texture>(mrb);

	MrbWrap::define_mruby_function(mrb, ruby_texture_class, "load_from_file", MRUBY_FUNC {

		char* filename;
		mrb_value intrect = mrb_nil_value();

		mrb_get_args(mrb, "z|o", &filename, &intrect);

		auto texture = MrbWrap::convert_from_object<sf::Texture>(mrb, self);

		if (mrb_nil_p(intrect)) {

			texture->loadFromFile(filename);	//! TODO: Find out why this yields a warning

		} else {

			auto intrect_value = MrbWrap::convert_from_object<sf::IntRect>(mrb, intrect);
			texture->loadFromFile(filename, static_cast<sf::IntRect>(*intrect_value));	//! May not work everywhere, test it!

		}

		return self;

	}, MRB_ARGS_REQ(1));

}