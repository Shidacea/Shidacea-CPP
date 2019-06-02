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

end