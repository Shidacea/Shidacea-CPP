class MapConfig

	attr_reader :map_name

	def initialize(map_name)
		@map_name = map_name
		@script = nil
	end

	# TODO: Could be extended for multiple pages

	def script(&block)
		@script = block
	end

	def run_script
		@script&.call
	end

end