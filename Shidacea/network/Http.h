#pragma once

#include "Helper.h"
#include "ResourceManager.h"

#include <SFML/Network.hpp>

mrb_value ruby_http_init(mrb_state* mrb, mrb_value self);

void setup_ruby_class_http(mrb_state* mrb);