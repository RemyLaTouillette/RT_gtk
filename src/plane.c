/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhenne <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/10 03:03:34 by bhenne            #+#    #+#             */
/*   Updated: 2016/08/25 15:46:25 by tlepeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

void	complete_plane(t_hit *hit, t_plane *plane)
{
	hit->type = PLANE;
	hit->radius = 0;
	hit->color = plane->color;
	hit->pos = plane->pos;
	hit->point_norm.x = -plane->normal.x;
	hit->point_norm.y = -plane->normal.y;
	hit->point_norm.z = -plane->normal.z;
	hit->reflection = plane->reflection;
	hit->specular = plane->specular;
	hit->opacity = plane->opacity;
	hit->ref_index = plane->ref_index;
	hit->is_negativ = plane->is_negativ;
	hit->texture = plane->texture;
	hit->dir = init_vector(0, 0, 0);
}

double	find_plane_hit(t_ray *ray, t_plane *plane)
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

t_hit	is_plane_hit(t_ray *ray, t_plane *plane)
{
	t_hit	hit;
	double	res;

	hit.bool = 0;
	hit.t = 0;
	hit.color.r = 0;
	hit.color.g = 0;
	hit.color.b = 0;
	res = find_plane_hit(ray, plane);
	if (res > (double)(1.0 / PRECISION))
	{
		hit.t = res;
		hit.t_max = hit.t + 1;
		hit.bool = 1;
		complete_plane(&hit, plane);
	}
	return (hit);
}
