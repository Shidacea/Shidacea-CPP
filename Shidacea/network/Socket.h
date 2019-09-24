#pragma once

#include "Helper.h"
#include "ResourceManager.h"

#include <SFML/Network.hpp>

mrb_value ruby_socket_init(mrb_state* mrb, mrb_value self);
mrb_value ruby_socket_connect(mrb_state* mrb, mrb_value self);
mrb_value ruby_socket_disconnect(mrb_state* mrb, mrb_value self);
mrb_value ruby_socket_send_message(mrb_state* mrb, mrb_value self);
mrb_value ruby_socket_receive(mrb_state* mrb, mrb_value self);
mrb_value ruby_socket_last_message(mrb_state* mrb, mrb_value self);
mrb_value ruby_socket_blocking(mrb_state* mrb, mrb_value self);
mrb_value ruby_socket_blocking_equals(mrb_state* mrb, mrb_value self);
mrb_value ruby_socket_remote_address(mrb_state* mrb, mrb_value self);
mrb_value ruby_socket_remote_port(mrb_state* mrb, mrb_value self);
mrb_value ruby_socket_local_port(mrb_state* mrb, mrb_value self);

void setup_ruby_class_socket(mrb_state* mrb);