# TODO: Use this

module SDC
	module Launshi

		class SceneLaunshi < SDC::Scene

			def at_init

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
				SDC.draw_texture(filename: "assets/graphics/Background.png")

				0.upto(2) do |i|
					SDC.draw_texture(filename: "assets/graphics/Frame.png", coordinates: SDC::Coordinates.new(340*i + 150, 60))
				end
			end

		end

	end
end