module SDC

	# Common control sequences

	C_NULL = "\0"
	C_BELL = "\a"
	C_BACKSPACE = "\b"
	C_TAB = "\t"
	C_NEWLINE = "\n"
	C_VERT_TAB = "\v"
	C_FORM_FEED = "\f"
	C_CAR_RET = "\r"
	C_CTRL_Z = "\z"
	C_ESCAPE = "\e"
	C_CTRL_BACK = "\x7F"

	# Basic attributes

	@window = nil
	@scene = nil
	@next_scene = nil
	@game = nil
	@limiter = nil
	@text_input = nil

	def self.xy(x = 0.0, y = 0.0)
		return Coordinates.new(x, y)
	end

	def self.window
		return @window
	end

	def self.window=(value)
		@window = value
	end

	def self.scene
		return @scene
	end

	def self.scene=(value)
		@scene = value
	end

	def self.next_scene
		return @next_scene
	end

	def self.next_scene=(value)
		@next_scene = value
	end

	def self.game
		return @game
	end

	def self.game=(value)
		@game = value
	end

	def self.limiter
		return @limiter
	end

	def self.limiter=(value)
		@limiter = value
	end

	def self.text_input
		return @text_input 
	end

	def self.text_input=(value)
		@text_input = value
	end

	# Script routines for easier readability, directly referencing other methods

	def self.key_pressed?(key, override_text_input: false)
		return @window.has_focus? && (override_text_input || !@text_input) && SDC::EventKey.const_defined?(key) && SDC::EventKey.is_pressed?(SDC::EventKey.const_get(key))
	end

	def self.key(key)
		return SDC::EventKey.const_get(key) if SDC::EventKey.const_defined?(key)
	end

	def self.mouse_button_pressed?(button)
		return @window.has_focus? && SDC::EventMouse.const_defined?(button) && SDC::EventMouse.is_button_pressed?(SDC::EventMouse.const_get(button))
	end

	def self.mouse_button(button)
		return SDC::EventMouse.const_get(button) if SDC::EventMouse.const_defined?(button)
	end

	# Returns an integer array with two elements of the pixel coordinates.
	# Therefore, window scaling WILL change the dimensions of the area the mouse can operate in.
	def self.get_mouse_pos
		return SDC::EventMouse.get_position(SDC.window)
	end

	# Returns the mouse coordinate for the current view.
	# If you want to check for another view, you need to activate it first or execute any mouse check methods in a view block.
	def self.get_mouse_coords
		return SDC::EventMouse.get_coordinates(SDC.window)
	end

	def self.get_mouse_point
		return SDC::ShapePoint.new(self.get_mouse_coords)
	end

	def self.right_klick?
		return self.mouse_button_pressed?(:Right)
	end

	def self.left_klick?
		return self.mouse_button_pressed?(:Left)
	end

	def self.get_variable(index, default: nil)
		return @game.get_variable(index, default: default)
	end

	def self.set_variable(index, value)
		@game.set_variable(index, value)
	end

	def self.get_switch(index)
		return @game.get_switch(index)
	end

	def self.set_switch(index, value: true)
		@game.set_switch(index, value: value)
	end

	def self.reset_switch(index, value: false)
		@game.set_switch(index, value: value)
	end

	def self.toggle_switch(index)
		@game.toggle_switch(index)
	end

	def self.increase_variable(index, value = 1, default: 0)
		@game.increase_variable(index, value, default: default)
	end

	def self.decrease_variable(index, value = 1, default: 0)
		@game.decrease_variable(index, value, default: default)
	end

	def self.multiply_variable(index, value, default: 0)
		@game.multiply_variable(index, value, default: default)
	end

	# Other utility methods for rapid development

	def self.draw_texture(index: nil, file_index: nil, filename: nil, z: 0, draw_window: SDC.window, coordinates: SDC::Coordinates.new)
		texture = SDC::Data.load_texture(index, file_index: file_index, filename: filename)
		puts "Warning: Texture index #{index} not loaded." if !texture

		sprite = SDC::Sprite.new
		sprite.link_texture(texture)
		draw_window.draw_translated(sprite, z, coordinates)
	end

	def self.draw_text(index: nil, font_index: nil, font: nil, text: "", size: 10, z: 0, draw_window: SDC.window, coordinates: SDC::Coordinates.new, color: nil)
		text_obj = SDC::Data.load_text(index = index, content: text, size: size, font_index: font_index, font: font)
		puts "Warning: Text index #{index} not loaded." if !text_obj

		text_obj.color = color if color
		draw_window.draw_translated(text_obj, z, coordinates)
	end

	def self.play_sound(index: nil, file_index: nil, filename: nil, volume: 100.0, pitch: 1.0)
		sound_buffer = SDC::Data.load_sound_buffer(index, file_index: file_index, filename: filename)

		sound = SDC::Sound.new
		sound.link_sound_buffer(sound_buffer)
		sound.volume = volume
		sound.pitch = pitch
		sound.play
	end

	def self.play_music(index: nil, file_index: nil, filename: nil, volume: 100.0, pitch: 1.0)
		music = SDC::Data.load_music_track(index, file_index: file_index, filename: filename)

		music.volume = volume
		music.pitch = pitch
		music.play
	end

	def self.stop_music(index, file_index: nil, filename: nil)
		music = SDC::Data.load_music_track(index, file_index: file_index, filename: filename)
		
		music.stop
	end

	def self.handle_backspace_input(text_buffer)
		text_buffer.chop!
	end

	def self.handle_ctrl_backspace_input(text_buffer)
		# Remove the last word and every whitespace after it
		text_buffer.rstrip!
		last_space = text_buffer.rindex(" ")
		if last_space then
			text_buffer[last_space+1..-1] = ""
		else
			text_buffer.clear
		end
	end

	def self.is_ctrl_char(char)
		return (char.ord < 32 || char == C_CTRL_BACK)
	end

	# TODO: Allow specific input class

	def self.process_text_input(event: nil, text_buffer: nil, override: false)
		if event.has_type?(:TextEntered) then
			char = event.text_char

			# Want to filter certain chars? Use the filter method!
			if block_given? then
				filter_result = yield(char, text_buffer)
				char = filter_result if filter_result
				return if override
			end

			if char == C_BACKSPACE then
				self.handle_backspace_input(text_buffer)
			elsif char == C_CTRL_BACK then
				self.handle_ctrl_backspace_input(text_buffer)
			elsif self.is_ctrl_char(char) then

			else
				text_buffer.concat(char)
			end
		end
	end

end