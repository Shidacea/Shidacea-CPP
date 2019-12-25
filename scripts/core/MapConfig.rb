class MapConfig

	attr_reader :map_name

	def initialize(map_name)
		@map_name = map_name
		@script = nil
	end

	def script=(script)
		@script = script
	end

	def run_script
		@script.tick if @script&.running?
	end

end