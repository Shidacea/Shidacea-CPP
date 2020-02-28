# Framerate limiter

module SDC

	class Limiter

		def initialize(max: 720, renders_per_second: 60, ticks_per_second: 60, gc_per_second: 60)
			@counter = 0
			@max = max

			# Intervals are rounded down, for now
			@render_interval = (@max / renders_per_second).to_i
			@tick_interval = (@max / ticks_per_second).to_i
			@gc_interval = (@max / gc_per_second).to_i
		end

		# Allow for changes via options, if necessary
		def change_renders_per_second(new_value)
			@render_interval = (@max / new_value).to_i
		end

		def tick
			@timer = Time.now if @counter == 0

			if @counter % @tick_interval == 0 then
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

			if @counter % @render_interval == 0 then
				SDC.scene.main_draw
			end

			if @counter % @gc_interval == 0 then
				# Initiate garbace collector
				GC.start
			end

			@counter += 1

			if @counter == @max then
				@counter = 0
			end

			# Check how advanced the timer is
			# If it is too far ahead of the scheduled time, just stall a bit
			# This ensures a stable framerate without an desynchronization
			while (Time.now - @timer) < ((1.0 + @counter.to_f) / @max) do
			end

			return true
		end

	end

end