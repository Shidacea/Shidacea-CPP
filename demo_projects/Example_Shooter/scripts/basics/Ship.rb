module ShooterTest
	class Ship < SDC::Entity
	
		# Define new properties
		self.define_class_property :health, default: 0
		self.define_class_property :shield, default: 0
		self.define_class_property :weapon, default: nil
		self.define_class_property :drive, default: :CombustionDrive
		self.define_class_property :z, default: Z_SHIP
		self.define_class_property :mass, default: 1.0

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

		def correct_shapes

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
			@angle += angle_difference * SDC.game.dt
			@sprites[0].rotation += angle_difference * SDC.game.dt
			correct_shapes
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
			@velocity *= (1.0 - selected_drive.friction)
			
			@drives.each do |drive|
				drive.update
			end
		end

		def custom_physics
			SDC.scene.check_collisions(self)
		end

		def has_max_speed
			return @velocity.squared_norm >= selected_drive.max_speed
		end

		def update_shapes
			
		end

		def at_entity_collision(other_entity, hurtshape, hitshape)
			dv = @velocity - other_entity.velocity
			dx = @position - other_entity.position
			
			reduced_mass = 2.0 * other_entity.mass / (other_entity.mass + self.mass)
			@velocity = @velocity - dx * reduced_mass * (dv.dot(dx) / dx.squared_norm)

			reduced_mass = 2.0 * self.mass / (other_entity.mass + self.mass)
			other_entity.velocity = other_entity.velocity + dx * reduced_mass * (dv.dot(dx) / dx.squared_norm)
		end

	end
end