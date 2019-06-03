# This is where you want to do the most
# Each relevant scene can be defined here

class SceneTest < Scene 

	def at_init
		a = CoreEntity.new(@sprites)
		b = CoreEntity.new(@sprites)
		c = CoreEntity.new(@sprites)
		b.delete
		d = CoreEntity.new(@sprites)
		a.delete
		c.delete
		d.delete
	end

	def process_events
		while event = $window.poll_event do
			if event.type == EventType::KeyPressed then
				puts "Key Code = " + event.key_code.to_s
			elsif event.type == EventType::Closed
				$next_scene = nil
			end
		end
	end

end