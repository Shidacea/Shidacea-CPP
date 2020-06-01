module ShooterTest
	class PlayerShip < ShooterTest::Ship
		register_id :PlayerShip

		SDC::Data.load_texture(:PlayerShip, filename: "assets/graphics/Ship.png")
		add_sprite(index: 0, texture_index: :PlayerShip, rect: SDC::IntRect.new(0, 0, 40, 60), origin: SDC.xy(20, 30))

		self.max_speed = 100.0

	end
end