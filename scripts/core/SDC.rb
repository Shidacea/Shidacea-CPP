module SDC

	@window = nil
	@scene = nil
	@next_scene = nil
	@game = nil
	@resource_manager = nil

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

	def self.resource_manager
		return @resource_manager
	end
	
	def self.resource_manager=(value)
		@resource_manager = value
	end

end