module ShooterTest
	class Particle

		attr_accessor :gone, :pos, :velocity, :color, :lifetime, :z, :shape, :texture_index

		def initialize(texture_index: nil, shape: nil, lifetime: 1, z: 0, position: SDC.xy, velocity: SDC.xy, color: SDC::Color.new(255, 255, 255, 255), &update_block)
			@lifetime = lifetime
			@gone = false
			@z = z
			@position = position
			@velocity = velocity
			@update_block = update_block
			@shape = shape
			@texture_index = texture_index
			@color = color
		end

		def update
			@lifetime -= 1
			@gone = true if @lifetime <= 0
			@position += @velocity * SDC.game.dt

			while @position.x > SDC.window.width do
				@position -= SDC.xy(SDC.window.width, 0)
			end

			while @position.x < 0 do
				@position += SDC.xy(SDC.window.width, 0)
			end

			while @position.y > SDC.window.height do
				@position -= SDC.xy(0, SDC.window.height)
			end

			while @position.y < 0 do
				@position += SDC.xy(0, SDC.window.height)
			end

			@update_block&.call
		end

		def draw(window)
			if @shape then
				@shape.fill_color = @color
				window.draw_translated(@shape, @z, @position)

			elsif @texture_index then
				# TODO
				SDC.draw_texture(index: @texture_index, z: @z, coordinates: @position, window: window)
			end
		end

	end
end