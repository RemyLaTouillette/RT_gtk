/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlepeche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/09 15:23:31 by tlepeche          #+#    #+#             */
/*   Updated: 2016/09/10 20:11:28 by tlepeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

void	complete_cone_hit(t_hit *hit, t_cone *cone)
{
	hit->type = CONE;
	hit->length = cone->len;
	hit->dir = cone->dir;
	hit->radius = cone->r;
	hit->specular = cone->specular;
	hit->reflection = cone->reflection;
	hit->texture = cone->texture;
	hit->is_negativ = cone->is_negativ;
	hit->color.r = cone->color.r;
	hit->color.g = cone->color.g;
	hit->color.b = cone->color.b;
	hit->opacity = cone->opacity;
	hit->ref_index = cone->ref_index;
}

double	find_cone_limit(t_ray *ray, t_cone *cone, t_intern intern, t_hit *hit)
{
	t_vec	inter;
	t_vec	proj;
	double	tmp;
	double	angle;

	inter = vec_add(ray->pos, scalar_product(ray->dir, hit->t));
	proj = vec_sub(intern.aa, inter);
	tmp = dot_product(intern.ab, proj) / intern.ab2;
	intern.ab = scalar_product(intern.ab, tmp);
	intern.ab = vec_add(intern.ab, intern.aa);
	proj = intern.ab;
	proj = vec_sub(cone->pos, proj);
	tmp = get_length(proj);
	hit->dist_from_center = (tmp > cone->len) ? 0 : tmp;
	if (tmp > cone->len)
		return (0.0);
	hit->point_norm = inter;
	hit->point_norm = vec_sub(cone->pos, inter);
	angle = atan(cone->r / cone->len);
	tmp = get_length(hit->point_norm) / cos(angle);
	proj = scalar_product(normalize(proj), tmp);
	hit->point_norm = normalize(vec_sub(proj, hit->point_norm));
	return (hit->t);
}

t_hit	cone_first_try(t_cone *cone, t_hit hit_size, t_hit hit, double *t)
{
	hit.bool = 1;
	if (hit_size.bool == 1 && cone->is_closed == 1)
	{
		hit.t = t[0] < hit_size.t ? t[0] : hit_size.t;
		hit.t_max = t[0] < hit_size.t ? hit_size.t : t[0];
		hit.point_norm_max = t[0] < hit_size.t ? hit_size.point_norm : hit.point_norm;
		hit.point_norm = t[0] < hit_size.t ? hit.point_norm : hit_size.point_norm;
	}
	else
	{
		hit.t = t[0];
		hit.t_max = t[1];
	}
	return (hit);
}

t_hit	cone_second_try(t_cone *cone, t_hit hit_size, t_hit hit, double *t)
{
	hit.bool = 1;
	if (hit_size.bool == 1 && cone->is_closed == 1)
	{
		hit.t = t[1] < hit_size.t ? t[1] : hit_size.t;
		hit.t_max = t[1] < hit_size.t ? hit_size.t : t[1];
		hit.point_norm = t[1] < hit_size.t ? hit.point_norm : hit_size.point_norm;
		hit.point_norm_max = t[1] < hit_size.t ? hit_size.point_norm : hit.point_norm;
	}
	else
	{
		hit.t = t[1];
		hit.t_max = t[1];
	}
	return (hit);
}

t_hit	cone_third_try(t_cone *cone, t_hit hit_size, t_hit hit)
{
	if ((hit_size.t_max < (double)(1.0 / PRECISION) ||
		hit.t_max < (double)(1.0 / PRECISION)) && cone->is_closed == 1)
	{
		hit = hit_size;
		hit.t_max = hit.t;
	}
	return (hit);
}
