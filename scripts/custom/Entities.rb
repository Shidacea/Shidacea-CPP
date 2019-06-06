# Edit this file to define entities for your game

class TestEntity < Entity

	attr_reader :boxes

	add_box("Hello")
	add_box("Bla", index: 2)
	
	add_texture(Texture.new.load_from_file("assets/graphics/test/Chishi.png"))

	def at_init
		link_texture(@textures[0])
	end

end