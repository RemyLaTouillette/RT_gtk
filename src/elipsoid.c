/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elipsoid.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlepeche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/06 03:52:42 by tlepeche          #+#    #+#             */
/*   Updated: 2016/09/20 17:34:25 by tlepeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

static inline void		complete_elips(t_hit *hit, t_elips *elips)
{
	hit->type = ELIPS;
	hit->radius = elips->radius;
	hit->length = 0;
	hit->dir = init_vector(0, 0, 0);
	hit->color = elips->color;
	hit->specular = elips->specular;
	hit->reflection = elips->reflection;
	hit->opacity = elips->opacity;
	hit->ref_index = elips->ref_index;
	hit->is_negativ = elips->is_negativ;
	hit->texture = elips->texture;
}

static inline void		find_normal(t_ray *ray, t_elips *elips, t_hit *hit)
{
	hit->nml = vec_add(ray->pos, scalar_product(ray->dir, hit->t));
	hit->nml = vec_sub(elips->center, hit->nml);
	hit->nml.x *= 2.0 * (elips->quad.a * elips->quad.a);
	hit->nml.y *= 2.0 * (elips->quad.b * elips->quad.b);
	hit->nml.z *= 2.0 * (elips->quad.c * elips->quad.c);
	hit->nml = normalize(hit->nml);
	hit->nml_max = scalar_product(ray->dir, hit->t_max);
	hit->nml_max = vec_add(ray->pos, hit->nml_max);
	hit->nml_max = vec_sub(elips->center, hit->nml_max);
	hit->nml_max.x *= 2.0 * (elips->quad.a * elips->quad.a);
	hit->nml_max.y *= 2.0 * (elips->quad.b * elips->quad.b);
	hit->nml_max.z *= 2.0 * (elips->quad.c * elips->quad.c);
	hit->nml_max = normalize(hit->nml_max);
}

static inline double	elips_det(t_ray *r, t_elips *e, double *a, double *b)
{
	double	c;
	t_vec	tmp;

	*a = r->dir.x * r->dir.x * e->quad.a * e->quad.a;
	*a += r->dir.y * r->dir.y * e->quad.b * e->quad.b;
	*a += r->dir.z * r->dir.z * e->quad.c * e->quad.c;
	tmp = vec_sub(e->center, r->pos);
	*b = tmp.x * r->dir.x * e->quad.a * e->quad.a;
	*b += tmp.y * r->dir.y * e->quad.b * e->quad.b;
	*b += tmp.z * r->dir.z * e->quad.c * e->quad.c;
	*b *= 2.0;
	c = tmp.x * tmp.x * e->quad.a * e->quad.a;
	c += tmp.y * tmp.y * e->quad.b * e->quad.b;
	c += tmp.z * tmp.z * e->quad.c * e->quad.c;
	c -= e->radius * e->radius;
	return ((*b) * (*b) - (4 * (*a) * c));
}

static inline void		elips_hit(double a, double b, double det, t_hit *hit)
{
	double t1;
	double t2;

	t1 = (-b + sqrt(det)) / (2 * a);
	t2 = (-b - sqrt(det)) / (2 * a);
	if (t1 <= PRECISION && t2 <= PRECISION)
	{
		hit->t = 0.0;
		hit->t_max = 0.0;
	}
	if (t1 <= PRECISION)
	{
		hit->t = t2;
		hit->t_max = t2;
	}
	else if (t2 <= PRECISION)
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

void					is_elips_hit(t_ray *ray, t_elips *elips, t_hit *hit)
{
	double	det;
	double	a;
	double	b;

	if (elips->radius > 0.0)
	{
		det = elips_det(ray, elips, &a, &b);
		if (det == 0)
		{
			hit->t = (-b / (2 * a));
			hit->t_max = (-b / (2 * a));
			hit->bool = hit->t > 0.0 ? 1 : 0;
		}
		else if (det > 0)
		{
			elips_hit(a, b, det, hit);
			hit->bool = hit->t > 0.0 ? 1 : 0;
		}
		find_normal(ray, elips, hit);
		complete_elips(hit, elips);
	}
}
