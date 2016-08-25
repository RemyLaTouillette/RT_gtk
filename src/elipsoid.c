/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elipsoid.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlepeche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/06 03:52:42 by tlepeche          #+#    #+#             */
/*   Updated: 2016/08/25 16:21:04 by tlepeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

void	complete_elips(t_hit *hit, t_elips *elips)
{
	hit->type = ELIPS;
	hit->radius = elips->radius;
	hit->length = 0;
//	hit->pos = elips->center;
	hit->dir = init_vector(0, 0, 0);
	hit->color = elips->color;
	hit->specular = elips->specular;
	hit->reflection = elips->reflection;
	hit->opacity = elips->opacity;
	hit->ref_index = elips->ref_index;
	hit->is_negativ = elips->is_negativ;
	hit->texture = elips->texture;
}

void	find_normal(t_ray *ray, t_elips *elips, t_hit *hit)
{
	hit->point_norm = vec_add(ray->pos, scalar_product(ray->dir, hit->t));
	hit->point_norm = vec_sub(elips->center, hit->point_norm);
	hit->point_norm.x *= 2.0 * (elips->quad.a * elips->quad.a);
	hit->point_norm.y *= 2.0 * (elips->quad.b * elips->quad.b);
	hit->point_norm.z *= 2.0 * (elips->quad.c * elips->quad.c);
	hit->point_norm = normalize(hit->point_norm);
	hit->point_norm_max = scalar_product(ray->dir, hit->t_max);
	hit->point_norm_max = vec_add(ray->pos, hit->point_norm_max);
	hit->point_norm_max = vec_sub(elips->center, hit->point_norm_max);
	hit->point_norm_max.x *= 2.0 * (elips->quad.a * elips->quad.a);
	hit->point_norm_max.y *= 2.0 * (elips->quad.b * elips->quad.b);
	hit->point_norm_max.z *= 2.0 * (elips->quad.c * elips->quad.c);
	hit->point_norm_max = normalize(hit->point_norm_max);
}

double	find_elips_det(t_ray *ray, t_elips *elips, double *a, double *b)
{
	double	c;
	t_vec	tmp;

	*a = pow(ray->dir.x, 2) * pow(elips->quad.a, 2);
	*a += pow(ray->dir.y, 2) * pow(elips->quad.b, 2);
	*a += pow(ray->dir.z, 2) * pow(elips->quad.c, 2);
	tmp = vec_sub(elips->center, ray->pos);
	*b = tmp.x * ray->dir.x * pow(elips->quad.a, 2);
	*b += tmp.y * ray->dir.y * pow(elips->quad.b, 2);
	*b += tmp.z * ray->dir.z * pow(elips->quad.c, 2);
	*b *= 2.0;
	c = tmp.x * tmp.x * pow(elips->quad.a, 2);
	c += tmp.y * tmp.y * pow(elips->quad.b, 2);
	c += tmp.z * tmp.z * pow(elips->quad.c, 2);
	c -= pow(elips->radius, 2);
	return (pow(*b, 2) - (4 * (*a) * c));
}

void	find_elips_closest_hit(double a, double b, double det, t_hit *hit)
{
	double t1;
	double t2;

	t1 = (-b + sqrt(det)) / (2 * a);
	t2 = (-b - sqrt(det)) / (2 * a);
	if (t1 <= (double)(1.0 / PRECISION) && t2 <= (double)(1.0 / PRECISION))
	{
		hit->t = 0.0;
		hit->t_max = 0.0;
	}
	if (t1 <= (double)(1.0 / PRECISION))
	{
		hit->t = t2;
		hit->t_max = t2;
	}
	else if (t2 <= (double)(1.0 / PRECISION))
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

t_hit	is_elips_hit(t_ray *ray, t_elips *elips)
{
	t_hit	hit;
	double	det;
	double	a;
	double	b;

	hit.bool = 0;
	hit.color = init_color(0, 0, 0);
	if (elips->radius > 0.0)
	{
		det = find_elips_det(ray, elips, &a, &b);
		if (det == 0)
		{
			hit.t = (-b / (2 * a));
			hit.t_max = (-b / (2 * a));
			hit.bool = hit.t > 0.0 ? 1 : 0;
		}
		else if (det > 0)
		{
			find_elips_closest_hit(a, b, det, &hit);
			hit.bool = hit.t > 0.0 ? 1 : 0;
		}
		find_normal(ray, elips, &hit);
		complete_elips(&hit, elips);
	}
	return (hit);
}
