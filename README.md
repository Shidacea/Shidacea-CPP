# Shidacea 2D Game Engine

What you see is the game engine Shidacea, decoupled from my game Inuhh Shinvasion 2.

This repository is a template for game projects. Depending on your level of knowledge and desire to mess around with my code, you can do several things:

* Just change the main mruby scripts and some configuration files to build your game
* Change the core mruby scripts and add new ones in the C++ core files
* Change stuff in the C++ wrapper files
* Dive into mruby and SFML and modify them
* Disassemble the whole thing, write some assembly code and segfault yourself into oblivion (not recommended)

# Requirements

The following programs need to be installed:

* CMake
* Ruby
* Bison

For Windows you need to make sure that the paths leading to ruby.exe and bison.exe are in the PATH variable.
CMake can be obtained using Visual Studio, which is the recommended option.
Also make sure to avoid path names with spaces in them, as mruby might fail to compile otherwise.

# Features

* Platform independency (technically, but not tested yet)
* Scripting support using mruby
* Wrapped SFML classes for use with mruby
* Basic game classes
* Simple event handling
* Simple state machine for scenes
* Modding support

# Planned features

* Map routines (Tiled support)
* Imgui support (if I can get it to work)
* Game physics
* Collision detection routines

# Caveats

## Script naming conventions

Do not give mruby scripts same names, even if they are in different subdirectories of the `scripts`-directory. The subdirectory structure is ONLY for convenience reasons! The final build scripts will NOT follow this structure!

It is adviced to create a separate directory inside the scripts-directory for your own additions if you plan to add new scripts. Also use prefixes for your files, e.g. `scripts/my_project/my_project_test.rb` instead of `scripts/custom/test.rb`.
