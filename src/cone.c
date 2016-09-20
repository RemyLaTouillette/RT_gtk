/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlepeche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/09 15:10:51 by tlepeche          #+#    #+#             */
/*   Updated: 2016/09/20 17:52:09 by tlepeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

static inline t_hit		create_cone_disk(t_ray *ray, t_cone *cone, double side)
{
	t_hit	hit;
	t_plane	plane;
	t_vec	new_dir;
	t_vec	inter;

	new_dir = scalar_product(cone->dir, side);
	plane.pos = vec_add(cone->pos, scalar_product(new_dir, cone->len));
	plane.normal = scalar_product(new_dir, -1);
	hit.t = find_plane_hit(ray, &plane);
	hit.bool = 0;
	if (hit.t > PRECISION)
	{
		inter = vec_add(ray->pos, scalar_product(ray->dir, hit.t));
		if (get_length(vec_sub(plane.pos, inter)) <= cone->r)
		{
			hit.bool = 1;
			hit.nml = new_dir;
		}
	}
	return (hit);
}

static inline double	find_cone_det(t_intern intern, double angle, double *t)
{
	double	a;
	double	b;
	double	c;
	double	det;

	a = c2(angle) * dot_product(intern.v, intern.v);
	a -= s2(angle) * intern.x * intern.x;
	b = 2.0 * c2(angle) * dot_product(intern.v, intern.oxb);
	b -= 2.0 * s2(angle) * intern.x * intern.y;
	c = c2(angle) * dot_product(intern.oxb, intern.oxb);
	c -= s2(angle) * intern.y * intern.y;
	det = b * b - 4 * a * c;
	t[0] = (-b - sqrt(det)) / (2 * a);
	t[1] = (-b + sqrt(det)) / (2 * a);
	return (det);
}

static inline int		disk_hit(t_cone *cone, t_ray *ray, t_hit *final_hit)
{
	t_hit	hit_size;
	t_hit	hit;

	init_hit(&hit_size);
	if (cone->is_closed == 1)
	{
		hit_size = create_cone_disk(ray, cone, -1);
		hit = create_cone_disk(ray, cone, 1);
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

static inline t_hit		cone_hit(t_cone *cone, t_ray *r, t_intern i, double *t)
{
	t_hit	hit_size;
	t_hit	hit_max;
	t_hit	hit;

	init_hit(&hit);
	init_hit(&hit_max);
	if (disk_hit(cone, r, &hit_size) == 1)
		return (hit_size);
	sort_distance(t);
	hit.t = t[0];
	hit_max.t = t[1];
	t[1] = find_cone_limit(r, cone, i, &hit_max);
	hit.nml_max = hit_max.nml;
	t[0] = find_cone_limit(r, cone, i, &hit);
	hit_max.nml_max = hit.nml;
	if (t[0] > PRECISION)
		return (cone_first_try(cone, &hit_size, &hit, t));
	else
	{
		hit = hit_max;
		if (t[1] > PRECISION)
			return (cone_second_try(cone, &hit_size, &hit, t));
	}
	return (cone_third_try(cone, &hit_size, &hit));
}

void					is_cone_hit(t_ray *ray, t_cone *cone, t_hit *hit)
{
	t_intern	intern;
	double		t[2];
	double		angle;

	angle = atan(cone->r / cone->len);
	create_cone_intern_struct(ray, cone, &intern);
	if (find_cone_det(intern, angle, t) >= 0)
	{
		*hit = cone_hit(cone, ray, intern, t);
		if (cone->is_closed == 0 && dot_product(ray->dir, hit->nml) > 0 &&
			cone->opacity == 1)
			hit->nml = scalar_product(hit->nml, -1);
		complete_cone_hit(hit, cone);
	}
}
