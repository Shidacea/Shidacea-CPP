# TODO: Use this

module SDC
	module Launshi

		class SceneLaunshi < SDC::Scene

			def at_init
				config = SDC::Launshi.load_config_file("demo_projects/Example_Test", "config.json")
				SDC::Launshi.load_thumbnail(config)
				SDC::Launshi.set_config(config)
			end
			
			def handle_event(event)
				if event.has_type?(:Closed) then
					SDC.next_scene = nil
				end
			end

			def update
				if SDC::key_pressed?(:Enter) then
					SDC.next_scene = nil
				end
			end

			def draw
				SDC.draw_texture(filename: "assets/graphics/FrameFilters.png", coordinates: SDC::Coordinates.new(0, 0))

				0.upto(3) do |i|
					SDC.draw_texture(filename: "assets/graphics/FrameGame.png", coordinates: SDC::Coordinates.new(400, i*180))
					SDC.draw_texture(index: "Texture000".to_sym, coordinates: SDC::Coordinates.new(426, i*180 + 26))
				end

				SDC.draw_texture(filename: "assets/graphics/FrameScroll.png", coordinates: SDC::Coordinates.new(1240, 0))
			end

		end

	end
end