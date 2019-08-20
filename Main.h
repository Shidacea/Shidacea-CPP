#pragma once

//! Mandatory includes if you want anything to work at all

#include <filesystem>
#include <iostream>

#include "Helper.h"

//! Includes for compiled Ruby scripts
//! If you want to add any compiled Ruby script, you need to add it here

#ifdef NDEBUG
#include "compiled_scripts/CompiledRubyCore.h"
#include "compiled_scripts/CompiledRubyCustomScenes.h"
#include "compiled_scripts/CompiledRubyCustomEntities.h"
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
#include "Events.h"
#include "Window.h"
#include "Texture.h"
#include "Map.h"
#include "ImGuiWrapper.h"
