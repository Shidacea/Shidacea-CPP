# Base entity class

class Entity

	# Accessor methods for content arrays (except for textures)

	attr_accessor :sprites, :boxes, :shapes, :hitshapes, :hurtshapes

	# Other accessor methods

	attr_accessor :position, :velocity

	attr_reader :magic_number

	# Class methods for adding different objects to any entity
	
	def self.add_box(index: nil, offset: Coordinates.new, size: nil)
		if !size then
			raise("No size given for box with index #{index}")
		end

		@boxes = SpecialContainer.new if !@boxes
		@boxes.add(ShapeBox.new(offset, size), index)
	end

	def self.add_shape(index: nil, type: nil, offset: Coordinates.new, radius: nil, size: nil, semiaxes: nil, direction: nil)
		@shapes = SpecialContainer.new if !@shapes
		shape = nil

		if type == ShapePoint then
			shape = type.new(offset)
		elsif type == ShapeLine then
			raise("Direction not defined for line shape with index #{index}") if !direction
			shape = type.new(offset, direction)
		elsif type == ShapeCircle then
			raise("Radius not defined for line shape with index #{index}") if !radius
			shape = type.new(offset, radius)
		elsif type == ShapeBox then
			raise("Size not defined for line shape with index #{index}") if !size
			shape = type.new(offset, size)
		elsif type == ShapeTriangle then
			# TODO
			shape = type.new
		elsif type == ShapeQuadrangle then
			# TODO
			shape = type.new
		elsif type == ShapeEllipse then
			raise("Semiaxes not defined for line shape with index #{index}") if !semiaxes
			shape = type.new(offset, axes)
		else
			raise("Unknown shape type #{type} for shape index #{index}")
		end

		@shapes.add(shape, index)
	end

	def self.add_texture(index: nil, filename: nil, rect: nil)
		if !filename then
			raise("No filename given for texture with index #{index}")
		end
		
		@textures = SpecialContainer.new if !@textures
		@textures.add(Texture.new.load_from_file(filename, rect), index)
	end

	def self.add_sprite(index: nil, texture_index: nil, offset: Coordinates.new)
		@sprites = SpecialContainer.new if !@sprites
		@sprites.add([texture_index, offset], index)
	end

	def self.set_hitshape(index: nil, active: true, shape_index: nil, damage: 0)
		@hitshapes = SpecialContainer.new if !@hitshapes
		@hitshapes.add(Hitshape.new(damage: damage, shape_index: shape_index, active: active), index)
	end

	def self.set_hurtshape(index: nil, active: true, shape_index: nil)
		@hurtshapes = SpecialContainer.new if !@hurtshapes
		@hurtshapes.add(Hurtshape.new(active: active, shape_index: shape_index), index)
	end

	# Class getter methods for utility and code readability

	def self.all_boxes
		@boxes = SpecialContainer.new if !@boxes
		return @boxes
	end

	def self.all_shapes
		@shapes = SpecialContainer.new if !@shapes
		return @shapes
	end

	def self.all_textures
		@textures = SpecialContainer.new if !@textures
		return @textures
	end

	def self.all_sprites
		@sprites = SpecialContainer.new if !@sprites
		return @sprites
	end

	def self.all_hitshapes
		@hitshapes = SpecialContainer.new if !@hitshapes
		return @hitshapes
	end

	def self.all_hurtshapes
		@hurtshapes = SpecialContainer.new if !@hurtshapes
		return @hurtshapes
	end

	# Create local copies of all boxes/shapes/...

	def load_boxes
		@boxes = []
		all_boxes = self.class.all_boxes

		0.upto(all_boxes.size - 1) do |i|
			element = all_boxes.get(i)

			@boxes[i] = element.dup if element
		end
	end

	def load_shapes
		@shapes = []
		all_shapes = self.class.all_shapes

		0.upto(all_shapes.size - 1) do |i|
			element = all_shapes.get(i)

			@shapes[i] = element.dup if element
		end
	end

	def load_textures
		@textures = []
		all_textures = self.class.all_textures

		0.upto(all_textures.size - 1) do |i|
			element = all_textures.get(i)

			# Don't duplicate textures but use a reference instead!
			# Textures should not be changed, but the internal sprite properties may be changed in exchange.
			# This is due to the internal structure of SFML in which sprites are much more variable than textures.
			# Also textures are 'heavy' objects, while sprites are relatively lightweighted.
			@textures[i] = element if element	
		end
	end

	def load_sprites
		@sprites = []
		all_sprites = self.class.all_sprites

		0.upto(all_sprites.size - 1) do |i|
			element = all_sprites.get(i)

			# Again this time, the objects should not be copied to avoid useless memory consumption

			if element then
				texture_index = element[0]
				@sprites[i] = Sprite.new(@resource_manager)
				@sprites[i].position = element[1]

				if texture_index then
					if texture_index >= 0 && texture_index < @textures.size then
						@sprites[i].link_texture(@textures[texture_index])
					else
						raise("Texture index for sprite index #{i} is out of range: #{texture_index}")
					end
				end
			end
		end

		def load_hitshapes
			@hitshapes = []
			all_hitshapes = self.class.all_hitshapes

			0.upto(all_hitshapes.size - 1) do |i|
				element = all_hitshapes.get(i)

				@hitshapes[i] = element.dup if element
			end
		end

		def load_hurtshapes
			@hurtshapes = []
			all_hurtshapes = self.class.all_hurtshapes

			0.upto(all_hurtshapes.size - 1) do |i|
				element = all_hurtshapes.get(i)

				@hurtshapes[i] = element.dup if element
			end
		end

	end

	# Actual instance methods which should not be changed

	def initialize(resource_manager)
		@resource_manager = resource_manager

		initialization_procedure
	end

	def initialization_procedure
		@parent = nil
		@children = []
		@position = Coordinates.new
		@velocity = Coordinates.new
		@acceleration = Coordinates.new

		# Set a magic number to identify parent-child-structures
		@magic_number = self.object_id

		load_boxes
		load_shapes
		load_textures
		load_sprites
		load_hitshapes
		load_hurtshapes

		at_init
	end

	def physics
		accelerate($game.gravity)

		@velocity += @acceleration * $game.dt
		@position += @velocity * $game.dt

		# Debug floor
		if @position.y > 500.0 then
			@position.y = 500.0
			@velocity.y = 0.0
		end

		@acceleration.x = 0.0
		@acceleration.y = 0.0
	end

	def accelerate(vector)
		@acceleration += vector
	end

	def absolute_position
		return (@parent ? @position + @parent.absolute_position : @position)
	end

	def set_parent(entity)
		@parent = entity
		broadcast_magic_number(entity.magic_number)
	end

	def set_child(entity)
		@children.push(entity)
		entity.set_parent(self)
	end

	def broadcast_magic_number(number)
		@magic_number = number
		@children.each {|child| child.cascade_magic_number(number)}
	end

	def test_box_collision_with(other_entity)
		# Avoid collisions between identical entities and its children
		return nil if magic_number == other_entity.magic_number

		@boxes.each do |box|
			other_entity.boxes.each do |other_box|
				result = Collider.test(box, absolute_position, other_box, other_entity.absolute_position)
				return other_box if result
			end
		end

		return nil
	end

	def test_shape_collision_with(other_entity)
		return nil if magic_number == other_entity.magic_number

		@shapes.each do |shape|
			other_entity.shapes.each do |other_shape|
				result = Collider.test(shape, absolute_position, other_shape, other_entity.absolute_position)
				return other_shape if result
			end
		end

		return nil
	end

	def get_colliding_action_shapes_with(other_entity)
		return nil if magic_number == other_entity.magic_number

		# TODO: Get all hurtshapes of this entity and the respective hitshapes of the other entity colliding with them.
		# TODO: Also implement hooks and methods for how to handle these.
	end

	def draw(window)
		# This function draws each sprite at its designated position
		# The offset of the sprite position relative to the entity position is included

		@sprites.each do |sprite|
			window.draw_translated(sprite, absolute_position)
		end
	end

	# Custom routines which can be redefined for inherited objects

	def at_init

	end

	def update

	end

	def custom_draw

	end

	def at_entity_collision(other_entity, hurtboxes)

	end

	def at_tile_collision(tile)

	end

end