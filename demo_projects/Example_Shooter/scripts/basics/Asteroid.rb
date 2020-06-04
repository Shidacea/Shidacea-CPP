module ShooterTest
	class Asteroid < SDC::Entity
		register_id :Asteroid

		self.define_class_property :z, default: Z_ASTEROID
		self.define_class_property :mass, default: 1000.0

		SDC::Data.load_texture(:Asteroid, filename: "assets/graphics/Asteroid.png")
		add_sprite(index: 0, texture_index: :Asteroid, rect: SDC::IntRect.new(0, 0, 400, 400), origin: SDC.xy(200, 200))

		add_shape(index: 0, type: SDC::CollisionShapeCircle, radius: 200.0)
		add_box(index: 0, size: SDC.xy(400.0, 400.0), offset: SDC.xy(0.0, 0.0), origin: SDC.xy(200, 200))

		set_hitshape(index: 0, shape_index: 0, damage: 3)
		set_hurtshape(index: 0, shape_index: 0)

		def custom_physics
			# TODO: Put in SceneMenu
			SDC.scene.check_collisions(self)
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