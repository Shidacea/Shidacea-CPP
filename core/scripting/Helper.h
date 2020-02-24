#pragma once

#include <mruby.h>
#include <mruby/dump.h>
#include <mruby/variable.h>
#include <mruby/data.h>
#include <mruby/compile.h>
#include <mruby/class.h>
#include <mruby/array.h>
#include <mruby/string.h>
#include <cstring>
#include <string>
#include <filesystem>
#include <functional>
#include <type_traits>
#include <tuple>
#include <utility>

#include "StaticString.h"
#include "DefaultWrap.h"
#include "FormatString.h"
#include "ClassInfo.h"
#include "MemberSpec.h"

#include <SFML/Graphics.hpp>

//! Preprocessor shenanigans to switch between script file loading and pre-compiled bytecode
//! If debug mode is on (NDEBUG not defined), the macro will directly load the script file "scripts/XXX.rb"
//! If debug mode is off, the macro will execute the bytecode in the respective array compiled_ruby_XXX
//! In the latter case, don't forget to include "compiled_scripts/XXX.h" (but ONLY then), or else the array will not be defined
//! Sadly, there is no easy way to circumwent the conditioned include directive
#ifndef NDEBUG
#define MRB_LOAD_SCRIPT(mrb, name, path) MrbWrap::execute_script_file(mrb, #path ".rb")
#else
#define MRB_LOAD_SCRIPT(mrb, name, path) MrbWrap::execute_bytecode(mrb, compiled_ruby_##name)
#endif

//! If there are any scripts in the scripts folder of the release version, load them if DYNAMIC_LOADING is set
//! This way scripts can be loaded at runtime, e.g. for a precompiled engine

#ifndef NDEBUG
#define MRB_LOAD_SCRIPT_FOLDER(mrb, name, path) MrbWrap::load_all_scripts_recursively(mrb, #path)
#else
#ifdef DYNAMIC_LOADING
#define MRB_LOAD_SCRIPT_FOLDER(mrb, name, path) MrbWrap::execute_bytecode(mrb, compiled_ruby_##name); \
MrbWrap::load_all_scripts_recursively(mrb, #path)
#else
#define MRB_LOAD_SCRIPT_FOLDER(mrb, name, path) MrbWrap::execute_bytecode(mrb, compiled_ruby_##name)
#endif
#endif

//! TODO: Rewrite functions above and includes so that only the core and the custom scenes and entities need to be loaded
//! TODO: Do this by defining macros which may either load one single header or a folder with scripts recursively

#include <iostream>

//! Alias for the lamdba type used for mruby functions

#define MRUBY_FUNC [](mrb_state* mrb, mrb_value self) noexcept -> mrb_value

//! Short alias for optional value wrappers

#define MRBW_OPT MrbWrap::DefaultWrap
#define MRBW_RAT_OPT MrbWrap::RationalDefaultWrap

namespace MrbWrap {

	//! Will be defined below
	template <class T> mrb_value ruby_class_default_init_copy(mrb_state* mrb, mrb_value self);

	//! Some different ways to execute mruby code

	//! Execute a string containing mruby code
	//! Only useful for user-generated input
	//! If C++ code needs to execute ruby commands, don't use this
	void execute_string(mrb_state* mrb, std::string const& code);

	//! Ececute a mruby script file
	//! Easiest way to execute script files, but also the slowest
	void execute_script_file(mrb_state* mrb, std::string const& filename);

	//! Execute a file containing mruby bytecode
	//! WARNING: Does not work correctly for some reason, so this should NEVER be used!
	[[deprecated("May not work in many situations")]] void execute_bytecode_file(mrb_state* mrb, std::string const& filename);

	//! Execute embedded bytecode from a C array
	//! Fastest way to load a script, but needs some setup work
	void execute_bytecode(mrb_state* mrb, const uint8_t* symbol_array);

	//! Load mods
	void load_mods(mrb_state* mrb);

	//! Load all scripts in a given path
	void load_all_scripts_recursively(mrb_state* mrb, std::string path);

	//! Universal destructor wrapped into a C representation
	//! Will be used as callback for ruby object deallocation
	template <class T> static void free_data(mrb_state* mrb, void* object_ptr) {

		delete static_cast<T*>(object_ptr);

	}

	//! Create and returns a ruby class which can be used as a C++ class wrapper
	//! Use this when setting up a ruby class
	RClass* define_data_class(mrb_state* mrb, const char* name, RClass* super_class = nullptr);
	RClass* define_data_class_under(mrb_state* mrb, const char* name, RClass* ruby_module, RClass* super_class = nullptr);

	template <class T> void wrap_class(mrb_state* mrb, const char* name, RClass* super_class = nullptr) {

		ClassInfo<T>.class_ptr = define_data_class(mrb, name, super_class);
		ClassInfo<T>.symbol = mrb_intern_static(mrb, name, strlen(name));
		ClassInfo<T>.name = name;

	}

	template <class T> void wrap_class_under(mrb_state* mrb, const char* name, RClass* ruby_module, RClass* super_class = nullptr) {

		ClassInfo<T>.class_ptr = define_data_class_under(mrb, name, ruby_module, super_class);
		ClassInfo<T>.symbol = mrb_intern_static(mrb, name, strlen(name));	//! TODO: Test this
		ClassInfo<T>.name = name;

	}

	//! Define a new function for ruby
	void define_mruby_function(mrb_state* mrb, RClass* ruby_class, const char* name, mrb_value(*func)(mrb_state* mrb, mrb_value self) noexcept, mrb_aspec aspec = MRB_ARGS_NONE());

	//! Define a copy method automatically for any wrapped C++ object
	//! Use this when setting up a ruby class
	template <class T> void define_default_copy_init(mrb_state* mrb) {

		auto ruby_class = get_class_info_ptr<T>();

		mrb_define_method(mrb, ruby_class, "initialize_copy", ruby_class_default_init_copy<T>, MRB_ARGS_REQ(1));

	}

	//! Creates a direct ruby wrapper for any C++ object and stores it in 'self'
	//! Constructor arguments can be given as 'TArgs', if needed
	//! The name of the class T will be used as the argument for the ruby-internal name
	//! This may cause some weird names from certain compilers, but this shouldn't pose a problem
	//! DO NOT destroy the created object manually, the mruby garbage collector will do this for you!
	//! IMPORTANT: This works only with ruby classes specifically declared as data object
	//! Do this by using the function 'define_data_class' defined here
	//! Use this in callbacks
	template <class T, class ... TArgs> T* convert_to_object(mrb_state* mrb, mrb_value self, TArgs ... args) {

		auto new_object = new T(args...);

		static const mrb_data_type data_type = {

			typeid(T).name(), free_data<T>

		};

		DATA_PTR(self) = new_object;
		DATA_TYPE(self) = &data_type;

		return new_object;

	}

	//! Return the wrapped C++ object of class 'T' from 'self'
	//! This can be used to modify the internal properties of a wrapped C++ object
	//! Use this in callbacks
	template <class T> T* convert_from_object(mrb_state* mrb, mrb_value self) {

		auto type = DATA_TYPE(self);

		MrbWrap::verify_type<T>(mrb, self);

		return static_cast<T*>(mrb_data_get_ptr(mrb, self, type));

	}

	//! Copy the content of the wrapped C++ structure to the new wrapper in 'self'
	//! Use this in callbacks
	template <class T> void copy_object(mrb_state* mrb, mrb_value self) {

		mrb_value original;

		mrb_get_args(mrb, "o", &original);

		auto old_value = MrbWrap::convert_from_object<T>(mrb, original);
		auto new_value = MrbWrap::convert_to_object<T>(mrb, self);

		*new_value = *old_value;

	}

	//! Default copy routine which can be used for trivial copy constructors
	//! Use this as a callback routine
	template <class T> mrb_value ruby_class_default_init_copy(mrb_state* mrb, mrb_value self) {

		MrbWrap::copy_object<T>(mrb, self);

		return self;
	}

	//! Creates a C++ instance of the class 'T' and wraps it directly into the ruby instance variable of the ruby object 'self'
	//! Use this in callbacks
	template <class T, class ... TArgs> T* convert_to_instance_variable(mrb_state* mrb, mrb_value self, const char* var_c_str, TArgs ... args) {

		auto new_object = new T(args...);

		static const struct mrb_data_type data_type = {

			typeid(T).name(), free_data<T>

		};

		//! mrb_intern_lit does not work here, because string lengths are pretty weird in mruby
		//! Also, the symbols do not need to be computed more than once, so this variable is made static (also see below)
		static auto symbol = mrb_intern_static(mrb, var_c_str, strlen(var_c_str));
		auto wrapper = Data_Wrap_Struct(mrb, mrb->object_class, &data_type, new_object);

		mrb_iv_set(mrb, self, symbol, mrb_obj_value(wrapper));

		return new_object;

	}

	//! Obtains a pointer to the C++ object of class 'T' back from the instance variable with name 'var_c_str' from the ruby object 'self'
	//! Use this in callbacks
	template <class T> T* convert_from_instance_variable(mrb_state* mrb, mrb_value self, const char* var_c_str) {

		static auto symbol = mrb_intern_static(mrb, var_c_str, strlen(var_c_str));
		auto instance_var = mrb_iv_get(mrb, self, symbol);
		auto type = DATA_TYPE(instance_var);

		return static_cast<T*>(mrb_data_get_ptr(mrb, instance_var, type));

	}

	//! TODO: Do not generate a value each time calling this
	//! Get default value of wrapper class, else just return C++ default
	template <class T> constexpr auto get_default(T arg) {

		if constexpr (std::is_base_of<BaseDefaultWrap, T>::value) {

			return T::value;

		} else {

			auto ret_value = T();
			return ret_value;

		}

	};

	//! Function to cast any value to an internal ruby value
	template <class T> inline mrb_value cast_value_to_ruby(mrb_state* mrb, T value) {

		if constexpr (std::is_same_v<T, mrb_int>) {

			return mrb_fixnum_value(value);

		} else if constexpr (std::is_same_v<T, mrb_float>) {

			return mrb_float_value(mrb, value);

		} else if constexpr (std::is_same_v<T, mrb_bool>) {

			return mrb_bool_value(value);

		} else if constexpr (std::is_same_v<T, char*>) {

			return mrb_str_new(mrb, value, strlen(value));

		} else if constexpr (std::is_same_v<T, mrb_value>) {

			return value;

		} else {

			static_assert(std::false_type::value, "Invalid mruby type given");

		}

	}

	//! TODO: Return mrb_value

	//! Get matching ruby class, e.g. mrb_int for int
	template <class T, class Trait = void> struct CastToRuby { using type = void; };

	template <class T> 
	struct CastToRuby<T, typename std::enable_if<std::is_base_of_v<BaseDefaultWrap, T>>::type> {

		using real_type = typename T::type;
		using type = typename CastToRuby<real_type>::type;

	};

	template <> struct CastToRuby<bool> { using type = mrb_bool; };
	template <> struct CastToRuby<std::string> { using type = char*; };
	template <class T> struct CastToRuby<T, typename std::enable_if<std::is_floating_point_v<T>>::type> { using type = mrb_float; };
	template <class T> struct CastToRuby<T, typename std::enable_if<std::is_integral_v<T>>::type> { using type = mrb_int; };
	template <class T> struct CastToRuby<T, typename std::enable_if<std::conjunction_v<std::is_class<T>, std::negation<std::is_base_of<BaseDefaultWrap, T>>>>::type> { using type = mrb_value; };

	//! Get the return type of a function
	template <class F> struct GetReturnType { using type = void; };

	template <class C, class T, class ... TArgs> struct GetReturnType<T (C::*)(TArgs...)> {

		using type = T;

	};

	template <class C, class ... TArgs> struct GetReturnType<void (C::*)(TArgs...)> {

		using type = void;

	};

	//! Utility function to cast arguments into usable values
	template <class Dest, class C> auto arg_cast(C arg, mrb_state* mrb = nullptr) {

		if constexpr (std::is_same_v<Dest, C>) {

			return arg;

		} else if constexpr (std::is_same_v<Dest, std::string>) {

			return std::string(arg);

		} else if constexpr (std::is_same_v<Dest, char*>) {

			return const_cast<char*>(arg.c_str());

		} else if constexpr (std::is_same_v<Dest, mrb_value>) {

			return mrb_value();

		} else if constexpr (std::conjunction_v<std::is_same<C, mrb_value>, std::is_pointer<Dest>>) {

			return convert_from_object<std::remove_pointer_t<Dest>>(mrb, arg);

		} else if constexpr (std::is_same_v<C, mrb_value>) {

			return *convert_from_object<Dest>(mrb, arg);

		} else {

			return static_cast<Dest>(arg);

		}

	}

	//! Utility function to cast return values into mruby compatible values
	template <class Dest, class C> auto return_cast(C arg, mrb_state* mrb) {

		if constexpr (std::is_same_v<Dest, C>) {

			return arg;

		} else if constexpr (std::is_same_v<Dest, std::string>) {

			return std::string(arg);

		} else if constexpr (std::is_same_v<Dest, char*>) {

			return const_cast<char*>(arg.c_str());

		} else if constexpr (std::is_same_v<Dest, mrb_value>) {

			auto ruby_class = get_class_info_ptr<C>();
			auto new_mruby_obj = mrb_obj_new(mrb, ruby_class, 0, NULL);

			return new_mruby_obj;

		} else if constexpr (std::conjunction_v<std::is_same<C, mrb_value>, std::is_pointer<Dest>>) {

			return convert_from_object<std::remove_pointer_t<Dest>>(mrb, arg);

		} else if constexpr (std::is_same_v<C, mrb_value>) {

			return *convert_from_object<Dest>(mrb, arg);

		} else {

			return static_cast<Dest>(arg);

		}

	}

	template <class C> bool check_for_type(mrb_state* mrb, mrb_value obj) {

		auto expected_class = get_class_info_ptr<C>();

		return mrb_obj_is_kind_of(mrb, obj, expected_class);

	}

	template <class C> void verify_type(mrb_state* mrb, mrb_value obj) {

		if (!check_for_type<C>(mrb, obj)) {

			std::string message = std::string("Object of class ")
				+ std::string(mrb_class_name(mrb, mrb_obj_class(mrb, obj)))
				+ std::string(" is not of class ")
				+ std::string(mrb_class_name(mrb, get_class_info_ptr<C>()));

			mrb_raise(mrb, mrb->eException_class, message.c_str());

		}

	}
	
	//! Initialize and return a tuple of the ruby arguments
	template <class ... TArgs> constexpr auto generate_arg_tuple() {
		//! Generate a tuple of the final mruby types
		std::tuple<CastToRuby<TArgs>::type...> args;

		//! Set the tuple values to their default values if given
		std::apply([](auto&& ...arg) {

			//! Also ensure correct casting to the mruby type
			((arg = arg_cast<CastToRuby<TArgs>::type>(get_default(TArgs()))), ...);

		}, args);

		return args;
	}

	//! Obtain values from ruby function call
	template <class ... TArgs, class ... CastedTypes> inline void get_args_from_tuple(mrb_state* mrb, std::tuple<CastedTypes...>& args) {
		//! If any arguments, get them and store them into the tuple
		if constexpr (sizeof...(TArgs) > 0) {
			std::apply([&mrb](auto& ...arg) {

				//! The format string gets determined automatically from the template arguments
				mrb_get_args(mrb, FormatString<TArgs...>::value, &arg...);

			}, args);
		}

	}

	//! Get a tuple of the mruby values of the args
	template <class ... TArgs> constexpr auto get_raw_args(mrb_state* mrb) {

		auto args = generate_arg_tuple<TArgs...>();
		get_args_from_tuple<TArgs...>(mrb, args);

		return args;

	}

	//! Get a tuple of the C++ values of the args
	template <class ... TArgs> constexpr auto get_converted_args(mrb_state* mrb) {

		auto args = get_raw_args<TArgs...>(mrb);

		auto converted_args = std::apply([&mrb](auto&& ...arg) {

			return std::make_tuple(arg_cast<GetRealType<TArgs>::type>(arg, mrb)...);

		}, args);

		return converted_args;

	}

	//! Now following are function wrappers which should cover about 75%-100% of all needed cases.
	//! Definitely supported are the following argument and return types:
	//!
	//! - int (with default value 0)
	//! - float (with default values 0, except inf and nan, as long as you use the rational wrapper)
	//! - char (with default value 0)
	//! - char* (no default value)
	//! - std::string (no default value)
	//! - bool (with default value false)
	//! - Many classes (no default value)
	//! - Pointers to classes (WARNING: NOT TESTED YET)
	//!
	//! If you want to use any other type (or reference), this will probably not work yet.
	//! Please contact me (Hadeweka) or make a pull request if you find something which doesn't work.
	//! The list may expand in the future if needed.
	//! Remember that this is also still in a somewhat experimental stage.
	//! If in doubt, just write your own wrapper using define_mruby_function to avoid any problems.

	//! TODO: Wrap static functions

	//! Wrap a constructor with arbitrary arguments
	template <class C, class ... TArgs> void wrap_constructor(mrb_state* mrb) {

		auto ruby_class = get_class_info_ptr<C>();

		MrbWrap::define_mruby_function(mrb, ruby_class, "initialize", MRUBY_FUNC {

			auto args = get_converted_args<TArgs...>(mrb);

			//! Generate the desired object with the called arguments
			std::apply([&mrb, self](auto& ...arg) {

				MrbWrap::convert_to_object<C>(mrb, self, arg...);

			}, args);

			return self;

		//! TODO: Maybe change this at some point if it should become relevant
		}, MRB_ARGS_NONE());

	}

	template <class C, auto Member, class ... TArgs> void wrap_member_function(mrb_state* mrb, const char* name) {

		using Spec = typename MemberSpec<Member>;

		auto ruby_class = get_class_info_ptr<C>();

		MrbWrap::define_mruby_function(mrb, ruby_class, name, MRUBY_FUNC {

			auto args = get_converted_args<TArgs...>(mrb);

			auto content = MrbWrap::convert_from_object<C>(mrb, self);

			if constexpr(std::is_void_v<GetReturnType<decltype(Member)>::type>) {

				std::apply([&content](auto& ...arg) {

					((*content).*Member)(arg...);

				}, args);

				return mrb_nil_value();

			} else {

				typename GetReturnType<decltype(Member)>::type return_value = std::apply([&content](auto& ...arg) {

					return ((*content).*Member)(arg...);

				}, args);

				using ret_type = decltype(return_value);
				using casted_ret_type = typename CastToRuby<ret_type>::type;

				auto casted_return_value = return_cast<casted_ret_type>(return_value, mrb);

				if constexpr (std::is_same_v<casted_ret_type, mrb_value>) {

					auto new_value = MrbWrap::convert_from_object<ret_type>(mrb, casted_return_value);
					*new_value = return_value;

				}

				return cast_value_to_ruby(mrb, casted_return_value);

			}

		}, MRB_ARGS_NONE());

	}

	//! Wrap a getter using a member function or object
	template <class C, auto Member> void wrap_getter(mrb_state* mrb, const char* name) {

		auto ruby_class = get_class_info_ptr<C>();

		MrbWrap::define_mruby_function(mrb, ruby_class, name, MRUBY_FUNC {

			auto content = MrbWrap::convert_from_object<C>(mrb, self);

			if constexpr (std::is_member_object_pointer_v<decltype(Member)>) {

				auto return_value = ((*content).*Member);

				using ret_type = decltype(return_value);
				using casted_ret_type = typename CastToRuby<ret_type>::type;
				
				auto casted_return_value = return_cast<casted_ret_type>(return_value, mrb);

				if constexpr (std::is_same_v<casted_ret_type, mrb_value>) {

					auto new_value = MrbWrap::convert_from_object<ret_type>(mrb, casted_return_value);
					*new_value = return_value;

				}

				return cast_value_to_ruby(mrb, casted_return_value);

			} else if constexpr (std::is_member_function_pointer_v<decltype(Member)>) {

				auto return_value = ((*content).*Member)();

				using ret_type = decltype(return_value);
				using casted_ret_type = typename CastToRuby<ret_type>::type;
				
				auto casted_return_value = return_cast<casted_ret_type>(return_value, mrb);

				if constexpr (std::is_same_v<casted_ret_type, mrb_value>) {

					auto new_value = MrbWrap::convert_from_object<ret_type>(mrb, casted_return_value);
					*new_value = return_value;

				}

				return cast_value_to_ruby(mrb, casted_return_value);

			} else {

				//! TODO: Maybe an error here?
				return mrb_nil_value();

			}

		}, MRB_ARGS_NONE());

	}

	//! Wrap a setter using a member function or object
	template <class C, auto Member, class ArgType> void wrap_setter(mrb_state* mrb, const char* name) {

		auto ruby_class = get_class_info_ptr<C>();

		MrbWrap::define_mruby_function(mrb, ruby_class, name, MRUBY_FUNC {

			typename CastToRuby<ArgType>::type new_value;
			mrb_get_args(mrb, FormatString<ArgType>::value, &new_value);

			auto content = MrbWrap::convert_from_object<C>(mrb, self);

			if constexpr (std::is_member_object_pointer_v<decltype(Member)>) {

				((*content).*Member) = arg_cast<ArgType>(new_value);

				return cast_value_to_ruby(mrb, new_value);

			} else if constexpr (std::is_member_function_pointer_v<decltype(Member)>) {

				((*content).*Member)(arg_cast<ArgType>(new_value));

				return cast_value_to_ruby(mrb, new_value);

			} else {

				//! TODO: Maybe an error here?
				return mrb_nil_value();

			}

		}, MRB_ARGS_REQ(1));

	}

}
