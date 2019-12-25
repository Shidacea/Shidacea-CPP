class MapConfig

	attr_reader :map_name
	attr_accessor :script

	def initialize(map_name)
		@map_name = map_name
		@script = nil
	end

	def run_script
		@script.tick if @script&.running?
	end

end