module ShooterTest
	class SceneMenu < SDC::Scene

		Z_PARTICLE = 1

		def handle_event(event)
			if event.has_type?(:Closed) then
				SDC.next_scene = nil
			end
		end

		def at_init
			@player_ship = ShooterTest::PlayerShip.new
			@player_ship.position = SDC.xy(300, 200)
			@particles = []
		end

		def draw
			@player_ship.draw SDC.window
			@particles.each {|particle| particle.draw(SDC.window)}
		end

		def spawn_particle
			particle_shape = SDC::DrawShapeRectangle.new
			particle_shape.size = SDC.xy(6, 6)
			particle_shape.origin = SDC.xy(3, 3)

			new_position = @player_ship.position + @player_ship.direction * (-30.0) + @player_ship.direction_normal * ((rand(3) - 1) * 15.0)
			new_velocity = @player_ship.velocity + @player_ship.direction * (-2.0)

			particle = ShooterTest::Particle.new(shape: particle_shape, lifetime: rand(256), position: new_position, velocity: new_velocity, z: Z_PARTICLE) do
				particle.color = SDC::Color.new(255, particle.lifetime * 0.5, 0, particle.lifetime)
			end

			@particles.push(particle)
		end

		def update
			if SDC.key_pressed?(:A) then
				@player_ship.rotate(-5.0)
			end

			if SDC.key_pressed?(:D) then
				@player_ship.rotate(5.0)
			end

			if SDC.key_pressed?(:W) then
				@player_ship.accelerate(@player_ship.direction * 0.1)
				unless @player_ship.has_max_speed then
					rand(3).times do 
						spawn_particle
					end
				end
			end

			if SDC.key_pressed?(:S) then
				@player_ship.accelerate(@player_ship.direction * (-0.05))
			end

			@player_ship.update
			@particles.reject! do |particle|
				particle.update
				particle.gone
			end
		end

	end
end