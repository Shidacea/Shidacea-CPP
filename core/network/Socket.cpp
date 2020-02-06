#include "Socket.h"

mrb_value ruby_socket_connect(mrb_state* mrb, mrb_value self) {

	char* address;
	mrb_int port;
	mrb_value timeout;	//! TODO: Implement

	mrb_get_args(mrb, "zi|o", &address, &port, &timeout);

	auto socket = MrbWrap::convert_from_object<sf::TcpSocket>(mrb, self);

	auto status_code = socket->connect(sf::IpAddress(address), static_cast<unsigned short>(port), sf::Time::Zero);

	return mrb_fixnum_value(status_code);

}

mrb_value ruby_socket_disconnect(mrb_state* mrb, mrb_value self) {

	auto socket = MrbWrap::convert_from_object<sf::TcpSocket>(mrb, self);

	socket->disconnect();

	return mrb_nil_value();

}

mrb_value ruby_socket_send_message(mrb_state* mrb, mrb_value self) {

	char* message;

	mrb_get_args(mrb, "z", &message);

	auto socket = MrbWrap::convert_from_object<sf::TcpSocket>(mrb, self);

	//! TODO: Implement checks for packets in another method

	auto status_code = socket->send(message, strlen(message));

	return mrb_fixnum_value(status_code);

}

mrb_value ruby_socket_receive(mrb_state* mrb, mrb_value self) {

	mrb_int max_length = 1024;

	mrb_get_args(mrb, "i", &max_length);

	auto socket = MrbWrap::convert_from_object<sf::TcpSocket>(mrb, self);

	auto received_string = reinterpret_cast<char*>(malloc(static_cast<size_t>(max_length)*sizeof(char)));
	size_t received_bytes;

	auto status_code = socket->receive(received_string, static_cast<size_t>(max_length), received_bytes);

	static auto sym = mrb_intern_static(mrb, "@last_message", strlen("@last_message"));
	mrb_iv_set(mrb, self, sym, mrb_str_new(mrb, received_string, received_bytes));

	return mrb_fixnum_value(status_code);

}

mrb_value ruby_socket_last_message(mrb_state* mrb, mrb_value self) {

	static auto sym = mrb_intern_static(mrb, "@last_message", strlen("@last_message"));
	return mrb_iv_get(mrb, self, sym);

}

mrb_value ruby_socket_blocking(mrb_state* mrb, mrb_value self) {

	auto socket = MrbWrap::convert_from_object<sf::TcpSocket>(mrb, self);
	return mrb_bool_value(socket->isBlocking());

}

mrb_value ruby_socket_blocking_equals(mrb_state* mrb, mrb_value self) {

	mrb_bool blocking;
	mrb_get_args(mrb, "b", &blocking);

	auto socket = MrbWrap::convert_from_object<sf::TcpSocket>(mrb, self);
	socket->setBlocking(blocking);

	return mrb_bool_value(blocking);

}

mrb_value ruby_socket_remote_address(mrb_state* mrb, mrb_value self) {

	//! TODO: May need testing

	auto socket = MrbWrap::convert_from_object<sf::TcpSocket>(mrb, self);
	auto address = socket->getRemoteAddress().toString().c_str();

	return mrb_str_new_cstr(mrb, address);

}

mrb_value ruby_socket_remote_port(mrb_state* mrb, mrb_value self) {

	auto socket = MrbWrap::convert_from_object<sf::TcpSocket>(mrb, self);
	return mrb_fixnum_value(socket->getRemotePort());

}

mrb_value ruby_socket_local_port(mrb_state* mrb, mrb_value self) {

	auto socket = MrbWrap::convert_from_object<sf::TcpSocket>(mrb, self);
	return mrb_fixnum_value(socket->getLocalPort());

}

void setup_ruby_class_socket(mrb_state* mrb, RClass* ruby_module) {

	auto ruby_socket_class = MrbWrap::define_data_class_under(mrb, "Socket", ruby_module);
	auto ruby_socket_status_module = mrb_define_module_under(mrb, ruby_socket_class, "Status");

	mrb_define_const(mrb, ruby_socket_status_module, "Done", mrb_fixnum_value(static_cast<mrb_int>(sf::Socket::Status::Done)));
	mrb_define_const(mrb, ruby_socket_status_module, "NotReady", mrb_fixnum_value(static_cast<mrb_int>(sf::Socket::Status::NotReady)));
	mrb_define_const(mrb, ruby_socket_status_module, "Partial", mrb_fixnum_value(static_cast<mrb_int>(sf::Socket::Status::Partial)));
	mrb_define_const(mrb, ruby_socket_status_module, "Disconnected", mrb_fixnum_value(static_cast<mrb_int>(sf::Socket::Status::Disconnected)));
	mrb_define_const(mrb, ruby_socket_status_module, "Error", mrb_fixnum_value(static_cast<mrb_int>(sf::Socket::Status::Error)));

	//! TODO: Implement UDP support as optional argument
	MrbWrap::wrap_constructor<sf::TcpSocket>(mrb, ruby_socket_class);

	mrb_define_method(mrb, ruby_socket_class, "connect", ruby_socket_connect, MRB_ARGS_ARG(2, 1));
	mrb_define_method(mrb, ruby_socket_class, "disconnect", ruby_socket_disconnect, MRB_ARGS_NONE());
	mrb_define_method(mrb, ruby_socket_class, "send_message", ruby_socket_send_message, MRB_ARGS_REQ(1));
	mrb_define_method(mrb, ruby_socket_class, "receive", ruby_socket_receive, MRB_ARGS_OPT(1));
	mrb_define_method(mrb, ruby_socket_class, "last_message", ruby_socket_last_message, MRB_ARGS_NONE());
	mrb_define_method(mrb, ruby_socket_class, "blocking?", ruby_socket_blocking, MRB_ARGS_NONE());
	mrb_define_method(mrb, ruby_socket_class, "blocking=", ruby_socket_blocking_equals, MRB_ARGS_REQ(1));
	mrb_define_method(mrb, ruby_socket_class, "remote_address", ruby_socket_remote_address, MRB_ARGS_NONE());
	mrb_define_method(mrb, ruby_socket_class, "remote_port", ruby_socket_remote_port, MRB_ARGS_NONE());
	mrb_define_method(mrb, ruby_socket_class, "local_port", ruby_socket_local_port, MRB_ARGS_NONE());

}