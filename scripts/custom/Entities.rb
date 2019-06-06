# Edit this file to define entities for your game

class TestEntity < Entity

	attr_reader :boxes

	add_box("Hello")
	add_box("Bla", index: 2)

	def initialize
		super
	end

end