class SceneShooterMenu < SDC::Scene 

	def handle_event(event)
		if event.has_type?(:Closed) then
			SDC.next_scene = nil
		end
	end

end