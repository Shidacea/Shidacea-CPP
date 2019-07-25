# Edit this file to define entities for your game

class TestEntity < Entity
	add_shape(type: ShapeCircle, radius: 25.0)
	add_box(size: Coordinates.new(25.0, 25.0))

	add_texture(index: 0, filename: "assets/graphics/test/Chishi.png", rect: IntRect.new(0, 0, 50, 50))
	add_sprite(index: 0, texture_index: 0)

	# Debug methods to be implemented in main Entity class at a later time

	def move_sprite(sprite_index, difference)
		@sprites[sprite_index].position += difference
	end

	def move_sprite_to(sprite_index, coordinates)
		@sprites[sprite_index].position = coordinates
	end

	def sprite_position(sprite_index)
		return @sprites[sprite_index].position
	end

	def get_shape(shape_index)
		return @shapes[shape_index]
	end

end