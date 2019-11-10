module SDC
	module AI

		class Script
		
			def initialize(&block)
				@fiber = Fiber.new {block.call}
			end

			def tick
				@fiber.resume
			end

			def running?
				return @fiber.alive?
			end

		end

		def self.done
			Fiber.yield
		end

		def self.wait(n)
			n.times {done}
		end

		def self.once(&block)
			block.call
			done
		end

		def self.times(n, &block)
			n.times do
				block.call
				done
			end
		end

		def self.forever(&block)
			loop do
				block.call
				done
			end
		end

	end

end