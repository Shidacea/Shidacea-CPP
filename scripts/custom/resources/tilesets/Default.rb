tileset = Tileset.new
texture = Texture.new

8.times {tileset.add_tile(SDC::CustomTile.new)}
tileset.tiles[3].solid = true
tileset.tiles[4].solid = true
tileset.tiles[5].solid = true

texture.load_from_file("assets/graphics/maptest/Tileset.png")
tileset.link_texture(texture)

SDC::Data::add_tileset(tileset)
SDC::Data::add_texture(texture)