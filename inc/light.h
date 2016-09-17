/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/13 22:39:57 by nbelouni          #+#    #+#             */
/*   Updated: 2016/09/14 18:46:02 by tlepeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _LIGHT_H
# define _LIGHT_H

# include <scene.h>
# include <ray.h>

# define DIFFUSE	1
# define PARALLEL	2
# define DIRECT		3

typedef struct	s_light
{
	int			type;
	t_vec		pos;
	t_vec		look_at;
	t_color		color;
	double		angle;
}				t_light;

t_color			apply_light(t_scene *scene, t_hit curr_pixel, t_ray *cam_ray);
t_color			diffuse_shadow(t_hit px, t_ray *ray, t_light *light, t_hit tmp);
t_color			diffuse_light(t_hit curr_px, t_ray *light_ray, t_light *light);
t_color			specular_light(t_hit px, t_vec ref, t_light *l, t_ray *ray);
double			find_spot_angle(t_node *tmp_light, t_ray *ray);
t_color			*set_color1(t_node *tmp, t_ray *ray, t_hit *hit, int shadow);
t_color			*set_color2(t_node *tmp, t_ray *cam, t_ray *ray, t_hit *hit);
void			init_light_ray(t_node *tmp_light, t_ray *ray);
void			magic(t_scene *s, t_color *color, t_node **tmp, t_color **c);
void			free_colors(t_color **c);
void			set_hit(t_hit *tmp_cont, t_hit *hit, t_ray *ray, int *shadow);

#endif
