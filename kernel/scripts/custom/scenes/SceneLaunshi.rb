module SDC
	class Launshi

		COLOR_TEXT_REGULAR = SDC::Color.new(255, 255, 255, 255)
		COLOR_TEXT_DISABLED = SDC::Color.new(127, 0, 0, 255)
		COLOR_TEXT_INPUT = SDC::Color.new(0, 0, 0, 255)

		class SceneLaunshi < SDC::Scene

			def at_init
				@launshi = SDC::Launshi.new
				@launshi.load_configs("demo_projects")
				@launshi.load_configs("projects", create_if_missing: true)

				SDC::Data.load_font(:Standard, filename: "assets/fonts/arial.ttf")
				@title_size = 20
				@wrong_version_size = 15
				@title_offset_x = 5
				@title_offset_y = 5

				@launshi.apply_filters

				@active_config_id = 0

				@start_buttons = []
				@info_buttons = []
				@genre_buttons = []

				@text_title_filter = SDC::Text.new("Title filter", SDC::Data.fonts[:Standard], @title_size)
				@text_desc_filter = SDC::Text.new("Description filter", SDC::Data.fonts[:Standard], @title_size)
				@text_genre_filter = SDC::Text.new("Genre filter", SDC::Data.fonts[:Standard], @title_size)

				@text_title_filter_content = SDC::Text.new("", SDC::Data.fonts[:Standard], @title_size)
				@text_title_filter_content.color = COLOR_TEXT_INPUT
				@text_desc_filter_content = SDC::Text.new("", SDC::Data.fonts[:Standard], @title_size)
				@text_desc_filter_content.color = COLOR_TEXT_INPUT

				@text_genre = SDC::Text.new("", SDC::Data.fonts[:Standard], @title_size)

				@text_title = SDC::Text.new("", SDC::Data.fonts[:Standard], @title_size)
				@text_subtitle = SDC::Text.new("", SDC::Data.fonts[:Standard], @title_size)
				@text_version = SDC::Text.new("", SDC::Data.fonts[:Standard], @title_size)
				@text_genres = SDC::Text.new("", SDC::Data.fonts[:Standard], @title_size)
				@text_devs = SDC::Text.new("", SDC::Data.fonts[:Standard], @title_size)

				@text_start = SDC::Text.new("START", SDC::Data.fonts[:Standard], @title_size)
				@text_info = SDC::Text.new("INFO", SDC::Data.fonts[:Standard], @title_size)

				@text_error_top = SDC::Text.new("", SDC::Data.fonts[:Standard], @wrong_version_size)
				@text_error_bottom = SDC::Text.new("", SDC::Data.fonts[:Standard], @wrong_version_size)

				0.upto(3) do |i|
					button_start_shape = SDC::ShapeBox.new(SDC::Coordinates.new(585 + 40, i*180 + 140 + 15), SDC::Coordinates.new(40, 15))
					button_start = SDC::Button.new(shape: button_start_shape)
					@start_buttons[i] = button_start

					button_info_shape = SDC::ShapeBox.new(SDC::Coordinates.new(585 + 100 + 40, i*180 + 140 + 15), SDC::Coordinates.new(40, 15))
					button_info = SDC::Button.new(shape: button_info_shape)
					@info_buttons[i] = button_info
				end

				offset_y = 10 + 5*(@title_offset_y + @title_size) + 5
				gx = 0
				gy = 0
				SDC::Launshi::AVAILABLE_GENRES.each do |genre|
					button_genre_shape = SDC::ShapeBox.new(SDC::Coordinates.new(10 + 180*gx + 15, offset_y + (30 + 10)*gy + 15), SDC::Coordinates.new(15, 15))
					button_genre = SDC::Button.new(shape: button_genre_shape)
					@genre_buttons.push(button_genre)

					gx += 1
					if gx == 2 then
						gx = 0
						gy += 1
					end
				end
			end
			
			def scroll_down
				@active_config_id += 1
				@active_config_id = [@active_config_id, [0, @launshi.get_configs.size - 4 - 1].max].min
			end

			def scroll_up
				@active_config_id -= 1
				@active_config_id = [@active_config_id, 0].max
			end

			def handle_event(event)
				if event.has_type?(:Closed) then
					SDC.next_scene = nil

				elsif event.has_type?(:KeyPressed) then
					if event.key_pressed?(:Down) then
						scroll_down
					elsif event.key_pressed?(:Up) then
						scroll_up
					end

				elsif event.has_type?(:MouseWheelScrolled) then
					if event.mouse_scrolled_up? then
						scroll_up
					elsif event.mouse_scrolled_down? then
						scroll_down
					end

				elsif event.has_type?(:MouseButtonReleased) then
					if event.mouse_left_click? then
						project_start_id = nil
						project_info_id = nil

						0.upto(3) do |i|

							configs = @launshi.get_filtered_configs
							config = configs[@active_config_id + i]

							if config && @launshi.check_version(config) then
								@start_buttons[i].on_mouse_touch do
									project_start_id = @active_config_id + i
								end
							end

							@info_buttons[i].on_mouse_touch do
								project_info_id = @active_config_id + i
							end
						end

						if project_start_id && project_start_id < @launshi.get_filtered_configs.size then
							SDC::Launshi.set_final_config(project_start_id, @launshi)
							SDC.next_scene = nil

						elsif project_info_id && project_info_id < @launshi.get_filtered_configs.size then
							# TODO: Info window
						end

						0.upto(SDC::Launshi::AVAILABLE_GENRES.size - 1) do |i|
							@genre_buttons[i].on_mouse_touch do	
								@launshi.genre_filters[i] = !@launshi.genre_filters[i]
								@launshi.apply_filters
							end
						end

					end
				end
			end

			def update
				
			end

			def draw
				# TODO: Optimize the routines, especially in the SDC module

				SDC.draw_texture(filename: "assets/graphics/FrameFilters.png", coordinates: SDC::Coordinates.new(0, 0))

				SDC.window.draw_translated(@text_title_filter, SDC::Coordinates.new(10, 10))

				@text_title_filter_content.string = @launshi.name_filter
				SDC.window.draw_translated(@text_title_filter_content, SDC::Coordinates.new(10, 10 + 1*(@title_offset_y + @title_size)))
				
				SDC.window.draw_translated(@text_desc_filter, SDC::Coordinates.new(10, 10 + 2*(@title_offset_y + @title_size)))

				@text_title_filter_content.string = @launshi.description_filter
				SDC.window.draw_translated(@text_desc_filter_content, SDC::Coordinates.new(10, 10 + 3*(@title_offset_y + @title_size)))

				SDC.window.draw_translated(@text_genre_filter, SDC::Coordinates.new(10, 10 + 4*(@title_offset_y + @title_size)))
				
				offset_y = 10 + 5*(@title_offset_y + @title_size) + 5
				gx = 0
				gy = 0
				0.upto(SDC::Launshi::AVAILABLE_GENRES.size - 1) do |i|
					genre = SDC::Launshi::AVAILABLE_GENRES[i]
					if @launshi.genre_filters[i] then
						SDC.draw_texture(filename: "assets/graphics/Checkbox_ticked.png", coordinates: SDC::Coordinates.new(10 + 180*gx, offset_y + (30 + 10)*gy))
					else
						SDC.draw_texture(filename: "assets/graphics/Checkbox.png", coordinates: SDC::Coordinates.new(10 + 180*gx, offset_y + (30 + 10)*gy))
					end

					@text_genre.string = genre
					SDC.window.draw_translated(@text_genre, SDC::Coordinates.new(10 + 30 + 10 + 180*gx, offset_y + 2 + (30 + 10)*gy))

					@genre_buttons[gy*2 + gx].draw
					
					gx += 1
					if gx == 2 then
						gx = 0
						gy += 1
					end
				end

				configs = @launshi.get_filtered_configs
				0.upto(3) do |i|
					config = configs[@active_config_id + i]
					next if !config

					SDC.draw_texture(filename: "assets/graphics/FrameGame.png", coordinates: SDC::Coordinates.new(400, i*180))
					SDC.draw_texture(index: config.path.to_sym, coordinates: SDC::Coordinates.new(426, i*180 + 26)) if config.json["thumbnail"] && !config.json["thumbnail"].empty?
					
					# Information block

					# TODO: More sophisticated length checks

					genre_list = "Genres: " + config.json["genres"][0..4].join(", ") + (config.json["genres"].size > 5 ? ", ..." : "")
					dev_list = "Developers: " + config.json["developers"][0..4].join(", ") + (config.json["developers"].size > 5 ? ", ..." : "") + " (" + config.json["year"].to_s + ")"

					offset = Coordinates.new(580 + @title_offset_x, i*180 + @title_offset_y)

					@text_title.string = config.json["title"]
					SDC.window.draw_translated(@text_title, offset)

					offset.y += @title_size + @title_offset_y
					@text_subtitle.string = config.json["subtitle"]
					SDC.window.draw_translated(@text_subtitle, offset)

					offset.y += @title_size + @title_offset_y
					@text_version.string = "Project version: " + config.json["project_version"]
					SDC.window.draw_translated(@text_version, offset)

					offset.y += @title_size + @title_offset_y
					@text_genres.string = genre_list
					SDC.window.draw_translated(@text_genres, offset)

					offset.y += @title_size + @title_offset_y
					@text_devs.string = dev_list
					SDC.window.draw_translated(@text_devs, offset)

					version = config.json["shidacea_version"]

					correct_version = @launshi.check_version(config)
					text_color = (correct_version ? COLOR_TEXT_REGULAR : COLOR_TEXT_DISABLED)

					# TODO: Use buttons to simplify this

					@start_buttons[i].draw
					@info_buttons[i].draw

					SDC.draw_texture(filename: "assets/graphics/Button.png", coordinates: SDC::Coordinates.new(585, i*180 + 140))

					@text_start.color = text_color
					SDC.window.draw_translated(@text_start, SDC::Coordinates.new(585 + 8, i*180 + 140 + 2))

					SDC.draw_texture(filename: "assets/graphics/Button.png", coordinates: SDC::Coordinates.new(585 + 100, i*180 + 140))

					SDC.window.draw_translated(@text_info, SDC::Coordinates.new(585 + 100 + 15, i*180 + 140 + 2))

					if !correct_version then
						@text_error_top.color = COLOR_TEXT_DISABLED
						@text_error_top.string = "Project does not run on Shidacea version #{SDC::Script.version}"
						@text_error_bottom.color = COLOR_TEXT_DISABLED
						@text_error_top.string = "Required Shidacea version is at least #{config.json['shidacea_version'].split('.')[0..1].join('.')}"

						SDC.window.draw_translated(@text_error_top, SDC::Coordinates.new(585 + 200 - 10, i*180 + 140 - 3))
						SDC.window.draw_translated(@text_error_bottom, SDC::Coordinates.new(585 + 200 - 10, i*180 + 140 - 3 + @wrong_version_size))
					end
				end

				SDC.draw_texture(filename: "assets/graphics/FrameScroll.png", coordinates: SDC::Coordinates.new(1240, 0))
			end

		end

	end
end