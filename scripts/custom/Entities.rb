# Edit this file to define entities for your game

class TestEntity < Entity

	attr_accessor :sprite	 # Only for debug

	add_box("Hello")
	add_box("Bla", index: 2)
	
	add_texture(Texture.new.load_from_file("assets/graphics/test/Chishi.png", IntRect.new(0, 0, 50, 50)))	# TODO: Simplify this to something like add_texture_from_file("path...", index = 1)

	def at_init
		@sprite = Sprite.new(@resource_manager)
		@sprite.link_texture(@textures[0])
	end

	def draw(window)
		@sprite.draw(window)
	end

end