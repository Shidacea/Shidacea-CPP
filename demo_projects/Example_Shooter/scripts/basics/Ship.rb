module ShooterTest
	class Ship < SDC::Entity
	
		# Define new properties
		self.define_class_property :health, default: 0
		self.define_class_property :shield, default: 0
		self.define_class_property :weapon, default: nil
		self.define_class_property :drive, default: :CombustionDrive
		self.define_class_property :z, default: Z_SHIP

		attr_reader :angle

		def at_init
			@angle = 0.0
			@drives = []
			add_drive(self.drive)

			@drive_index = 0
		end

		def selected_drive
			return @drives[@drive_index]
		end

		def add_drive(drive_symbol)
			@drives.push(ShooterTest.const_get(drive_symbol).new)
		end

		def rotate_drive(diff)
			@drive_index += diff
			correct_drive_index
		end

		def select_drive(index)
			@drive_index = index
			correct_drive_index
		end

		def correct_drive_index
			@drive_index = @drives.size - 1 if @drive_index >= @drives.size
			@drive_index = 0 if @drive_index < 0
		end

		def rotate(angle_difference)
			@angle += angle_difference
			@sprites[0].rotation += angle_difference
		end

		def boost
			unless selected_drive.overheated then
				accelerate(direction * selected_drive.boost)
				selected_drive.run

				unless has_max_speed then
					selected_drive.generate_particles(self)
				end
			end
		end

		def brake
			accelerate(velocity * (-selected_drive.brake))
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
			if speed > selected_drive.max_speed then
				#@velocity *= (1.0 - selected_drive.friction)
			end

			@velocity *= (1.0 - selected_drive.friction)
			
			@drives.each do |drive|
				drive.update
			end
		end

		def has_max_speed
			return @velocity.squared_norm >= selected_drive.max_speed
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