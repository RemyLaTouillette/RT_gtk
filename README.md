
	RAY TRACER

CONFIG :
	fichiers dans ./scenes

	SCENE : options :	-'cartoon' : (y / n)
						-'depth' : depth of field (y / n), focus : index z ou la vision est nette
						-'blur' : flou (0 - 100)
						-'filter' : ('sepia' / 'bn' (noir et blanc) / 'none')
						-'ambient' : coef de la lumiere ambiente (0.0 - 10.0)
						-'color' : couleur de la lumiere ambiente (r, g, b) (0 - 255)
						-'reflection' : nombre de reflets (1 - 5)

	CAMERA :	-pos : (x , y, z)
				-look_at : (x, y, z) direction de la camera
	OBJECTS :

	valeurs communes:	-color : (r, g, b) (0.0 - 1.0)
			
			options:	-specular : brillance (0 - 100)
						-reflection : taux de reflexion (0.0 - 1.0)
						-opacity : (0.0 - 1.0)
						-ref_index : indice de refraction (1.0 - 10.0)
						-is_negativ : object negatif ( = fait des trous) (y / n)
						-texture : ('marble' / 'checker' / 'none')
	
	valeurs specifiques a chaque object:

			sphere :						-radius
											-pos : (x , y, z)
			cone / cylinder :				-radius
											-length
											-dir : (x, y, z)
					options	:				-is_closed : (y / n) 
											.si le cone / cylindre est ouvert, l'indice de refraction est toujours egal a 1
                                			
			plane:							-normal : (x, y, z)
											-pos : (x , y, z)
											.l'indice de refraction est toujours egal a 1
											
			elips (elipsoide) :				-radius
											-pos : (x, y, z)
											-quad : (x, y, z), plus le nombre est petit, plus l'elipse est etiree sur l'axe (0.01 - 5.0)
                                			
			triangle :						-v1 : (x, y, z)
											-v2 : (x, y, z)
											-v3 : (x, y, z)
											.v1, v2, v3 sont les points qui definissent le triangle
											.l'indice de refraction est toujours egal a 1


			parallelo (parallelogramme) :	-v1 : (x, y, z)
											-v2 : (x, y, z)
											-v3 : (x, y, z)
											.v1, v2, v3 sont les points qui definissent le triangle qui sert de base au parallelogramme
											.l'indice de refraction est toujours egal a 1

			tetra (tetraede) :				-v1 : (x, y, z)
											-v2 : (x, y, z)
											-v3 : (x, y, z)
											-v4 : (x, y, z)
											.v1, v2, v3, v4 sont les points qui definissent le tetraede

	LIGHTS :

	valeurs communes:	-color : (r, g, b) (0 - 255)

	valeurs specifiques a chaque type de lumiere :

			diffuse :	-pos : (x, y, z)

			parallel :	-pos : direction de la lumiere (x, y, z)

			direct :	-pos : (x, y, z)
						-angle : (0 - 180)
						-dir: direction de la lumiere (x, y, z)

- x, y, z (respectivement : horizontal (-1 gauche, 1 droite), vertical (-1 haut, 1 bas), profondeur (-1 vers camera, 1 inverse))
