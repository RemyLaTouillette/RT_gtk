/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlepeche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/08 20:00:35 by tlepeche          #+#    #+#             */
/*   Updated: 2016/09/20 17:42:43 by tlepeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

static inline t_hit		create_cyl_disk(t_ray *ray, t_cylinder *c, double side)
{
	t_hit	hit;
	t_plane	plane;
	t_vec	new_dir;
	t_vec	inter;

	new_dir = scalar_product(c->dir, side);
	plane.pos = scalar_product(new_dir, c->length * 0.5);
	plane.pos = vec_add(c->pos, plane.pos);
	plane.normal = scalar_product(new_dir, -1);
	hit.t = find_plane_hit(ray, &plane);
	hit.bool = 0;
	if (hit.t > PRECISION)
	{
		inter = vec_add(ray->pos, scalar_product(ray->dir, hit.t));
		if (get_length(vec_sub(plane.pos, inter)) <= c->radius)
		{
			hit.bool = 1;
			hit.nml = new_dir;
		}
	}
	return (hit);
}

static inline double	find_cyl_det(t_cylinder *cyl, t_intern i, double *t)
{
	double	a;
	double	b;
	double	c;
	double	det;

	a = dot_product(i.v, i.v);
	b = 2.0 * dot_product(i.v, i.oxb);
	c = dot_product(i.oxb, i.oxb);
	c -= (cyl->radius * cyl->radius * i.ab2);
	det = b * b - 4 * a * c;
	t[0] = (-b - sqrt(det)) / (2 * a);
	t[1] = (-b + sqrt(det)) / (2 * a);
	return (det);
}

static inline int		disk_hit(t_cylinder *c, t_ray *ray, t_hit *final_hit)
{
	t_hit hit_size;
	t_hit hit;

	init_hit(&hit_size);
	if (c->is_closed == 1)
	{
		hit_size = create_cyl_disk(ray, c, -1);
		hit = create_cyl_disk(ray, c, 1);
		if (hit.bool != 0)
		{
			if (hit_size.bool == 0)
			{
				hit_size.bool = 1;
				hit_size.t = hit.t;
				hit_size.nml = hit.nml;
			}
			else
			{
				complete_disk_hit(&hit, &hit_size, final_hit);
				return (1);
			}
		}
	}
	*final_hit = hit_size;
	return (0);
}

static inline t_hit		cyl_hit(t_cylinder *c, t_ray *r, t_intern i, double *t)
{
	t_hit	hit_size;
	t_hit	hit_max;
	t_hit	hit;

	init_hit(&hit);
	init_hit(&hit_max);
	if (disk_hit(c, r, &hit_size) == 1)
		return (hit_size);
	sort_distance(t);
	hit.t = t[0];
	hit_max.t = t[1];
	t[1] = find_cyl_limit(r, c, i, &hit_max);
	hit.nml_max = hit_max.nml;
	t[0] = find_cyl_limit(r, c, i, &hit);
	hit_max.nml_max = hit.nml;
	if (t[0] > PRECISION)
		return (cyl_first_try(c, &hit_size, &hit, t));
	else
	{
		hit = hit_max;
		if (t[1] > PRECISION)
			return (cyl_second_try(c, &hit_size, &hit, t));
	}
	return (cyl_third_try(c, &hit_size, &hit));
}

void					is_cylinder_hit(t_ray *ray, t_cylinder *c, t_hit *hit)
{
	t_intern	intern;
	double		t[2];

	create_cyl_intern_struct(ray, c, &intern);
	if (find_cyl_det(c, intern, t) >= 0)
	{
		*hit = cyl_hit(c, ray, intern, t);
		if (c->is_closed == 0 &&
			dot_product(ray->dir, hit->nml) > 0 && c->opacity == 1)
			hit->nml = scalar_product(hit->nml, -1);
		complete_cyl_hit(hit, c);
	}
}
