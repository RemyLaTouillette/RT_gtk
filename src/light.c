/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/14 01:43:09 by nbelouni          #+#    #+#             */
/*   Updated: 2016/09/10 15:57:30 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

int		find_pos_obj(t_scene *scene, t_ray *ray, t_hit *hit, int *is_neg)
{
	t_node		*tmp_object;
	t_hit		tmp_content;
	int			shadow;

	tmp_object = scene->objects;
	shadow = 0;
	while (tmp_object)
	{
		if (*is_neg == 0)
			*is_neg = neg_exists(tmp_object);
		tmp_content = get_hit(ray, tmp_object, 0);
		if (tmp_content.bool == 1)
			set_hit(&tmp_content, hit, ray, &shadow);
		tmp_object = tmp_object->next;
	}
	return (shadow);
}

void	find_neg_obj(t_scene *scene, t_ray *ray, t_hit *hit, t_hit *neg_hit)
{
	t_node		*tmp_object;
	t_hit		tmp_content;

	tmp_object = scene->objects;
	while (tmp_object)
	{
		tmp_content = get_hit(ray, tmp_object, 1);
		if (tmp_content.bool == 1 &&
		((tmp_content.t == tmp_content.t_max) ||
		(tmp_content.t < hit->t && tmp_content.t_max > hit->t_max)))
		{
			if (neg_hit->bool == 0)
				*neg_hit = tmp_content;
			else if (neg_hit->t_max < tmp_content.t_max)
				neg_hit->t_max = tmp_content.t_max;
		}
		tmp_object = tmp_object->next;
	}
}

int		is_shadow(t_scene *scene, t_ray *light_ray, t_hit *closest_hit)
{
	t_hit		neg_hit;
	int			is_neg;
	int			shadow;

	*closest_hit = init_hit();
	neg_hit = init_hit();
	is_neg = 0;
	shadow = find_pos_obj(scene, light_ray, closest_hit, &is_neg);
	if (shadow == 1 && is_neg)
	{
		find_neg_obj(scene, light_ray, closest_hit, &neg_hit);
		if (neg_hit.bool == 1)
		{
			if (neg_hit.t_max > 0.0 && neg_hit.t_max <= light_ray->length &&
			(neg_hit.t_max >= closest_hit->t_max))
				shadow = 0;
			*closest_hit = init_hit();
		}
	}
	return (shadow);
}

t_color	light_up_it(t_scene *scene, t_ray *ray, t_hit *hit, t_ray *cam_ray)
{
	t_node		*tmp;
	t_color		tmp_color;
	t_color		*c[2];
	int			shadow;

	magic(scene, &tmp_color, &tmp, c);
	while (tmp)
	{
		shadow = 0;
		init_light_ray(tmp, ray);
		shadow = is_shadow(scene, ray, &hit[1]);
		if (((t_light *)(tmp->data))->type != DIRECT ||
		acos(find_spot_angle(tmp, ray)) < ((t_light *)(tmp->data))->angle)
		{
			if ((c[0] = set_color1(tmp, ray, hit, shadow)))
				tmp_color = add_color(tmp_color, *c[0]);
			if ((shadow == 0 || hit[1].opacity < 1) && hit[0].t != hit[0].t_max
			&& (c[1] = set_color2(tmp, cam_ray, ray, hit)))
				tmp_color = add_color(tmp_color, *c[1]);
		}
		free_colors(c);
		tmp = tmp->next;
	}
	return (tmp_color);
}

t_color	apply_light(t_scene *scene, t_hit curr_pixel, t_ray *cam_ray)
{
	t_ray		light_ray;
	t_vec		obj_pos;
	t_hit		hit[2];

	hit[0] = curr_pixel;
	obj_pos = vec_add(cam_ray->pos, scalar_product(cam_ray->dir, hit[0].t));
	light_ray.pos = obj_pos;
	hit[0].color = light_up_it(scene, &light_ray, hit, cam_ray);
	return (hit[0].color);
}
