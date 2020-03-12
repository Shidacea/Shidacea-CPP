# Launshi module with helper functions

module SDC
	module Launshi

		def self.load_config_file(filename)
			full_name = SDC::Script.path + "/" + filename
		
			content = ""
			file = File.open(full_name, "r")
			while !file.eof?
				content += file.readline
			end

			file.close

			return JSON.parse(content)
		end

		def self.load_scripts(config)
			config["scripts"]&.each do |script|
				if script.end_with?("/") then
					SDC::Script.load_recursively(script.chop)
				elsif script.end_with?(".rb") then
					SDC::Script.load(script)
				else
					raise("Invalid file to load: #{script}")
				end
			end
		end

	end
end