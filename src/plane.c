/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhenne <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/10 03:03:34 by bhenne            #+#    #+#             */
/*   Updated: 2016/09/28 20:01:12 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

static inline void		complete_plane(t_hit *hit, t_plane *plane)
{
	hit->type = PLANE;
	hit->radius = 0.0;
	hit->color = plane->color;
	hit->nml.x = -plane->normal.x;
	hit->nml.y = -plane->normal.y;
	hit->nml.z = -plane->normal.z;
	hit->dist_from_center = 0.0;
	hit->reflection = plane->reflection;
	hit->specular = plane->specular;
	hit->opacity = plane->opacity;
	hit->ref_index = plane->ref_index;
	hit->is_negativ = plane->is_negativ;
	hit->texture = plane->texture;
	hit->dir = init_vector(0, 0, 0);
}

double					find_plane_hit(t_ray *ray, t_plane *plane)
{
	double	tmp_magic;
	double	tmp;

	if ((tmp_magic = dot_product(plane->normal, ray->dir)) == 0.0)
		return (0);
	else
	{
		tmp = -(dot_product(plane->normal, vec_sub(plane->pos, ray->pos)));
		return (tmp / tmp_magic);
	}
}

void					is_plane_hit(t_ray *ray, t_plane *plane, t_hit *hit)
{
	double	res;

	res = find_plane_hit(ray, plane);
	if (res > PRECISION)
	{
		hit->t = res;
		hit->t_max = hit->t + 1;
		hit->bool = 1;
		complete_plane(hit, plane);
	}
}
