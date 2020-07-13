require "./utility/MrbWrapDoc.rb"

m = MrbWrapDoc.new(top_module: "SDC")

m.parse_file("engine/audio/Music.cpp")
m.parse_file("engine/audio/Sound.cpp")
m.parse_file("engine/audio/SoundBuffer.cpp")
m.parse_file("engine/graphics/Color.cpp")
m.parse_file("engine/graphics/DrawShape.cpp")

m.generate_doc("engine_docs/")