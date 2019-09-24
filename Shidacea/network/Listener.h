#pragma once

#include "Helper.h"
#include "ResourceManager.h"

#include <SFML/Network.hpp>

mrb_value ruby_listener_init(mrb_state* mrb, mrb_value self);
mrb_value ruby_listener_listen(mrb_state* mrb, mrb_value self);
mrb_value ruby_listener_accept(mrb_state* mrb, mrb_value self);

void setup_ruby_class_listener(mrb_state* mrb);