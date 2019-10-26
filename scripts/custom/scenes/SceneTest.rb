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

		@entities.each do |entity|
			@entities.each do |other_entity|
				next if !entity.test_box_collision_with(other_entity)
				entity.each_colliding_action_shape(other_entity) do |hurtshape, hitshape|
					entity.collision_with_entity(other_entity, hurtshape, hitshape)
				end
			end
		end

		@entities.each {|entity| entity.update}

	end

	def at_init
		@last_key_code = nil

		@music = Music.new
		@music.open_from_file("assets/music/Example.wav")
		@music.looping = true

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
		@test_value = 4
		@test_array = [1, 2, 3]
		@test_string = "Hello"
		@test_string2 = "Derp"
	end

	def draw
		view_player = View.new(FloatRect.new(@entities[0].position.x - 1280 * 0.5, @entities[0].position.y - 720 * 0.5, 1280, 720))
		$window.set_view(view_player)
		@test_map.reload(@entities[0].position)
		@test_map.draw($window, Coordinates.new(0, 0))
		@entities.each {|entity| entity.draw($window)}
		
		view_minimap = View.new(FloatRect.new(@entities[0].position.x - 1280 * 0.5, @entities[0].position.y - 720 * 0.5, 1280, 720))
		view_minimap.set_viewport(FloatRect.new(0.8, 0.0, 0.2, 0.2))
		$window.use_view(view_minimap) do
			@test_map.draw($window, Coordinates.new(0, 0))
		end

	end

	def draw_imgui
		ImGui.begin "Glorious Test Dialog Number 1" do

			shape_collision_no = 0
			box_collision_no = 0

			@entities.each do |entity|
				@entities.each do |other_entity|

					shape_collision_no += 1 if entity.test_shape_collision_with(other_entity)
					box_collision_no += 1 if entity.test_box_collision_with(other_entity)

				end
			end

			# Filter double collisions
			ImGui.button "Play music" {@music.play}
			ImGui.button "Pause music" {@music.pause}
			ImGui.text "Shape Collision: #{shape_collision_no.div(2)}"
			ImGui.text "Box Collision:   #{box_collision_no.div(2)}"
			ImGui.text "HP of entity 0: #{@entities[0].hp}"
			ImGui.text "Last key code: #{@last_key_code}"
			ImGui.button "Reset mouse" {EventMouse::set_position([300, 200], $window)}
			ImGui.button "Get mouse pos" {puts EventMouse::get_position($window)}
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

			ImGui.button "Test socket" do
				puts "Socket"
				@socket = Socket.new
				puts @socket.connect("127.0.0.1", 293)
				puts @socket.remote_address
				puts @socket.remote_port
				puts @socket.local_port
				puts @socket.send_message("TestBla")
			end

			ImGui.button "Test listener" do
				puts "Listener"
				@listener = Listener.new
				@socket = Socket.new
				puts @listener.listen(293)
				puts @listener.accept(@socket)
				puts @socket.remote_address
				puts @socket.remote_port
				puts @socket.local_port
				puts @socket.receive(100)
				puts @socket.last_message
			end

			ImGui.button "Toggle show sprite 0" do
				@entities[0].active_sprites[0] = !@entities[0].active_sprites[0]
			end

		end
	end
end