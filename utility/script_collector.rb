script_directory = ARGV[0]

output_directory = ARGV[1]
header_output_file = ARGV[2]
list_output_file = ARGV[3]

script_file = ARGV[4]
name = ARGV[5]
define_value = ARGV[6]

header = File.open(output_directory + header_output_file, "w")
list = File.open(output_directory + list_output_file, "w")

header.puts '#pragma once'
header.puts
header.puts '#include "MrbLoad.h"'
header.puts
header.puts "#ifdef #{define_value}"

script_file_content = ""
f = File.open(script_file, "r")
while !f.eof?
	script_file_content += f.readline
end
f.close

parsed_json = JSON.parse(script_file_content)

counter = 0
parsed_json["scripts"].each do |script|
	header.puts "#include \"compiled_scripts/script_#{name}_#{counter}.h\""
	list.puts script

	counter += 1
end

header.puts '#endif'
header.puts
header.puts "inline void load_#{name}_scripts(mrb_state* mrb) {\n"

counter = 0
parsed_json["scripts"].each do |script|
	if script[-1] == '/' || script[-1] == '\\' then
		# Directory
		header.puts "\tMRB_LOAD_#{name.upcase}_SCRIPT_FOLDER(mrb, script_#{name}_#{counter}, #{script[0..-2]});"
	else
		# File
		header.puts "\tMRB_LOAD_#{name.upcase}_SCRIPT(mrb, script_#{name}_#{counter}, #{script});"
	end

	counter += 1
end

header.puts
header.puts '}'

header.close
list.close
