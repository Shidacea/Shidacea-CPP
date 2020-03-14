module SDC

	# Basic attributes

	@window = nil
	@scene = nil
	@next_scene = nil
	@game = nil
	@limiter = nil

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

	# Script routines for easier readability, directly referencing other methods

	def self.key_pressed?(key)
		return @window.has_focus? && SDC::EventKey.const_defined?(key) && SDC::EventKey.is_pressed?(SDC::EventKey.const_get(key))
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

	def self.draw_texture(index: nil, filename: nil, coordinates: Coordinates.new)
		texture = nil
		if filename then
			if index then
				texture = SDC::Data.load_texture(index, filename: filename)
			else
				# TODO: Maybe transfer this ability into the Data class itself for the case of index = 0
				texture = SDC::Data.load_texture((SDC::Data::SYMBOL_PREFIX + filename).to_sym, filename: filename)
			end

		elsif index then
			texture = SDC::Data.textures[index]
			puts "Warning: Texture index #{index} not loaded." if !texture

		else
			raise("No arguments given for texture drawing")

		end

		sprite = Sprite.new
		sprite.link_texture(texture)
		SDC.window.draw_translated(sprite, coordinates)
	end
end