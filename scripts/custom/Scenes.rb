# This is where you want to do the most work
# Each relevant scene can be defined here

class SceneTest < Scene 

	def handle_event(event)
		if event.type == EventType::KeyPressed then
			puts "Key Code = " + event.key_code.to_s
		elsif event.type == EventType::Closed
			$next_scene = nil
		end
	end

	def update
		if EventKey::is_pressed?(EventKey::A) then
			EventMouse::set_position([300, 200], $window)
		elsif EventKey::is_pressed?(EventKey::B) then
			puts EventMouse::get_position($window)
		elsif EventKey::is_pressed?(EventKey::C) then
			@entities[0].move_sprite(0, Coordinates.new(-5, -2))
		elsif EventKey::is_pressed?(EventKey::D) then
			@inspected_entity = $scene
		elsif EventKey::is_pressed?(EventKey::E) then
			$window.set_imgui_scale(2.0)
		end
	end

	def at_init
		@entities = []
		@entities.push(create(TestEntity))
		@entities.push(create(TestEntity))

		@entities[0].move_sprite_to(0, Coordinates.new(400, 400))

		@entities[1].move_sprite_to(0, Coordinates.new(200, 300))

		@test_toggle = false
		@inspected_entity = nil
		@test_value = 4
		@test_array = [1, 2, 3]
		@test_string = "Hello"
		@test_string2 = "Derp"

		@test_box = ShapeCircle.new(25)
	end

	def draw
		@entities.each {|entity| entity.draw($window)}
	end

	def draw_imgui
		ImGui.begin "Glorious Test Dialog Number 1" do
			ImGui.text "Collision: #{Collider.test(@test_box, @entities[0].sprite_position(0), @test_box, @entities[1].sprite_position(0))}"
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
				ImGui.text "Value: #{@inspected_entity}"
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
							
							# Avoid any complications resulting from an invalidated iterator
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