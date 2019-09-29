module Data

	@entities = []
	@tiles = []

	def self.add_entity(entity, index: nil)
		index = @entities.size if !index
		@entities[index] = entity
		return index
	end

	def self.entities
		return @entities
	end

	def self.add_tile(tile, index: nil)
		index = @tiles.size if !index
		@tiles[index] = entity
		return index
	end

	def self.tiles
		return @tiles
	end

end