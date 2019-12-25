config = MapConfig.new("Test Map 001")

config.script = SDC::AI::Script.new do
	SDC::AI::forever do
	
		puts "Map Test"

	end 
end 

SDC::Data::add_map_config(config, index: "TestMap")