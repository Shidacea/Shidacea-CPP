module SDC
	module Data

		extend SDCMeta::DataStorage

		self.define_new_data_type(:entity, plural: :entities)
		self.define_new_data_type(:text)
		self.define_new_data_type(:tileset)
		self.define_new_data_type(:texture)
		self.define_new_data_type(:sound_buffer)
		self.define_new_data_type(:map_config, as_hash: true)

	end
end