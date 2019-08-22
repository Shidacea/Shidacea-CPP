# Shidacea 2D Game Engine

What you see is the game engine Shidacea, decoupled from my game Inuhh Shinvasion 2.

This repository is a template for game projects. Depending on your level of knowledge and desire to mess around with my code, you can do several things:

* Just change the main mruby scripts and some configuration files to build your game
* Change the core mruby scripts and add new ones in the C++ core files
* Change stuff in the C++ wrapper files
* Dive into mruby and SFML and modify them
* Disassemble the whole thing, write some assembly code and segfault yourself into oblivion (not recommended)

Overall, this engine was designed to appeal to many people instead of a single group. 
However, a certain degree of knowledge about Ruby is needed.

# Idea and history

This project was inspired by the RPG Maker series from Enterbrain and complications with previous games written in Ruby. 
It aims to combine the beauty of Ruby for scripting with the speed of C++ for critical procedures while maintaining platform independency.

The original purpose of this engine was to serve as a backbone to Inuhh Shinvasion 2, but it quickly became its own thing.
Even if the original idea was to create a Jump'n'run game, it can technically be used for any 2D project.

# Requirements

The following programs need to be installed:

* CMake
* Ruby
* Bison

For Windows you need to make sure that the paths leading to ruby.exe and bison.exe are in the PATH variable.
CMake can be obtained using Visual Studio, which is the recommended option.
Also make sure to avoid path names with spaces in them, as mruby might fail to compile otherwise.

# Properties

* Platform independency (technically, but not tested yet)
* Scripting support using mruby
* Wrapped SFML classes for use with mruby
* Modding support

# Features

* Simple event handling
* Simple state machine for scenes
* Basic game classes
* Wrapped ImGui methods for debugging

# Planned features

* Game physics
* Collision detection routines
* A special level editor written using this engine
* Examples

# Caveats

## Submodules

If you download this repository, make sure to download the submodules as well, since a simple download won't include them.
The best way to use Shidacea is to fork it and use Git for maintaining it and updating the submodules.

## Loading other mruby script files

The ruby instruction `require` is NOT available (adding it as a gem would be possible, but not applicable to the concept of pre-compiled bytecode).
This means that you need to write files with no direct dependencies, as they could be loaded in an arbitrary order.
Functions may reference other classes, but you should put inherited classes inside the file of their superclass.

The order of loading the script folders is: core -> custom/scenes -> custom/entities -> custom/Main.rb

## 64 bit support

At the moment, this program doesn't support compilation in 64 bit yet.