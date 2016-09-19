
	RAY TRACER

CONFIG :
	files in ./scenes

	SCENE : options :	-'cartoon' : (y / n)
						-'depth' : depth of field (y / n), focus : z index where you have a clear vision
						-'blur' : blur (0 - 100)
						-'filter' : ('sepia' / 'bn' (black and white) / 'none')
						-'ambient' : ambiente light coef (0.0 - 10.0)
						-'color' : ambient light color (r, g, b) (0 - 255)
						-'reflection' : number of reflects (1 - 5)

	CAMERA :	-pos : (x , y, z)
				-look_at : (x, y, z) camera direction
	OBJECTS :

	common values:	-color : (r, g, b) (0.0 - 1.0)
			
			options:	-specular : shine (0 - 100)
						-reflection : refection rate (0.0 - 1.0)
						-opacity : (0.0 - 1.0)
						-ref_index : index of refraction (1.0 - 10.0)
						-is_negativ : negatives objects ( = make holes) (y / n)
						-texture : ('marble' / 'checker' / 'none')
						.if option undefined, a default value is set

	specific value for each objects:

			sphere :						-radius
											-pos : (x , y, z)
			cone / cylinder :				-radius
											-length
											-dir : (x, y, z)
					options	:				-is_closed : (y / n) 
											.if cone / cylinder is open, the index of refraction is always set to 1
                                			
			plane:							-normal : (x, y, z)
											-pos : (x , y, z)
											.index of refraction is always set to 1
											
			elips (elipsoide) :				-radius
											-pos : (x, y, z)
											-quad : (x, y, z), the smaller the number is, the stretcher the axe is (0.01 - 5.0)
                                			
			triangle :						-v1 : (x, y, z)
											-v2 : (x, y, z)
											-v3 : (x, y, z)
											.v1, v2, v3 are the apex that define the triangle
											.index of refraction is always set to 1


			parallelo (parallelogramme) :	-v1 : (x, y, z)
											-v2 : (x, y, z)
											-v3 : (x, y, z)
											.v1, v2, v3 are the apex of the triangle which is used as the parallelogramme base.
											.index of refraction is always set to 1

			tetra (tetraedre) :				-v1 : (x, y, z)
											-v2 : (x, y, z)
											-v3 : (x, y, z)
											-v4 : (x, y, z)
											.v1, v2, v3, v4 are the apex that define the tetraedre

	LIGHTS :

	commons values:	-color : (r, g, b) (0 - 255)

	specifics values for each type of light :

			diffuse :	-pos : (x, y, z)

			parallel :	-pos : light direction (x, y, z)

			direct :	-pos : (x, y, z)
						-angle : (0 - 180)
						-dir: light direction (x, y, z)

- x, y, z (respectively: horizontally (-1 left, 1 right), vertically (-1 up, 1 down), depth (-1 toward the camera, 1 opposite direction))
