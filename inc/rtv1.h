/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhenne <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/07 01:48:17 by bhenne            #+#    #+#             */
/*   Updated: 2016/10/03 19:55:33 by tlepeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _RTV1_H
# define _RTV1_H

# include <math.h>
# include <stdlib.h>

# include <gtk/gtk.h>
# include <libft.h>

# include <objects.h>
# include <scene.h>
# include <vector.h>
# include <camera.h>
# include <node.h>
# include <light.h>
# include <parse.h>
# include <ray.h>
# include <thread.h>

# include <cyco_internal_struct.h>
# include <cone.h>
# include <cylinder.h>
# include <parallelo.h>
# include <triangle.h>
# include <plane.h>
# include <sphere.h>
# include <elipsoid.h>
# include <quad.h>
# include <tetra.h>
# include <error_handler.h>

# include <aa.h>
# include <image_buffer.h>
# include <ui_init.h>

# include <texture_mapping.h>

# define ESCAPE		53
# define WIDTH		1920
# define HEIGHT		1080
# define PRECISION	0.000001

# define N_THREAD	4

t_color		*new_color_array(int blur_lvl);

void		apply_depth_of_field(void *b, void *n, t_scene *s, t_iter *iter);
void		apply_blur(void *b, void *n, int blur_lvl, t_iter *iter);
int			key_hook(int keycode, t_env *e);

void		test_blur(int r, t_hit *pxl, double *blur);
void		find_blur_dist(t_ray *st, t_hit *hit, t_cam *cam, double *b);
void		*draw_scene(void *data);
t_color		color_render(t_scene *s, t_ray *start, t_text *text, double *blur);

double		deg_to_rad(double angle);
t_color		mix_color(t_color *mixed_color, int n_color);
void		add_color(t_color *a, t_color *b);
void		check_color(t_color *color);
void		mult_color(t_color *ref, double coef);
void		init_color(t_color *color, int r, int g, int b);

int			is_black_edge(t_hit *hit);
t_color		cartoon(t_color *color);

void		write_vector(t_vec v, char *name);
double		apply_marble_noise(int x, int y, double res, double **tab_noise);
double		apply_wood_noise(int x, int y, double res, double **tab_noise);
t_color		checkerboard(t_color color, t_vec vec);
int			is_black_edge(t_hit *hit);

void		find_closest_object(t_node *nodes, t_ray *ray, t_hit *h);
void		init_hit(t_hit *hit);
void		get_hit(t_ray *ray, t_node *nodes, int is_neg, t_hit *t);
int			neg_exists(t_node *node);
t_hit		find_neg_hit(t_node *nodes, t_ray *ray, t_hit *c_hit, int is_neg);

void		sort_distance(double *t);
void		complete_disk_hit(t_hit *hit, t_hit *hit_size, t_hit *final_hit);

void		save_bmp(unsigned char *buf);
void		save_jpeg(unsigned char *buf);
void		ui_init(t_env *e);
void		check_scene(t_env *e);
double		**create_tab_noise(void);
void		init_threads(t_thread *threads, t_env *e);

int			scene_cmp(t_scene *new_scene, t_scene *old_scene);
int			objects_cmp(t_node *new_obj, t_node *old_obj);
int			sphere_cmp(t_sphere *new, t_sphere *old);
int			cylinder_cmp(t_cylinder *new, t_cylinder *old);
int			cone_cmp(t_cone *new, t_cone *old);
int			plane_cmp(t_plane *new, t_plane *old);
int			elips_cmp(t_elips *new, t_elips *old);
int			triangle_cmp(t_triangle *new, t_triangle *old);
int			para_cmp(t_parallelo *new, t_parallelo *old);
int			tetra_cmp(t_tetra *new, t_tetra *old);
int			vec_cmp(t_vec v1, t_vec v2);
int			ray_cmp(t_ray r1, t_ray r2);
int			color_cmp(t_color c1, t_color vc);
int			quad_cmp(t_quad q1, t_quad q2);
int			lights_cmp(t_node *new_lights, t_node *old_lights);
int			free_and_return(void *ptr, int i);

t_color		apply_refraction(t_ray *st, t_scene *s, t_hit *hit, t_text *t);
GdkPixbuf	*get_texture(void);

#endif
