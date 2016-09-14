/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhenne <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/07 01:48:17 by bhenne            #+#    #+#             */
/*   Updated: 2016/09/14 15:58:08 by tlepeche         ###   ########.fr       */
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
# include <refraction.h>
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

//# include <save_bmp.h>
# include <aa.h>
# include <image_buffer.h>
//# include <ui.h>

# define ESCAPE		53
# define WIDTH		1920
# define HEIGHT		1080
# define PRECISION	10000000

# define N_THREAD	4

t_color		mix_color(t_color *mixed_color, int n_color);
t_color		*new_color_array(int blur_lvl);

void		*apply_depth_of_field(t_env *env, t_blur *array, double dof);
void		*apply_blur(t_env *env, int blur_lvl);
int			key_hook(int keycode, t_env *e);
void		*draw_scene(void *data);
double		deg_to_rad(double angle);

t_color		add_color(t_color a, t_color b);
void		check_color(t_color *color);
t_color		mult_color(t_color ref, double coef);
t_color		init_color(int r, int g, int b);

int			is_black_edge(t_hit *hit);

t_color		sub_color(t_color a, t_color b);
void		write_vector(t_vec v, char *name);
double		apply_marble_noise(int x, int y, double res, double **tab_noise);
double		apply_wood_noise(int x, int y, double res, double **tab_noise);
t_color		checkerboard(t_color color, t_vec vec);
int			is_black_edge(t_hit *hit);

void		*apply_blur(t_env *env, int blur_lvl);
void		*apply_depth_of_field(t_env *env, t_blur *array, double dof);
int			put_pixel_on_image(void *img, int x, int y, t_color color);
t_color		color_render(t_scene *s, t_ray *start, double noise, t_blur *blur);

t_hit		find_closest_object(t_node *nodes, t_ray *ray);
t_hit		init_hit(void);
t_hit		get_hit(t_ray *ray, t_node *nodes, int is_neg);
int			neg_exists(t_node *node);
t_hit		find_neg_hit(t_node *nodes, t_ray *ray, t_hit *c_hit, int is_neg);

void		sort_distance(double *t);
t_hit		complete_disk_hit(t_hit hit, t_hit hit_size);

void		save_bmp(unsigned char *buf);
void		ui_init(t_env *e);
#endif
