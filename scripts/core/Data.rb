module SDC
	module Data

		def self.define_new_data_type(name, plural: name.to_s + "s")
			instance_variable_set("@#{plural}", [])
			data = instance_variable_get("@#{plural}")

			define_singleton_method("add_#{name}") do |obj, index: nil|
				index = data.size if !index
				data[index] = obj
				return index
			end

			define_singleton_method(plural) do
				return data
			end
		end

		self.define_new_data_type(:entity, plural: :entities)
		self.define_new_data_type(:text)
		self.define_new_data_type(:tileset)
		self.define_new_data_type(:texture)
		self.define_new_data_type(:sound_buffer)

	end
end