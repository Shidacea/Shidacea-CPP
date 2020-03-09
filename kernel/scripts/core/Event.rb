# Extension for events, for better readability

module SDC

	class Event

		def has_type?(event_type)
			return self.type == SDC::EventType.const_get(event_type)
		end

		def key_pressed?(key)
			return self.key_code == SDC.key(key)
		end

		def mouse_button_pressed?(button)
			return self.mouse_button_code == SDC.button(button)
		end

		def mouse_coordinates
			return SDC::Coordinates.new(self.mouse_button_x.to_f, self.mouse_button_y.to_f)
		end

		def new_mouse_coordinates
			return SDC::Coordinates.new(self.mouse_move_x.to_f, self.mouse_move_y.to_f)
		end

	end

end