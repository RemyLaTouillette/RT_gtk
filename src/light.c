/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/14 01:43:09 by nbelouni          #+#    #+#             */
/*   Updated: 2016/09/27 18:26:50 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

static inline void		magic(t_scene *s, t_color *t, t_node **tmp, t_color *c)
{
	init_color(t, 0, 0, 0);
	*tmp = s->lights;
	init_color(&c[0], 0, 0, 0);
	init_color(&c[1], 0, 0, 0);
}

static inline double	find_spot_angle(t_node *tmp_light, t_ray *ray)
{
	t_vec		look;
	t_light		*light;
	double		angle;

	light = ((t_light *)(tmp_light->data));
	if (light->type == DIRECT)
	{
		look = vec_sub(light->look_at, light->pos);
		angle = dot_product(ray->dir, look);
		angle /= get_length(ray->dir);
		angle /= get_length(look);
	}
	else
		angle = 1;
	return (angle);
}

static inline void		init_light_ray(t_node *tmp_light, t_ray *ray)
{
	t_vec		tmp;
	t_light		*light;

	light = ((t_light *)(tmp_light->data));
	if (light->type == PARALLEL)
	{
		tmp = scalar_product(light->pos, -1);
		ray->dir = normalize(tmp);
		ray->length = 100;
	}
	else
	{
		tmp = vec_sub(ray->pos, light->pos);
		ray->length = get_length(tmp);
		ray->dir = normalize(tmp);
	}
}

static inline t_color	light_it_up(t_scene *s, t_ray *r, t_hit *h, t_ray *cam)
{
	t_node		*tmp;
	t_color		tmp_color;
	t_color		c[2];
	int			shadow;

	magic(s, &tmp_color, &tmp, c);
	while (tmp)
	{
		shadow = 0;
		init_light_ray(tmp, r);
		shadow = is_shadow(s, r, &h[1]);
		if (((t_light *)(tmp->data))->type != DIRECT ||
		acos(find_spot_angle(tmp, r)) < ((t_light *)(tmp->data))->angle)
		{
			c[0] = set_color1(tmp, r, h, shadow);
			add_color(&tmp_color, &c[0]);
			if ((shadow == 0 || h[1].opacity < 1) && h[0].t != h[0].t_max)
			{
				c[1] = set_color2(tmp, cam, r, h);
				add_color(&tmp_color, &c[1]);
			}
		}
		tmp = tmp->next;
	}
	return (tmp_color);
}

t_color					apply_light(t_scene *scene, t_hit *pxl, t_ray *cam_ray)
{
	t_ray		light_ray;
	t_vec		obj_pos;
	t_hit		hit[2];

	hit[0] = *pxl;
	obj_pos = vec_add(cam_ray->pos, scalar_product(cam_ray->dir, hit[0].t));
	light_ray.pos = obj_pos;
	hit[0].color = light_it_up(scene, &light_ray, hit, cam_ray);
	return (hit[0].color);
}
