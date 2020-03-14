# Launshi module with helper functions

module SDC
	module Launshi

		class Config

			attr_reader :path, :json
			
			def initialize(path, config_json)
				@path = path
				@json = config_json
			end

		end

		def self.set_config(config)
			@config = config
		end

		def self.get_config
			return @config
		end

		def self.load_config_file(path, filename)
			full_name = path + "/" + filename
		
			content = ""
			file = File.open(full_name, "r")
			while !file.eof?
				content += file.readline
			end

			file.close

			return Config.new(path, JSON.parse(content))
		end

		def self.load_scripts(config)
			config.json["scripts"]&.each do |script|
				if script.end_with?("/") then
					SDC::Script.load_recursively(script.chop)
				elsif script.end_with?(".rb") then
					SDC::Script.load(script)
				else
					raise("Invalid file to load: #{script}")
				end
			end
		end

		def self.load_thumbnail(config)
			old_path = SDC::Script.path
			SDC::Script.path = config.path
			SDC::Data.preload_texture("Texture000".to_sym, config.json["thumbnail"])
			SDC::Script.path = old_path
		end

	end
end