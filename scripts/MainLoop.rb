# This file is a template for a basic game loop
# It can be used in its current form or it can be modified

def main_routine(scene_class, title, width, height)

	begin

		$window = Window.new(title, width, height)
		$window.enable_vertical_sync

		$scene = scene_class.new

		while $window.is_open? do
			$scene.main_draw
			$scene.process_events
			$scene.main_update

			# The frequency of the Garbage Collector may be subject to change
			GC.start
		end

		$window.close

	rescue Exception => exc

		f = File.open("log.txt", "a")

		f.puts "Error in main loop at #{Time.now}:"
		f.puts exc.inspect
		f.puts ""

		f.close

		puts exc.inspect

		raise exc

	end

end