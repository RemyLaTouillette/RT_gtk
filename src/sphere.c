/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere->c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlepeche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/07 05:03:04 by tlepeche          #+#    #+#             */
/*   Updated: 2016/09/20 14:12:37 by tlepeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

static inline void		complete_sphere(t_hit *hit, t_sphere *s, t_ray *ray)
{
	hit->type = SPHERE;
	hit->radius = s->radius;
	hit->length = 0;
	hit->dir = init_vector(0, 0, 0);
	hit->color = s->color;
	hit->nml = vec_add(ray->pos, scalar_product(ray->dir, hit->t));
	hit->nml = normalize(vec_sub(s->center, hit->nml));
	hit->nml_max = scalar_product(ray->dir, hit->t_max);
	hit->nml_max = vec_add(ray->pos, hit->nml_max);
	hit->nml_max = vec_sub(s->center, hit->nml_max);
	hit->nml_max = normalize(hit->nml_max);
	hit->specular = s->specular;
	hit->reflection = s->reflection;
	hit->opacity = s->opacity;
	hit->ref_index = s->ref_index;
	hit->is_negativ = s->is_negativ;
	hit->texture = s->texture;
}

static inline double	sphere_det(t_ray *r, t_sphere *s, double *a, double *b)
{
	double	c;
	t_vec	tmp;

	*a = dot_product(r->dir, r->dir);
	tmp = vec_sub(s->center, r->pos);
	*b = 2.0 * dot_product(r->dir, tmp);
	c = dot_product(tmp, tmp) - (s->radius * s->radius);
	return ((*b) * (*b) - 4 * (*a) * c);
}

static inline void		sphere_hit(double a, double b, double det, t_hit *hit)
{
	double t1;
	double t2;

	t1 = (-b + sqrt(det)) / (2 * a);
	t2 = (-b - sqrt(det)) / (2 * a);
	if (t1 <= PRECISION && t2 <= PRECISION)
	{
		hit->t = -1.0;
		hit->t_max = -1.0;
	}
	if (t1 < PRECISION)
	{
		hit->t = t2;
		hit->t_max = t2;
	}
	else if (t2 < PRECISION)
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

t_hit					is_sphere_hit(t_ray *ray, t_sphere *sphere)
{
	t_hit	hit;
	double	det;
	double	a;
	double	b;

	hit.bool = 0;
	hit.color = init_color(0, 0, 0);
	if (sphere->radius > 0.0)
	{
		det = sphere_det(ray, sphere, &a, &b);
		if (det == 0)
		{
			hit.t = (-b / (2 * a));
			hit.t_max = (-b / (2 * a));
			hit.bool = hit.t > 0.0 ? 1 : 0;
		}
		else if (det > 0)
		{
			sphere_hit(a, b, det, &hit);
			hit.bool = hit.t > 0.0 ? 1 : 0;
		}
		complete_sphere(&hit, sphere, ray);
	}
	return (hit);
}
