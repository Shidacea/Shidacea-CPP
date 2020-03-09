class SceneMain < SDC::Scene

	def update
		SDC.next_scene = SceneTest
	end

end