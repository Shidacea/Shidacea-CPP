# Base entity class

class Entity

	# Class methods for adding different objects to any entity
	
	def self.add_box(box, index: nil)
		@boxes = SpecialContainer.new if !@boxes
		@boxes.add(box, index)
	end

	def self.add_shape(shape, index: nil)
		@shapes = SpecialContainer.new if !@shapes
		@shapes.add(shape, index)
	end

	def self.add_texture(texture, index: nil)
		@textures = SpecialContainer.new if !@textures
		@textures.add(texture, index)
	end

	def self.add_sprite(texture_index: nil, index: nil)
		@sprites = SpecialContainer.new if !@sprites
		@sprites.add([texture_index], index)
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

				if texture_index then
					if texture_index >= 0 && texture_index < @textures.size then
						@sprites[i].link_texture(@textures[texture_index])
					else
						raise("Texture index for sprite index #{i} is out of range: #{texture_index}")
					end
				end
			end
		end
	end

	# Actual instance methods which should not be changed

	def initialize(resource_manager)
		@resource_manager = resource_manager

		load_boxes
		load_shapes
		load_textures
		load_sprites

		at_init
	end

	def draw(window)
		@sprites.each do |sprite|
			sprite.draw(window)
		end
	end

	# Custom routines which can be redefined for inherited objects

	def at_init

	end

	def update

	end

	def custom_draw

	end

end