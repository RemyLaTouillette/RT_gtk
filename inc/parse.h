/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/27 14:27:54 by nbelouni          #+#    #+#             */
/*   Updated: 2016/09/15 13:52:13 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include <scene.h>
# include <fcntl.h>
# include <quad.h>
# include <sphere.h>
# include <cyco_internal_struct.h>
# include <cylinder.h>
# include <cone.h>
# include <plane.h>
# include <elipsoid.h>
# include <triangle.h>
# include <tetra.h>
# include <parallelo.h>

typedef struct		s_e_tool
{
	t_vec			*vec;
	t_quad			*quad;
	t_color			*color;
}					t_e_tool;

typedef struct		s_elem
{
	char			*name;
	int				n_values;
	char			**values;
	struct s_elem	*next;
}					t_elem;

typedef struct		s_part
{
	int				type;
	int				n_elems;
	t_elem			*elems;
	struct s_part	*sub_parts;
	struct s_part	*next;
}					t_part;

t_part				*create_part(void);
void				free_part(t_part **part);
t_elem				*create_elem(void);
void				free_elem(t_elem **elem);

int					arr_len(char **array);
char				**cpy_carray(char **array);

int					return_invalid_arg(char *name);

int					is_number(char *s);
int					is_valid(char *s);
int					is_initialized(int *is_init, t_scene *scene);

t_sphere			*init_sphere(void);
t_plane				*init_plane(void);
t_cylinder			*init_cylinder(void);
t_cone				*init_cone(void);
t_elips				*init_elips(void);
t_triangle			*init_triangle(void);
t_tetra				*init_tetra(void);
t_parallelo			*init_para(void);

int					cyl_invalid(t_cylinder *cyl, t_vec **v, t_color *c);
int					cone_invalid(t_cone *cyl, t_vec **v, t_color *c);
int					elips_invalid(t_elips *elips, t_e_tool *tool);
int					triangle_invalid(t_triangle *t, t_vec *v[3], t_color *c);
int					tetra_invalid(t_tetra *tetra, t_vec **v, t_color *color);
int					get_c_att1(t_elem *t, t_vec **p, t_vec **dir, t_color **c);

t_vec				*get_vec(char **values, char *name);
float				get_num(char **values);
int					get_bool(char **values);
int					get_enum(char **values);
t_color				*get_color(char **values, int ref);
t_quad				*get_quad(char **values);
int					get_is(t_elem *elem, int *is_negativ);
int					get_secur_is(t_elem *elem, int *is);
int					get_secur_num(t_elem *e, double *n, double min, double max);
int					get_secur_enum(t_elem *elem, int *e);

int					get_unsigned_double(t_elem *elem, double *radius);
int					get_new_vec(t_elem *elem, t_vec **pos);
int					get_new_quad(t_elem *elem, t_quad **quad);
int					get_new_color(t_elem *elem, t_color **color, int type);

t_scene				*get_scene(t_scene *scene, t_part *part);
t_cam				*get_cam(t_scene *scene, t_part *part);
t_scene				*get_lights(t_scene *scene, t_part *part);
t_scene				*get_objects(t_scene *scene, t_part *part);
t_plane				*get_plane(t_part *part);
t_sphere			*get_sphere(t_part *part);
t_cylinder			*get_cylinder(t_part *part);
t_cone				*get_cone(t_part *part);
t_elips				*get_elips(t_part *part);
t_triangle			*get_triangle(t_part *part);
t_parallelo			*get_para(t_part *part);
t_tetra				*get_tetra(t_part *part);

char				*get_file_content(char *file_name);
int					find_type(char *s);
char				*find_scop(char *s, int ref_level);
t_part				*parse_scop(char *scop);

t_scene				*parse(char *file_name);

#endif
