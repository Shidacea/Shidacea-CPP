# TODO: Use this

module SDC
	module Launshi

		class SceneLaunshi < SDC::Scene

			def at_init
				SDC::Data.preload_texture(:Background, "assets/graphics/Background.png")
				SDC::Data.preload_texture(:Frame, "assets/graphics/Frame.png")
				
				@background = SDC::Sprite.new
				@background.link_texture(SDC::Data.textures[:Background])

				@frame = SDC::Sprite.new
				@frame.link_texture(SDC::Data.textures[:Frame])
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
				SDC.window.draw(@background)

				0.upto(2) do |i|
					SDC.window.draw_translated(@frame, SDC::Coordinates.new(340*i + 150, 60))
				end
			end

		end

	end
end