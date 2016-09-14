/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlepeche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/08 20:00:35 by tlepeche          #+#    #+#             */
/*   Updated: 2016/09/10 20:19:29 by tlepeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

t_hit	create_cyl_disk(t_ray *ray, t_cylinder *cylinder, double side)
{
	t_hit	hit;
	t_plane	*plane;
	t_vec	new_dir;
	t_vec	inter;

	plane = (t_plane *)malloc(sizeof(t_plane));
	new_dir = scalar_product(cylinder->dir, side);
	plane->pos = scalar_product(new_dir, cylinder->length / 2.0);
	plane->pos = vec_add(cylinder->pos, plane->pos);
	plane->normal = scalar_product(new_dir, -1);
	hit.t = find_plane_hit(ray, plane);
	hit.bool = 0;
	if (hit.t > (double)(1.0 / PRECISION))
	{
		inter = vec_add(ray->pos, scalar_product(ray->dir, hit.t));
		if (get_length(vec_sub(plane->pos, inter)) <= cylinder->radius)
		{
			hit.bool = 1;
			hit.point_norm = new_dir;
		}
	}
	free(plane);
	return (hit);
}

double	find_cyl_det(t_cylinder *cyl, t_intern intern, double *t)
{
	double	a;
	double	b;
	double	c;
	double	det;

	a = dot_product(intern.v, intern.v);
	b = 2.0 * dot_product(intern.v, intern.oxb);
	c = dot_product(intern.oxb, intern.oxb);
	c -= (cyl->radius * cyl->radius * intern.ab2);
	det = b * b - 4 * a * c;
	t[0] = (-b - sqrt(det)) / (2 * a);
	t[1] = (-b + sqrt(det)) / (2 * a);
	return (det);
}

int		find_cyl_disk_hit(t_cylinder *cylinder, t_ray *ray, t_hit *final_hit)
{
	t_hit hit_size;
	t_hit hit;

	hit_size = init_hit();
	if (cylinder->is_closed == 1)
	{
		hit_size = create_cyl_disk(ray, cylinder, -1);
		hit = create_cyl_disk(ray, cylinder, 1);
		if (hit.bool != 0)
		{
			if (hit_size.bool == 0)
			{
				hit_size.bool = 1;
				hit_size.t = hit.t;
				hit_size.point_norm = hit.point_norm;
			}
			else
			{
				*final_hit = complete_disk_hit(hit, hit_size);
				return (1);
			}
		}
	}
	*final_hit = hit_size;
	return (0);
}

t_hit	cyl_hit(t_cylinder *cylinder, t_ray *ray, t_intern intern, double *t)
{
	t_hit	hit_size;
	t_hit	hit_max;
	t_hit	hit;

	hit = init_hit();
	hit_max = init_hit();
	if (find_cyl_disk_hit(cylinder, ray, &hit_size) == 1)
		return (hit_size);
	sort_distance(t);
	hit.t = t[0];
	hit_max.t = t[1];
	t[1] = find_cyl_limit(ray, cylinder, intern, &hit_max);
	hit.point_norm_max = hit_max.point_norm;
	t[0] = find_cyl_limit(ray, cylinder, intern, &hit);
	hit_max.point_norm_max = hit.point_norm;
	if (t[0] > (double)(1.0 / PRECISION))
		return (cyl_first_try(cylinder, hit_size, hit, t));
	else
	{
		hit = hit_max;
		if (t[1] > (double)(1.0 / PRECISION))
			return (cyl_second_try(cylinder, hit_size, hit, t));
	}
	return (cyl_third_try(cylinder, hit_size, hit));
}

t_hit	is_cylinder_hit(t_ray *ray, t_cylinder *cylinder)
{
	t_hit		hit;
	t_intern	intern;
	double		*t;

	hit = init_hit();
	if (!(t = (double *)malloc(sizeof(double) * (2))))
		return (hit);
	cylinder->dir = normalize(cylinder->dir);
	create_cyl_intern_struct(ray, cylinder, &intern);
	if (find_cyl_det(cylinder, intern, t) >= 0)
	{
		hit = cyl_hit(cylinder, ray, intern, t);
		if (cylinder->is_closed == 0 &&
			dot_product(ray->dir, hit.point_norm) > 0 && cylinder->opacity == 1)
			hit.point_norm = scalar_product(hit.point_norm, -1);
		complete_cyl_hit(&hit, cylinder);
	}
	free(t);
	return (hit);
}
