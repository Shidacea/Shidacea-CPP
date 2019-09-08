class SceneTest < Scene 

	def handle_event(event)
		if event.type == EventType::KeyPressed then
			if event.key_code == EventKey::W then
				@entities[0].accelerate(Coordinates.new(0.0, -1000.0 * $game.meter))
			end
			@last_key_code = event.key_code.to_s
		elsif event.type == EventType::Closed
			$next_scene = nil
		end
	end

	def update
		if EventKey::is_pressed?(EventKey::F10) then
			$window.set_imgui_scale(2.0)
		
		elsif EventKey::is_pressed?(EventKey::F1) then
			# Should trigger an error with backtrace
			do_stuff_which_does_not_exist

		end

		v = 5.0 * $game.meter
		dx = (EventKey::is_pressed?(EventKey::A) ? -v : 0.0) + (EventKey::is_pressed?(EventKey::D) ? v : 0.0)
		dy = (EventKey::is_pressed?(EventKey::S) ? v : 0.0)

		@entities[0].accelerate(Coordinates.new(dx, dy))

		@entities.each {|entity| entity.update}

	end

	def at_init
		@last_key_code = nil

		@test_map = Map.new(view_width: 30, view_height: 20)
		@test_map.load_from_file("dummy")

		@entities = []
		@entities.push(create(TestEntity))
		@entities.push(create(TestEntity))
		@entities.push(create(TestEntity))

		@entities[0].position = Coordinates.new(400, 400)

		@entities[1].position.x = 200
		@entities[1].position.y = 300

		@entities[0].set_child(@entities[2])
		@entities[2].position = Coordinates.new(50, 10)

		@test_toggle = false
		@inspected_entity = nil
		@test_value = 4
		@test_array = [1, 2, 3]
		@test_string = "Hello"
		@test_string2 = "Derp"
	end

	def draw
		@test_map.reload(@entities[0].position)
		@test_map.draw($window, @entities[0].position)
		@entities.each {|entity| entity.draw($window)}
	end

	def draw_imgui
		ImGui.begin "Glorious Test Dialog Number 1" do

			shape_collision_no = 0
			box_collision_no = 0

			@entities.each do |entity|
				@entities.each do |other_entity|

					# Avoid collisions between identical entities and its children
					next if entity.magic_number == other_entity.magic_number

					shape_collision_no += 1 if entity.test_shape_collision_with(other_entity)
					box_collision_no += 1 if entity.test_box_collision_with(other_entity)
				end
			end

			# Filter double collisions
			ImGui.text "Shape Collision: #{shape_collision_no.div(2)}"
			ImGui.text "Box Collision:   #{box_collision_no.div(2)}"
			ImGui.text "Last key code: #{@last_key_code}"
			ImGui.button "Reset mouse" {EventMouse::set_position([300, 200], $window)}
			ImGui.button "Get mouse pos" {puts EventMouse::get_position($window)}
			ImGui.button "Inspect $scene" {@inspected_entity = $scene}
			ImGui.button "Rescale entity" do
				@entities[0].shapes[0].scale *= 1.1
				@entities[0].boxes[0].scale *= 1.1
				@entities[0].sprites[0].scale *= 1.1
				@entities[0].sprites[0].position *= 1.1
			end
			ImGui.button "Reset entity" do
				@entities[0].shapes[0].scale = 1.0
				@entities[0].boxes[0].scale = Coordinates.new(1.0, 1.0)
				@entities[0].sprites[0].scale = Coordinates.new(1.0, 1.0)
				@entities[0].sprites[0].position = Coordinates.new(-25.0, -25.0)
			end

			if ImGui.button "Glorious Test Button Number 1" then
				@test_toggle = !@test_toggle
			end

			if @test_toggle then
				ImGui.begin_child "Some child" do
					ImGui.text "Oh yes, that button was pushed!"
				end
				ImGui.text "This text signifies that."
			end

			ImGui.input_int("Array", @test_array)
		end

		if @inspected_entity then
			ImGui.begin "Scene inspector###{self.object_id}" do
				@inspected_entity = self if ImGui.button "Back to self"

				# TODO: Add float support
				# TOOD: Add array support by treating arrays with separate inspections

				ImGui.new_line

				if @inspected_entity.is_a? Array then
					ImGui.text "Array elements:"

					0.upto(@inspected_entity.size - 1) do |i|
						value = @inspected_entity[i]

						if ImGui.button("Inspect index #{i}") then
							@inspected_entity = value
							
							# Avoid any complications resulting from an invalidated iterator
							break
						end

						ImGui.same_line
						ImGui.text(value.to_s)
					end
				else
					ImGui.text "Class: #{@inspected_entity.class}"
					ImGui.text "Instance variables:"

					@inspected_entity.instance_variables.each do |iv|
						value = @inspected_entity.instance_variable_get(iv)

						if value.is_a? String then
							ImGui.input_instance_variable_string(iv.to_s, @inspected_entity, iv)

						elsif value.is_a? Fixnum then
							ImGui.input_instance_variable_int(iv.to_s, @inspected_entity, iv)

						elsif [TrueClass, FalseClass].include? value.class then
							@inspected_entity.instance_variable_set(iv, !value) if ImGui.button("#{value}###{iv}")
						
							ImGui.same_line
							ImGui.text(iv.to_s)

						else
							if ImGui.button("Inspect###{iv}") then
								@inspected_entity = value

								break
							end

							ImGui.same_line
							ImGui.text(iv.to_s)
						end
					end
				end

				
			end
		end
	end

end