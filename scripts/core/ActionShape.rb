# Classes for specialized shapes.
# There are two different types of shapes which are used in this engine.
# It is of course possible, to extend them, but their implementation needs to be done specifically.

class Actionshape

	attr_accessor :active, :shape_index

	def initialize(active: true, shape_index: nil)
		@active = active
		@shape_index = shape_index
	end

end

# Hitshapes are shapes which are able to inflict damage or other conditions

class Hitshape < Actionshape

	attr_accessor :damage

	def initialize(active: true, shape_index: nil, damage: 0)
		super(active: active, shape_index: shape_index)
		@damage = damage
	end

end

# Hurtshapes are receptors for damage and interactions

class Hurtshape < Actionshape

	def initialize(active: true, shape_index: nil)
		super(active: active, shape_index: shape_index)
	end

end