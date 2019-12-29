module SDC
	module Data

		extend SDCMeta::DataStorage

		self.define_new_data_type(:entity, plural: :entities)
		self.define_new_data_type(:text)
		self.define_new_data_type(:tileset, as_hash: true)
		self.define_new_data_type(:texture, as_hash: true)
		self.define_new_data_type(:sound_buffer)
		self.define_new_data_type(:map_config, as_hash: true)
		self.define_new_data_type(:filename, as_hash: true)

		def self.load_texture(file_index)
			filename = self.filenames[file_index]

			if !self.textures[file_index] then
				texture = Texture.new
				texture.load_from_file(filename)
				self.add_texture(texture, index: file_index)
			end

			return self.textures[file_index]
		end

		def self.preload_texture(file_index, filename)
			self.add_filename(filename, index: file_index)
			self.load_texture(file_index)
		end

	end
end