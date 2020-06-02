module ShooterTest
	class Drive

		attr_reader :max_speed, :boost, :brake, :overheated

		extend SDCMeta::ClassProperty
		
		self.define_class_property(:boost, default: 0.5)
		self.define_class_property(:max_speed, default: 100.0)
		self.define_class_property(:brake, default: 0.05)
		self.define_class_property(:heating_rate, default: 0.0)
		self.define_class_property(:heat_threshold, default: 1.0)
		self.define_class_property(:cooldown_heat, default: 0.0)
		self.define_class_property(:cooldown_rate, default: 0.0)

		def initialize
			@heat_level = 0
			@overheated = false
			@running = false
		end

		def run
			@heat_level += self.heating_rate
			if @heat_level >= self.heat_threshold then
				@overheated = true
			end
			@running = true
		end

		def idle
			@heat_level -= self.cooldown_rate
			if @heat_level < self.cooldown_rate then
				@overheated = false
			end
			@heat_level = 0 if @heat_level < 0
		end

		def update
			idle if !@running
			@running = false
		end

		# TODO: Stamina
		
	end
end