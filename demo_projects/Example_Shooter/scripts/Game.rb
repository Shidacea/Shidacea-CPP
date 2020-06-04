# Structure for temporary game data
# Feel free to customize and extend this class

module ShooterTest
	class Game < SDC::BaseGame

		def initialize
			# Initialize base game values
			super
			@dt = 0.5
		end

	end
end