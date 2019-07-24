# Edit this file to define entities for your game

class TestEntity < Entity

	add_box("Hello")
	add_box("Bla", index: 2)

	add_texture(Texture.new.load_from_file("assets/graphics/test/Chishi.png", IntRect.new(0, 0, 50, 50)), index: 0)	# TODO: Simplify this to something like add_texture_from_file("path...", index = 1)
	add_sprite(texture_index: 0, index: 0)

	def move_sprite(sprite_index, difference)
		@sprites[sprite_index].position += difference
	end

	def move_sprite_to(sprite_index, coordinates)
		@sprites[sprite_index].position = coordinates
	end

	def sprite_position(sprite_index)
		return @sprites[sprite_index].position
	end

end