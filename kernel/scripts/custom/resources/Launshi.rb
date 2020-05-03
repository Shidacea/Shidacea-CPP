# Launshi module with helper functions and singleton instance variables

module SDC
	module Launshi

		PROJECT_FILE_NAME = "project.json"

		class Config

			attr_reader :path, :json
			
			def initialize(path, config_json)
				@path = path
				@json = config_json
			end

		end

		def self.reset_configs
			@configs = []
			@final_config = nil
		end

		def self.load_configs(path, create_if_missing: false)
			if !Dir.exists?(path) then
				Dir.mkdir(path)
			end
			Dir.foreach(path) do |entry|
				if !entry.start_with?(".") && File.directory?(path + "/" + entry) then
					config_file_name = path + "/" + entry + "/" + PROJECT_FILE_NAME

					if File.exist?(config_file_name) then
						new_config = self.load_config_file(path + "/" + entry, PROJECT_FILE_NAME)

						@configs.push(new_config)

						self.load_thumbnail(new_config)
					end
				end
			end
		end

		def self.set_final_config(index)
			@final_config = @configs[index]
		end

		def self.get_final_config
			return @final_config
		end

		def self.get_configs
			return @configs
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
			SDC::Data.preload_texture(config.path.to_sym, config.json["thumbnail"]) if config.json["thumbnail"] && !config.json["thumbnail"].empty?
			SDC::Script.path = old_path
		end

		def self.check_version(config)
			project_version = config.json["shidacea_version"]&.split(".")
			return false if !project_version

			sdc_version = SDC::Script.version.split(".")

			return false if project_version[0] != sdc_version[0]
			return false if project_version[1].to_i > sdc_version[1].to_i
			return true
		end

	end
end