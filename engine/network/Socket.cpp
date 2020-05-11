#include "Socket.h"

void setup_ruby_class_socket(mrb_state* mrb, RClass* ruby_module) {

	auto ruby_socket_class = MrbWrap::define_data_class_under(mrb, "Socket", ruby_module);
	auto ruby_socket_status_module = mrb_define_module_under(mrb, ruby_socket_class, "Status");

	MrbWrap::wrap_class_under<sf::TcpSocket>(mrb, "Socket", ruby_module);

	mrb_define_const(mrb, ruby_socket_status_module, "Done", mrb_fixnum_value(static_cast<mrb_int>(sf::Socket::Status::Done)));
	mrb_define_const(mrb, ruby_socket_status_module, "NotReady", mrb_fixnum_value(static_cast<mrb_int>(sf::Socket::Status::NotReady)));
	mrb_define_const(mrb, ruby_socket_status_module, "Partial", mrb_fixnum_value(static_cast<mrb_int>(sf::Socket::Status::Partial)));
	mrb_define_const(mrb, ruby_socket_status_module, "Disconnected", mrb_fixnum_value(static_cast<mrb_int>(sf::Socket::Status::Disconnected)));
	mrb_define_const(mrb, ruby_socket_status_module, "Error", mrb_fixnum_value(static_cast<mrb_int>(sf::Socket::Status::Error)));

	//! TODO: Implement UDP support as optional argument
	MrbWrap::wrap_constructor<sf::TcpSocket>(mrb);

	MrbWrap::define_member_function(mrb, ruby_socket_class, "connect", MRUBY_FUNC {

		char* address;
		mrb_int port;
		mrb_value timeout;	//! TODO: Implement

		mrb_get_args(mrb, "zi|o", &address, &port, &timeout);

		auto socket = MrbWrap::convert_from_object<sf::TcpSocket>(mrb, self);

		auto status_code = socket->connect(sf::IpAddress(address), static_cast<unsigned short>(port), sf::Time::Zero);

		return mrb_fixnum_value(status_code);

	}, MRB_ARGS_ARG(2, 1));

	MrbWrap::wrap_member_function<sf::TcpSocket, &sf::TcpSocket::disconnect>(mrb, "disconnect");

	MrbWrap::define_member_function(mrb, ruby_socket_class, "send_message", MRUBY_FUNC {

		char* message;

		mrb_get_args(mrb, "z", &message);

		auto socket = MrbWrap::convert_from_object<sf::TcpSocket>(mrb, self);

		//! TODO: Implement checks for packets in another method

		auto status_code = socket->send(message, strlen(message));

		return mrb_fixnum_value(status_code);

	}, MRB_ARGS_REQ(1));

	MrbWrap::define_member_function(mrb, ruby_socket_class, "receive", MRUBY_FUNC {

		auto args = MrbWrap::get_converted_args<MRBW_OPT<size_t, 1024>>(mrb);
		auto max_length = std::get<0>(args);

		auto socket = MrbWrap::convert_from_object<sf::TcpSocket>(mrb, self);

		auto received_string = reinterpret_cast<char*>(malloc(max_length * sizeof(char)));
		size_t received_bytes;

		auto status_code = socket->receive(received_string, max_length, received_bytes);

		static auto sym = mrb_intern_static(mrb, "@last_message", strlen("@last_message"));
		mrb_iv_set(mrb, self, sym, mrb_str_new(mrb, received_string, received_bytes));

		return mrb_fixnum_value(status_code);

	}, MRB_ARGS_REQ(1));

	MrbWrap::define_member_function(mrb, ruby_socket_class, "last_message", MRUBY_FUNC {

		static auto sym = mrb_intern_static(mrb, "@last_message", strlen("@last_message"));
		return mrb_iv_get(mrb, self, sym);

	}, MRB_ARGS_NONE());

	MrbWrap::wrap_getter<sf::TcpSocket, &sf::TcpSocket::isBlocking>(mrb, "blocking");
	MrbWrap::wrap_setter<sf::TcpSocket, &sf::TcpSocket::setBlocking, bool>(mrb, "blocking=");

	MrbWrap::define_member_function(mrb, ruby_socket_class, "remote_address", MRUBY_FUNC {

		//! TODO: May need testing

		auto socket = MrbWrap::convert_from_object<sf::TcpSocket>(mrb, self);
		auto address = socket->getRemoteAddress().toString().c_str();

		return mrb_str_new_cstr(mrb, address);

	}, MRB_ARGS_NONE());

	MrbWrap::wrap_getter<sf::TcpSocket, &sf::TcpSocket::getRemotePort>(mrb, "remote_port");
	MrbWrap::wrap_getter<sf::TcpSocket, &sf::TcpSocket::getLocalPort>(mrb, "local_port");
}