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
			while @position.x > SDC.draw_width do
				@position -= SDC.xy(SDC.draw_width, 0)
			end

			while @position.x < 0 do
				@position += SDC.xy(SDC.draw_width, 0)
			end

			while @position.y > SDC.draw_height do
				@position -= SDC.xy(0, SDC.draw_height)
			end

			while @position.y < 0 do
				@position += SDC.xy(0, SDC.draw_height)
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
			overlap_x_pos = (absolute_position.x > SDC.draw_width * 0.5)
			overlap_x_neg = (absolute_position.x < SDC.draw_width * 0.5)
			overlap_y_pos = (absolute_position.y > SDC.draw_height * 0.5)
			overlap_y_neg = (absolute_position.y < SDC.draw_height * 0.5)

			window.draw_translated(sprite, self.z, absolute_position + SDC.xy(0, SDC.draw_height)) if overlap_y_neg
			window.draw_translated(sprite, self.z, absolute_position + SDC.xy(0, -SDC.draw_height)) if overlap_y_pos
			window.draw_translated(sprite, self.z, absolute_position + SDC.xy(SDC.draw_width, 0)) if overlap_x_neg
			window.draw_translated(sprite, self.z, absolute_position + SDC.xy(-SDC.draw_width, 0)) if overlap_x_pos

			window.draw_translated(sprite, self.z, absolute_position + SDC.xy(SDC.draw_width, SDC.draw_height)) if overlap_x_neg && overlap_y_neg
			window.draw_translated(sprite, self.z, absolute_position + SDC.xy(SDC.draw_width, -SDC.draw_height)) if overlap_x_neg && overlap_y_pos
			window.draw_translated(sprite, self.z, absolute_position + SDC.xy(-SDC.draw_width, SDC.draw_height)) if overlap_x_pos && overlap_y_neg
			window.draw_translated(sprite, self.z, absolute_position + SDC.xy(-SDC.draw_width, -SDC.draw_height)) if overlap_x_pos && overlap_y_pos
		end

	end
end