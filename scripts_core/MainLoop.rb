# This file is a template for a basic game loop
# It can be used in its current form or it can be modified

def main_routine(scene_class, title, width, height)

	begin
		SDC.window = SDC::Window.new(title, width, height)
		SDC.limiter = SDC::Limiter.new(max: 720, renders_per_second: 60, ticks_per_second: 60, gc_per_second: 60)

		SDC.game = SDC::Game.new

		SDC.scene = scene_class.new
		SDC.next_scene = true

		while SDC.window.is_open? do
			# Main game loop logic is contained within the limiter
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