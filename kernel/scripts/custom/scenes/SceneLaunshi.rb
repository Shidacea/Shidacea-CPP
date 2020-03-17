# TODO: Use this

module SDC
	module Launshi

		class SceneLaunshi < SDC::Scene

			def at_init
				SDC::Launshi.reset_configs
				SDC::Launshi.load_configs("demo_projects")
				SDC::Launshi.load_configs("projects")

				@active_config_id = 0

				SDC::Data.load_font(:Standard, filename: "assets/fonts/arial.ttf")
				@title_size = 20
				@title_offset_x = 5
				@title_offset_y = 5
			end
			
			def scroll_down
				@active_config_id += 1
				@active_config_id = [@active_config_id, SDC::Launshi.get_configs.size - 1].min
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
					end
					if event.key_pressed?(:Up) then
						scroll_up
					end
				end
			end

			def update
				if SDC::key_pressed?(:Enter) then
					SDC::Launshi.set_final_config(@active_config_id)
					SDC.next_scene = nil
				end
			end

			def draw
				SDC.draw_texture(filename: "assets/graphics/FrameFilters.png", coordinates: SDC::Coordinates.new(0, 0))

				configs = SDC::Launshi.get_configs

				0.upto(3) do |i|
					config = configs[@active_config_id + i]
					next if !config

					SDC.draw_texture(filename: "assets/graphics/FrameGame.png", coordinates: SDC::Coordinates.new(400, i*180))
					SDC.draw_texture(index: config.path.to_sym, coordinates: SDC::Coordinates.new(426, i*180 + 26))
					
					# Information block

					# TODO: More sophisticated length checks

					genre_list = "Genres: " + config.json["genres"][0..4].join(", ") + (config.json["genres"].size > 5 ? ", ..." : "")
					dev_list = "Developers: " + config.json["developers"][0..4].join(", ") + (config.json["developers"].size > 5 ? ", ..." : "") + " (" + config.json["year"].to_s + ")"

					offset = Coordinates.new(580 + @title_offset_x, i*180 + @title_offset_y)
					SDC.draw_text(font_index: :Standard, text: config.json["title"], size: @title_size, coordinates: offset)

					offset.y += @title_size + @title_offset_y
					SDC.draw_text(font_index: :Standard, text: config.json["subtitle"], size: @title_size, coordinates: offset)

					offset.y += @title_size + @title_offset_y
					SDC.draw_text(font_index: :Standard, text: "Project version: " + config.json["project_version"], size: @title_size, coordinates: offset)

					offset.y += @title_size + @title_offset_y
					SDC.draw_text(font_index: :Standard, text: genre_list, size: @title_size, coordinates: offset)

					offset.y += @title_size + @title_offset_y
					SDC.draw_text(font_index: :Standard, text: dev_list, size: @title_size, coordinates: offset)

					SDC.draw_texture(filename: "assets/graphics/Button.png", coordinates: SDC::Coordinates.new(585, i*180 + 140))
					SDC.draw_text(font_index: :Standard, text: "START", size: @title_size, coordinates: SDC::Coordinates.new(585 + 8, i*180 + 140 + 2))

					SDC.draw_texture(filename: "assets/graphics/Button.png", coordinates: SDC::Coordinates.new(585 + 100, i*180 + 140))
					SDC.draw_text(font_index: :Standard, text: "INFO", size: @title_size, coordinates: SDC::Coordinates.new(585 + 100 + 15, i*180 + 140 + 2))
				end

				SDC.draw_texture(filename: "assets/graphics/FrameScroll.png", coordinates: SDC::Coordinates.new(1240, 0))
			end

		end

	end
end