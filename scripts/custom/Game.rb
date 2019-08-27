# Structure for temporary game data
# Feel free to customize and extend this class

class Game

	attr_reader :dt
	attr_accessor :gravity

	def initialize
		# Physics time step
		@dt = 0.01

		# Gravity
		@gravity = Coordinates.new(0, 9.81)
	end

end