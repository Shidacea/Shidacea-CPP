module SDC
	module Data

		@entities = []
		@texts = []
		@tilesets = []
		@textures = []

		def self.add_entity(entity, index: nil)
			index = @entities.size if !index
			@entities[index] = entity
			return index
		end

		def self.entities
			return @entities
		end
	
		def self.add_text(text, index: nil)
			index = @texts.size if !index
			@texts[index] = text
			return index
		end

		def self.texts
			return @texts
		end

		def self.add_tileset(tileset, index: nil)
			index = @tilesets.size if !index
			@tilesets[index] = tileset
			return index
		end

		def self.tilesets
			return @tilesets
		end

		def self.add_texture(texture, index: nil)
			index = @textures.size if !index
			@textures[index] = texture
			return index
		end

		def self.textures
			return @textures
		end

	end
end