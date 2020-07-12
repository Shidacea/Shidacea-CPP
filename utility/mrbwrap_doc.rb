# TODO: Add C-style comments
# TODO: Add class methods
# TODO: Add module methods
# TODO: Add constants

class MrbWrapDoc

	START_SEQUENCE = "@@@"

	COMMAND_INSTANCE_METHOD = "MRBWRAPDOC_IM"
	COMMAND_ATTRIBUTE = "MRBWRAPDOC_ATTR"

	PARSE_MODE_NONE = 0
	PARSE_MODE_YARD = 1

	FILE_TEMPLATE = "automatic_doc_"
	FILE_ENDING = ".rb"

	TAG_METHOD = 0
	TAG_ATTRIBUTE = 1

	def initialize
		@classes = {}
		@modules = {}
	end

	def parse_file(filename)
		lines = nil
		File.open(filename) do |f|
			lines = f.readlines
		end

		parse_mode = PARSE_MODE_NONE
		current_command = nil
		comment_line_list = []

		lines.each do |line|
			stripped_line = line.strip

			if stripped_line.start_with?("//", "//!")

				if parse_mode == PARSE_MODE_NONE
					if start_sequence_index = stripped_line.index(START_SEQUENCE)
						command = stripped_line[start_sequence_index..-1].delete_prefix(START_SEQUENCE).strip.split
						if command[0] == COMMAND_INSTANCE_METHOD
							current_command = command
							parse_mode = PARSE_MODE_YARD
						elsif command[0] == COMMAND_ATTRIBUTE
							current_command = command
							parse_mode = PARSE_MODE_YARD
						else
							puts "Unknown MrbWrapDoc command #{command[0]} with args #{command[1..-1]}"
						end
					end

				elsif parse_mode == PARSE_MODE_YARD
					comment_line = nil
					if stripped_line.start_with?("//!")
						comment_line = stripped_line.delete_prefix("//!").strip
					elsif stripped_line.start_with?("//")
						comment_line = stripped_line.delete_prefix("//").strip
					end

					comment_line_list.push(comment_line)

				end

			elsif parse_mode == PARSE_MODE_YARD
				if current_command[0] == COMMAND_INSTANCE_METHOD
					class_name = current_command[1]
					method_name = current_command[2]
					args = current_command[3..-1]

					@classes[class_name] = {} unless @classes[class_name]
					@classes[class_name][method_name] = [TAG_METHOD, comment_line_list, args]

				elsif current_command[0] == COMMAND_ATTRIBUTE
					class_name = current_command[1]
					attribute_name = current_command[2]
					attribute_type = current_command[3]
					attribute_property = current_command[4]

					@classes[class_name] = {} unless @classes[class_name]
					@classes[class_name][attribute_name] = [TAG_ATTRIBUTE, comment_line_list, attribute_type, attribute_property ? "rw" : attribute_property]

				end

				parse_mode = PARSE_MODE_NONE
				current_command = nil
				comment_line_list = []
			end
		end
	end

	def generate_doc(destination)
		@classes.each_key do |class_name|
			filename = destination + FILE_TEMPLATE + class_name + FILE_ENDING
			File.open(filename, "w") do |f|
				f.puts "class #{class_name}"
				f.puts
				
				@classes[class_name].each_key do |method_name|
					method_args = @classes[class_name][method_name]

					method_tag = method_args[0]
					method_lines = method_args[1]

					if method_tag == TAG_METHOD
						args = method_args[2]

						if args
							f.puts "\t# @!method #{method_name}(#{args.join(", ")})"
						else
							f.puts "\t# @!method #{method_name}"
						end

						f.puts "\t# @!scope instance"

					elsif method_tag == TAG_ATTRIBUTE
						attribute_type = method_args[2]
						attribute_property = method_args[3]

						f.puts "\t# @!attribute [#{attribute_property}] #{method_name}"
						f.puts "\t# @return [#{attribute_type}]"

					end

					method_lines.each do |line|
						f.puts "\t# #{line}"
					end
					f.puts
				end

				f.puts "end"
			end
		end
	end

end

m = MrbWrapDoc.new
m.parse_file("engine/audio/Music.cpp")
m.parse_file("engine/audio/Sound.cpp")
m.generate_doc("engine_docs/")