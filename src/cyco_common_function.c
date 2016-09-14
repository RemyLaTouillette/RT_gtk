/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cyco_common_function.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlepeche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/09 16:28:41 by tlepeche          #+#    #+#             */
/*   Updated: 2016/09/10 18:17:04 by tlepeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

t_hit	complete_disk_hit(t_hit hit, t_hit hit_size)
{
	t_hit	final_hit;

	final_hit = hit;
	if (hit_size.t < final_hit.t)
	{
		final_hit.t_max = final_hit.t;
		final_hit.t = hit_size.t;
		final_hit.point_norm_max = final_hit.point_norm;
		final_hit.point_norm = hit_size.point_norm;
	}
	else
	{
		final_hit.t_max = hit_size.t;
		final_hit.point_norm_max = hit_size.point_norm;
	}
	return (final_hit);
}

void	sort_distance(double *t)
{
	double t1;
	double t2;

	t1 = t[0] < t[1] ? t[0] : t[1];
	t2 = t[0] < t[1] ? t[1] : t[0];
	t[0] = t1;
	t[1] = t2;
}

void	create_cyl_intern_struct(t_ray *ray, t_cylinder *cyl, t_intern *intern)
{
	intern->aa = vec_add(cyl->pos, cyl->dir);
	intern->ab = vec_sub(cyl->pos, intern->aa);
	intern->v = vec_sub(intern->aa, ray->pos);
	intern->oxb = cross_product(intern->v, intern->ab);
	intern->v = cross_product(ray->dir, intern->ab);
	intern->ab2 = dot_product(intern->ab, intern->ab);
}

void	create_cone_intern_struct(t_ray *ray, t_cone *cone, t_intern *intern)
{
	intern->aa = vec_add(cone->pos, cone->dir);
	intern->ab = vec_sub(cone->pos, intern->aa);
	intern->v = vec_sub(intern->aa, ray->pos);
	intern->oxb = cross_product(intern->v, intern->ab);
	intern->v = cross_product(ray->dir, intern->ab);
	intern->ab2 = dot_product(intern->ab, intern->ab);
	intern->delta = vec_sub(cone->pos, ray->pos);
	intern->x = dot_product(ray->dir, cone->dir);
	intern->y = dot_product(intern->delta, cone->dir);
}
