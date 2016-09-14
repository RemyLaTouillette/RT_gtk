/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlepeche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/09 15:23:50 by tlepeche          #+#    #+#             */
/*   Updated: 2016/09/10 18:35:02 by tlepeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

void	complete_cyl_hit(t_hit *hit, t_cylinder *cylinder)
{
	hit->type = CYLINDER;
	hit->radius = cylinder->radius;
	hit->length = cylinder->length;
	hit->color.r = cylinder->color.r;
	hit->color.g = cylinder->color.g;
	hit->color.b = cylinder->color.b;
	hit->dir = cylinder->dir;
	hit->opacity = cylinder->opacity;
	hit->ref_index = cylinder->ref_index;
	hit->specular = cylinder->specular;
	hit->reflection = cylinder->reflection;
	hit->texture = cylinder->texture;
	hit->is_negativ = cylinder->is_negativ;
}

double	find_cyl_limit(t_ray *ray, t_cylinder *cyl, t_intern intern, t_hit *hit)
{
	t_vec		inter;
	t_vec		proj;
	double		tmp;

	inter = vec_add(ray->pos, scalar_product(ray->dir, hit->t));
	proj = vec_sub(intern.aa, inter);
	tmp = dot_product(intern.ab, proj) / intern.ab2;
	intern.ab = scalar_product(intern.ab, tmp);
	intern.ab = vec_add(intern.ab, intern.aa);
	tmp = get_length(vec_sub(cyl->pos, intern.ab));
	hit->dist_from_center = (tmp > cyl->length / 2) ? 0 : tmp;
	if (tmp > cyl->length / 2)
		return (0.0);
	hit->point_norm = inter;
	hit->point_norm = vec_sub(intern.ab, hit->point_norm);
	hit->point_norm = normalize(hit->point_norm);
	return (hit->t);
}

t_hit	cyl_first_try(t_cylinder *cyl, t_hit hit_size, t_hit hit, double *t)
{
	hit.bool = 1;
	if (hit_size.bool == 1 && cyl->is_closed == 1)
	{
		hit.t = t[0] < hit_size.t ? t[0] : hit_size.t;
		hit.t_max = t[0] < hit_size.t ? hit_size.t : t[0];
		hit.point_norm = t[0] < hit_size.t ? hit.point_norm : hit_size.point_norm;
		hit.point_norm_max = t[0] < hit_size.t ? hit_size.point_norm : hit.point_norm;
	}
	else
	{
		hit.t = t[0];
		hit.t_max = t[1];
	}
	return (hit);
}

t_hit	cyl_second_try(t_cylinder *cyl, t_hit hit_size, t_hit hit, double *t)
{
	hit.bool = 1;
	if (hit_size.bool == 1 && cyl->is_closed == 1)
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
		if (cyl->opacity == 1)
			hit.point_norm = scalar_product(hit.point_norm, -1);
	}
	return (hit);
}

t_hit	cyl_third_try(t_cylinder *cylinder, t_hit hit_size, t_hit hit)
{
	if ((hit_size.t_max < (double)(1.0 / PRECISION) ||
		hit.t_max < (double)(1.0 / PRECISION)) && cylinder->is_closed == 1)
	{
		hit = hit_size;
		hit.t_max = hit.t;
	}
	return (hit);
}
