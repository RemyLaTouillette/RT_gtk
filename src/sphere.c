/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere->c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlepeche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/07 05:03:04 by tlepeche          #+#    #+#             */
/*   Updated: 2016/09/10 17:33:02 by tlepeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

void	complete_sphere(t_hit *hit, t_sphere *sphere, t_ray *ray)
{
	hit->type = SPHERE;
	hit->radius = sphere->radius;
	hit->length = 0;
	hit->dir = init_vector(0, 0, 0);
	hit->color = sphere->color;
	hit->point_norm = vec_add(ray->pos, scalar_product(ray->dir, hit->t));
	hit->point_norm = normalize(vec_sub(sphere->center, hit->point_norm));
	hit->point_norm_max = scalar_product(ray->dir, hit->t_max);
	hit->point_norm_max = vec_add(ray->pos, hit->point_norm_max);
	hit->point_norm_max = vec_sub(sphere->center, hit->point_norm_max);
	hit->point_norm_max = normalize(hit->point_norm_max);
	hit->specular = sphere->specular;
	hit->reflection = sphere->reflection;
	hit->opacity = sphere->opacity;
	hit->ref_index = sphere->ref_index;
	hit->is_negativ = sphere->is_negativ;
	hit->texture = sphere->texture;
}

double	find_sphere_det(t_ray *ray, t_sphere *sphere, double *a, double *b)
{
	double	c;
	t_vec	tmp;

	*a = dot_product(ray->dir, ray->dir);
	tmp = vec_sub(sphere->center, ray->pos);
	*b = 2.0 * dot_product(ray->dir, tmp);
	c = dot_product(tmp, tmp) - pow(sphere->radius, 2);
	return ((*b) * (*b) - 4 * (*a) * c);
}

void	find_sphere_closest_hit(double a, double b, double det, t_hit *hit)
{
	double t1;
	double t2;

	t1 = (-b + sqrt(det)) / (2 * a);
	t2 = (-b - sqrt(det)) / (2 * a);
	if (t1 <= (double)(1.0 / PRECISION) && t2 <= (double)(1.0 / PRECISION))
	{
		hit->t = -1.0;
		hit->t_max = -1.0;
	}
	if (t1 < (double)(1.0 / PRECISION))
	{
		hit->t = t2;
		hit->t_max = t2;
	}
	else if (t2 < (double)(1.0 / PRECISION))
	{
		hit->t = t1;
		hit->t_max = t1;
	}
	else
	{
		hit->t = t1 < t2 ? t1 : t2;
		hit->t_max = t1 < t2 ? t2 : t1;
	}
}

t_hit	is_sphere_hit(t_ray *ray, t_sphere *sphere)
{
	t_hit	hit;
	double	det;
	double	a;
	double	b;

	hit.bool = 0;
	hit.color = init_color(0, 0, 0);
	if (sphere->radius > 0.0)
	{
		det = find_sphere_det(ray, sphere, &a, &b);
		if (det == 0)
		{
			hit.t = (-b / (2 * a));
			hit.t_max = (-b / (2 * a));
			hit.bool = hit.t > 0.0 ? 1 : 0;
		}
		else if (det > 0)
		{
			find_sphere_closest_hit(a, b, det, &hit);
			hit.bool = hit.t > 0.0 ? 1 : 0;
		}
		complete_sphere(&hit, sphere, ray);
	}
	return (hit);
}
