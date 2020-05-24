#pragma once

#include "Version.h"

//! Mandatory includes if you want anything to work at all

#include <filesystem>
#include <iostream>

//! Uncomment the following line if you want to allow dynamic script loading
//! WARNING: Will probably be removed

//#define SHIDACEA_DYNAMIC_LOADING

//! Uncomment the following line if you want to allow mod loading

//#define SHIDACEA_MOD_LOADING

#include "MrbWrap.h"
#include "MrbLoad.h"

//! Includes for compiled Ruby scripts
//! If you want to add any compiled Ruby script, you need to add it here

#include "compiled_scripts/scripts_include_sdclib.h"
#include "compiled_scripts/scripts_include_frontend.h"

//! Other included classes and functions
//! These may also include wrapped classes and functions

#include "Script.h"

#ifndef SHIDACEA_EXCLUDE_SFML

#include "RenderStates.h"
#include "Color.h"
#include "Shape.h"
#include "IntRect.h"
#include "FloatRect.h"
#include "Coordinates.h"
#include "Sprite.h"
#include "Socket.h"
#include "Listener.h"
#include "Events.h"
#include "View.h"
#include "Window.h"
#include "Font.h"
#include "Text.h"
#include "Texture.h"
#include "MapLayer.h"
#include "Tileset.h"
#include "Music.h"
#include "SoundBuffer.h"
#include "Sound.h"

#ifndef SHIDACEA_EXCLUDE_IMGUI
#include "ImGuiWrapper.h"
#endif

#endif