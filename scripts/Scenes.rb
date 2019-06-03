# This is where you want to do the most
# Each relevant scene can be defined here

class SceneTest < Scene 

	def handle_event(event)
		if event.type == EventType::KeyPressed then
			puts "Key Code = " + event.key_code.to_s
		elsif event.type == EventType::Closed
			$next_scene = nil
		end
	end

end