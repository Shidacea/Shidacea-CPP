class MapConfig

	attr_reader :map_name

	def initialize(map_name)
		@map_name = map_name
		@script = nil
	end

	def script(&block)
		@script = block
	end

	def run_script
		@script&.call
	end

end