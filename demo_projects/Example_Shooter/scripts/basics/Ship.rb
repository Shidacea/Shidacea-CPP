module ShooterTest
	class Ship < SDC::Entity
	
		# Define new properties
		self.define_class_property :health, default: 0
		self.define_class_property :shield, default: 0
		self.define_class_property :weapon, default: nil
		self.define_class_property :drive, default: nil
		self.define_class_property :max_speed, default: 50 # TODO: Put this into drive

		attr_reader :angle

		def at_init
			@angle = 0.0
		end

		def rotate(angle_difference)
			@angle += angle_difference
			@sprites[0].rotation += angle_difference
		end

		def direction
			return SDC.xy(Math::sin(@angle / 180.0 * Math::PI), -Math::cos(@angle / 180.0 * Math::PI))
		end

		def direction_normal
			return SDC.xy(Math::cos(@angle / 180.0 * Math::PI), Math::sin(@angle / 180.0 * Math::PI))
		end

		def custom_update
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

			speed = @velocity.squared_norm
			if speed > self.max_speed then
				@velocity *= (self.max_speed / speed)
			end
		end

		def has_max_speed
			return @velocity.squared_norm >= self.max_speed
		end

		def update_shapes
			
		end

		def custom_sprite_draw(window, sprite)
			window.draw_translated(sprite, self.z, absolute_position + SDC.xy(0, window.height))
			window.draw_translated(sprite, self.z, absolute_position + SDC.xy(0, -window.height))
			window.draw_translated(sprite, self.z, absolute_position + SDC.xy(window.width, 0))
			window.draw_translated(sprite, self.z, absolute_position + SDC.xy(-window.width, 0))
			window.draw_translated(sprite, self.z, absolute_position + SDC.xy(window.width, window.height))
			window.draw_translated(sprite, self.z, absolute_position + SDC.xy(window.width, -window.height))
			window.draw_translated(sprite, self.z, absolute_position + SDC.xy(-window.width, window.height))
			window.draw_translated(sprite, self.z, absolute_position + SDC.xy(-window.width, -window.height))
		end

	end
end