require "./utility/MrbWrapDoc.rb"

m = MrbWrapDoc.new(top_module: "SDC")

m.parse_file("engine/audio/Music.cpp")
m.parse_file("engine/audio/Sound.cpp")
m.parse_file("engine/audio/SoundBuffer.cpp")

m.parse_file("engine/graphics/Color.cpp")
m.parse_file("engine/graphics/DrawShape.cpp")
m.parse_file("engine/graphics/Font.cpp")
m.parse_file("engine/graphics/RenderStates.cpp")
m.parse_file("engine/graphics/Sprite.cpp")
m.parse_file("engine/graphics/Text.cpp")
m.parse_file("engine/graphics/Texture.cpp")
m.parse_file("engine/graphics/View.cpp")
m.parse_file("engine/graphics/Window.cpp")

m.parse_file("engine/internal/Coordinates.cpp")

m.generate_doc("engine_docs/")