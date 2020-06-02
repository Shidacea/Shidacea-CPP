module ShooterTest
	class ImpulseDrive < Drive

		self.boost = 0.5
		self.max_speed = 1000.0
		self.brake = 0.05

		self.heating_rate = 0.01
		self.cooldown_rate = 0.005

	end
end