#pragma once

#include <mruby.h>
#include <memory>

namespace MrbWrap {

	struct ClassInfoStruct {

		std::unique_ptr<RClass> class_ptr = nullptr;
		mrb_sym symbol = 0;
		const char* name = "";

	};

	template <class T> ClassInfoStruct ClassInfo;

	template <class T> void set_class_info_ptr(RClass* raw_ptr) {

		ClassInfo<T>.class_ptr = std::unique_ptr<RClass>(raw_ptr);

	}

	template <class T> auto get_class_info_symbol() {

		return ClassInfo<T>.symbol;

	}

	template <class T> auto get_class_info_ptr() {

		return ClassInfo<T>.class_ptr.get();

	}

	template <class T> auto get_class_info_name() {

		return ClassInfo<T>.name;

	}

}