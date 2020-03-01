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

			@update_block = nil
			@draw_block = nil
			@gc_block = nil
		end

		def set_update_routine(&block)
			@update_block = block
		end

		def set_draw_routine(&block)
			@draw_block = block
		end

		def set_gc_routine(&block)
			@gc_block = block
		end

		# Allow for changes via options, if necessary
		def change_renders_per_second(new_value)
			@render_interval = (@max / new_value).to_i
		end

		def tick
			@timer = Time.now if @counter == 0

			if @counter % @tick_interval == 0 then
				@update_block&.call
			end

			if @counter % @render_interval == 0 then
				@draw_block&.call
			end

			if @counter % @gc_interval == 0 then
				@gc_block&.call
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