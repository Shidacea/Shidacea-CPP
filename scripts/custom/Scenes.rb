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
			@test_entity.position += Coordinates.new((rand*10 - 5).to_i, (rand*10 - 5).to_i)
		elsif EventKey::is_pressed?(EventKey::D) then
			@inspected_entity = $scene
		end
	end

	def at_init
		@test_entity = TestEntity.new(@sprites)
		@test_entity.position = Coordinates.new(400, 400)
		@test_toggle = false
		@inspected_entity = nil
	end

	def draw
		@test_entity.draw($window)
	end

	def draw_imgui
		ImGui.begin "Glorious Test Dialog Number 1" do
			if ImGui.button "Glorious Test Button Number 1" then
				@test_toggle = !@test_toggle
			end
			if @test_toggle then
				ImGui.begin_child "Some child" do
					ImGui.text "Oh yes, that button was pushed!"
				end
				ImGui.text "This text signifies that."
			end
		end
		if @inspected_entity then
			ImGui.begin "Entity inspector" do
				ImGui.text "Value: #{@inspected_entity}"
				ImGui.text "Instance variables:"
				@inspected_entity.instance_variables.each do |iv|
					@inspected_entity.instance_variable_set(iv, nil) if ImGui.button "X###{iv}"
					ImGui.same_line
					ImGui.text "Name: #{iv}, Value: #{@inspected_entity.instance_variable_get(iv)}"
				end
			end
		end
	end

end