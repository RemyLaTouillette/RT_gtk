/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_tool1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/09 14:18:37 by nbelouni          #+#    #+#             */
/*   Updated: 2016/09/29 19:33:23 by tlepeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

static inline void	set_hit(t_hit *tmp, t_hit *hit, t_ray *ray, int *shadow)
{
	if (tmp->t > 0.0 && tmp->t <= ray->length)
	{
		*shadow = 1;
		if (hit->bool == 0 || tmp->opacity >= hit->opacity)
		{
			if (hit->bool == 0)
				*hit = *tmp;
			else if (hit->t > tmp->t)
				*hit = *tmp;
		}
	}
}

static inline int	find_pos_obj(t_scene *s, t_ray *ray, t_hit *hit, int *n)
{
	t_node		*tmp_object;
	t_hit		tmp_content;
	int			shadow;

	tmp_object = s->objects;
	shadow = 0;
	while (tmp_object)
	{
		if (*n == 0)
			*n = neg_exists(tmp_object);
		get_hit(ray, tmp_object, 0, &tmp_content);
		if (tmp_content.bool == 1)
			set_hit(&tmp_content, hit, ray, &shadow);
		tmp_object = tmp_object->next;
	}
	return (shadow);
}

static inline void	find_neg_obj(t_scene *s, t_ray *ray, t_hit *hit, t_hit *n)
{
	t_node		*tmp_object;
	t_hit		tmp_content;

	tmp_object = s->objects;
	while (tmp_object)
	{
		get_hit(ray, tmp_object, 1, &tmp_content);
		if (tmp_content.bool == 1 && ((tmp_content.t == tmp_content.t_max) ||
			(tmp_content.t < hit->t && tmp_content.t_max > hit->t_max)))
		{
			if ((tmp_content.t == tmp_content.t_max && tmp_content.t > n->t &&
				tmp_content.t_max < n->t_max) || (n->bool == 0) ||
					(n->t_max < tmp_content.t_max))
			{
				n->t = 0.0;
				if (n->bool == 0)
					*n = tmp_content;
				else if (n->t_max < tmp_content.t_max)
					n->t_max = tmp_content.t_max;
			}
		}
		tmp_object = tmp_object->next;
	}
}

int					is_shadow(t_scene *scene, t_ray *light_ray, t_hit *c)
{
	t_hit		neg_hit;
	int			is_neg;
	int			shadow;

	init_hit(c);
	init_hit(&neg_hit);
	is_neg = 0;
	shadow = find_pos_obj(scene, light_ray, c, &is_neg);
	if (shadow == 1 && is_neg)
	{
		find_neg_obj(scene, light_ray, c, &neg_hit);
		if (neg_hit.bool == 1)
		{
			if (neg_hit.t_max > 0.0 && neg_hit.t_max <= light_ray->length &&
					(neg_hit.t_max >= c->t_max))
				shadow = 0;
			init_hit(c);
		}
	}
	return (shadow);
}
