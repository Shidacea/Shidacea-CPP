# Structure for temporary game data
# Feel free to customize and extend this class

class Game

	attr_reader :dt, :meter
	attr_accessor :gravity

	def initialize
		# Distance unit in pixels
		@meter = 50.0

		# Physics time step
		@dt = 1.0 / 60.0

		# Gravity
		@gravity = Coordinates.new(0, 60.0) * @meter
	end

end