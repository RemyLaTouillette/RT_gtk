/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_tool2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/09 14:21:37 by nbelouni          #+#    #+#             */
/*   Updated: 2016/09/09 14:26:22 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

void		free_colors(t_color **c)
{
	if (c[0])
	{
		free(c[0]);
		c[0] = NULL;
	}
	if (c[1])
	{
		free(c[1]);
		c[1] = NULL;
	}
}

void		magic(t_scene *scene, t_color *tmp_color, t_node **tmp, t_color **c)
{
	*tmp_color = init_color(0, 0, 0);
	*tmp = scene->lights;
	c[0] = NULL;
	c[1] = NULL;
}

void		init_light_ray(t_node *tmp_light, t_ray *ray)
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

t_color		*set_color1(t_node *tmp, t_ray *ray, t_hit *hit, int shadow)
{
	t_color		*c2;

	if (!(c2 = (t_color *)malloc(sizeof(t_color))))
		return (NULL);
	if (shadow == 0 || hit[0].opacity < 1)
		*c2 = diffuse_light(hit[0], ray, ((t_light *)(tmp->data)));
	else if (hit[1].opacity < 1 && shadow == 1)
		*c2 = diffuse_shadow(hit[0], ray, ((t_light *)(tmp->data)), hit[1]);
	else
	{
		free(c2);
		return (NULL);
	}
	return (c2);
}

t_color		*set_color2(t_node *tmp, t_ray *cam_ray, t_ray *ray, t_hit *hit)
{
	t_color		*c2;
	t_vec		refl;
	double		dot;

	if (!(c2 = (t_color *)malloc(sizeof(t_color))))
		return (NULL);
	dot = dot_product(ray->dir, hit[0].point_norm);
	refl = vec_sub(scalar_product(hit[0].point_norm, dot * 2), ray->dir);
	*c2 = (specular_light(hit[0], refl, ((t_light *)(tmp->data)), cam_ray));
	return (c2);
}
