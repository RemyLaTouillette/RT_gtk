/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_tool1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/09 14:18:37 by nbelouni          #+#    #+#             */
/*   Updated: 2016/09/10 15:26:12 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

t_color	diffuse_shadow(t_hit px, t_ray *ray, t_light *light, t_hit tmp)
{
	double	angle;
	double	coef;
	t_color	tmp_color;

	angle = fabs(dot_product(ray->dir, px.point_norm));
	coef = 1 - tmp.opacity;
	tmp_color.r = px.color.r * angle * light->color.r * coef;
	tmp_color.g = px.color.g * angle * light->color.g * coef;
	tmp_color.b = px.color.b * angle * light->color.b * coef;
	return (tmp_color);
}

t_color	diffuse_light(t_hit curr_px, t_ray *light_ray, t_light *light)
{
	double	angle;
	double	coef;
	t_color	tmp_color;

	angle = dot_product(light_ray->dir, curr_px.point_norm);
	angle /= get_length(light_ray->dir);
	angle /= get_length(curr_px.point_norm);
	tmp_color = init_color(0, 0, 0);
	coef = curr_px.opacity;
	if (angle < 0)
	{
		angle = -angle;
		if (curr_px.opacity >= 0.5)
			coef = 1 - curr_px.opacity;
	}
	tmp_color.r = curr_px.color.r * angle * light->color.r * coef;
	tmp_color.g = curr_px.color.g * angle * light->color.g * coef;
	tmp_color.b = curr_px.color.b * angle * light->color.b * coef;
	return (tmp_color);
}

t_color	specular_light(t_hit px, t_vec ref, t_light *light, t_ray *cam_ray)
{
	t_color	tmp_color;
	double	spec;
	double	coef;
	double	tmp;

	tmp = dot_product(normalize(cam_ray->dir), normalize(ref));
	if (px.opacity == 1)
		spec = pow(tmp, px.specular + 1);
	else
		spec = pow(tmp, px.specular);
	if (spec < 0)
		coef = fabs(spec) * px.opacity;
	else
		coef = 1;
	tmp_color.r = spec * light->color.r * coef;
	tmp_color.g = spec * light->color.g * coef;
	tmp_color.b = spec * light->color.b * coef;
	return (tmp_color);
}

double	find_spot_angle(t_node *tmp_light, t_ray *ray)
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

void		set_hit(t_hit *tmp_content, t_hit *hit, t_ray *ray, int *shadow)
{
	if (tmp_content->t > 0.0 && tmp_content->t <= ray->length)
	{
		*shadow = 1;
		if (hit->bool == 0 || tmp_content->opacity >= hit->opacity)
		{
			if (hit->bool == 0)
				*hit = *tmp_content;
			else if (hit->t > tmp_content->t)
				*hit = *tmp_content;
		}
	}
}
