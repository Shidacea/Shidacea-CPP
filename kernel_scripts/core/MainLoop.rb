# This file is a template for a basic game loop
# It can be used in its current form or it can be modified

def main_routine(scene_class, title, width, height)

	begin
		SDC.window = SDC::Window.new(title, width, height)
		SDC.limiter = SDC::Limiter.new(max: 720, renders_per_second: 60, ticks_per_second: 60, gc_per_second: 60)

		# Update routine, formulated as block for the limiter
		SDC.limiter.set_update_routine do
			SDC.scene.process_events
			SDC.scene.main_update

			if !SDC.next_scene then	# Terminate program
				SDC.scene.at_exit
				SDC.scene = nil
				return false
			elsif SDC.next_scene != true then	# Change scene
				SDC.scene.at_exit
				SDC.scene = SDC.next_scene.new
				SDC.next_scene = true
				SDC.scene.at_init
			end
		end

		# Drawing routine
		SDC.limiter.set_draw_routine do
			SDC.scene.main_draw
		end

		# Garbage collecting routine
		SDC.limiter.set_gc_routine do
			# Initiate garbace collector
			GC.start
		end

		SDC.game = SDC::Game.new

		SDC.scene = scene_class.new
		SDC.next_scene = true

		while SDC.window.is_open? do
			# If it returns a false value, the game scene was set to nil
			break if !SDC.limiter.tick
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