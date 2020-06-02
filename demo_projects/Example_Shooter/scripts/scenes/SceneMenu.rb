module ShooterTest
	class SceneMenu < SDC::Scene

		def handle_event(event)
			if event.has_type?(:Closed) then
				SDC.next_scene = nil
			elsif event.has_type?(:KeyReleased) then
				if event.key_pressed?(:Q) then
					@player_ship.rotate_drive(-1)
				end

				if event.key_pressed?(:E) then
					@player_ship.rotate_drive(1)
				end
			end
		end

		def at_init
			@player_ship = PlayerShip.new
			@player_ship.position = SDC.xy(300, 200)
			@particles = []

			@player_ship.add_drive(:ImpulseDrive)
			@player_ship.add_drive(:HyperDrive)
			@player_ship.add_drive(:DarkMatterDrive)
			@player_ship.add_drive(:QuantumDrive)
		end

		def draw
			@player_ship.draw SDC.window
			@particles.each {|particle| particle.draw(SDC.window)}
		end

		def add_particle(particle)
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
				@player_ship.boost
			end

			if SDC.key_pressed?(:S) then
				@player_ship.brake
			end

			@player_ship.update
			@particles.reject! do |particle|
				particle.update
				particle.gone
			end
		end

	end
end