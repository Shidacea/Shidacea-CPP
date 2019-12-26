config = MapConfig.new("Test Map 001")

config.define_script do
	SDC::AI::once do
	
		puts "Map Test"

	end 
end 

SDC::Data::add_map_config(config, index: "TestMap")