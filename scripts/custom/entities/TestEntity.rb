class TestEntity < Entity
	add_shape(index: 0, type: ShapeCircle, radius: 25.0)
	add_box(index:0, size: Coordinates.new(25.0, 25.0))

	add_texture(index: 0, filename: "assets/graphics/test/Chishi.png", rect: IntRect.new(0, 0, 50, 50))
	add_sprite(index: 0, texture_index: 0, offset: Coordinates.new(-25.0, -25.0))

	set_hitshape(index: 7, shape_index: 0, damage: 1)
	set_hurtshape(index: 13, shape_index: 0)

	def update
		physics if !@parent
	end
end