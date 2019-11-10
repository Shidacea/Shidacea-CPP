module SDC
	module Data

		@entities = []
		@texts = []

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

	end
end