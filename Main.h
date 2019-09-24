#pragma once

constexpr char* VERSION = "0.0.1d";

//! Mandatory includes if you want anything to work at all

#include <filesystem>
#include <iostream>

//! Uncomment the following line if you want to allow dynamic script loading

//#define DYNAMIC_LOADING

//! Uncomment the following line if you want to allow mod loading

//#define MOD_LOADING

#include "Definitions.h"
#include "Helper.h"

//! Includes for compiled Ruby scripts
//! If you want to add any compiled Ruby script, you need to add it here

#ifdef NDEBUG
#include "compiled_scripts/CompiledRubyCore.h"
#include "compiled_scripts/CompiledRubyCustomScenes.h"
#include "compiled_scripts/CompiledRubyCustomEntities.h"
#include "compiled_scripts/CompiledRubyGame.h"
#include "compiled_scripts/CompiledRubyMain.h"
#endif

//! Other included classes and functions
//! These may also include wrapped classes and functions

#include "ResourceManager.h"
#include "RenderStates.h"
#include "Shape.h"
#include "IntRect.h"
#include "Coordinates.h"
#include "Sprite.h"
#include "Socket.h"
#include "Listener.h"
#include "Http.h"
#include "Events.h"
#include "Window.h"
#include "Texture.h"
#include "MapLayer.h"
#include "ImGuiWrapper.h"
