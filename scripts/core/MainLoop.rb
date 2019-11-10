# This file is a template for a basic game loop
# It can be used in its current form or it can be modified

def main_routine(scene_class, title, width, height)

	begin
		SDC.resource_manager = ResourceManager.new

		SDC.window = Window.new(title, width, height)
		SDC.window.enable_vertical_sync

		SDC.game = SDC::Game.new

		SDC.scene = scene_class.new
		SDC.next_scene = true

		while SDC.window.is_open? do
			SDC.scene.main_draw
			SDC.scene.process_events
			SDC.scene.main_update 

			if !SDC.next_scene then	# Terminate program
				SDC.scene.at_exit
				SDC.scene = nil
				break
			elsif SDC.next_scene != true then	# Change scene
				SDC.scene.at_exit
				SDC.scene = SDC.next_scene.new
				SDC.next_scene = true
				SDC.scene.at_init
			end

			# The frequency of the Garbage Collector may be subject to change
			GC.start
		end

		SDC.window.close

	rescue Exception => exc
		f = File.open("log.txt", "a")

		f.puts "Error in main loop at #{Time.now}:"
		f.puts exc.inspect
		f.puts exc.backtrace.join("\n")
		f.puts ""

		f.close

		raise exc
	end

end