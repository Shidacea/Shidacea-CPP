# TODO: This is only a placeholder for the C++ wrapper class of MapLayer
class MapLayer
end

class Map2

	def initialize(view_width, view_height)
		@view_width = view_width
		@view_height = view_height

		@map_layers = []
	end

	def load_from_file(filename)
		# TODO: Read properties from file
		@number_of_layers = 3
		@width = 100
		@height = 100

		@number_of_layers.times do
			new_layer = MapLayer.new(@width, @height, @view_width, @view_height)
			# TODO: Load tiles into map layer and initialize the mesh
			@map_layers.push(new_layer)
		end
	end

	def update

	end

	def reload
		@map_layers.each {|layer| layer.reload}
	end

	def draw(window, offset)
		@map_layers.each do |layer|
			window.draw_translated(layer, offset)
		end
	end

end