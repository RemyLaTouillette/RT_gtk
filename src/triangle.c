/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhenne <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/16 08:42:55 by bhenne            #+#    #+#             */
/*   Updated: 2016/09/29 19:01:50 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

static inline double	is_edge(t_vec v1, t_vec v2, t_ray *ray, t_hit *hit)
{
	t_vec	v_dist;
	t_vec	h;
	double	dot;
	double	angle;
	double	new_len;

	v_dist = vec_sub(v2, v1);
	h = vec_sub(v1, vec_add(ray->pos, scalar_product(ray->dir, hit->t)));
	dot = dot_product(h, v_dist) / (get_length(h) * get_length(v_dist));
	angle = acos(dot);
	new_len = get_length(h) * sin(angle);
	return (new_len);
}

static inline void		find_edge(t_triangle *t, t_ray *ray, t_hit *hit)
{
	double	t1;
	double	t2;
	double	t3;
	double	t_min;

	t1 = get_length(vec_sub(t->v0, t->v1));
	t2 = get_length(vec_sub(t->v0, t->v2));
	t3 = get_length(vec_sub(t->v1, t->v2));
	if (t1 < t2 && t1 < t3)
		t_min = t1 * 0.01;
	else if (t2 < t3)
		t_min = t2 * 0.01;
	else
		t_min = t3 * 0.01;
	hit->dist_from_center = 0.0;
	if (is_edge(t->v0, t->v1, ray, hit) < t_min)
		hit->dist_from_center = 1.0;
	if (is_edge(t->v1, t->v2, ray, hit) < t_min)
		hit->dist_from_center = 1.0;
	if (is_edge(t->v2, t->v0, ray, hit) < t_min)
		hit->dist_from_center = 1.0;
}

static inline void		tri_hit(t_triangle *t, t_hit *h, t_vec *tmp, double det)
{
	t_vec	normal;

	normal = cross_product(tmp[0], tmp[1]);
	h->bool = 1;
	h->type = TRIAN;
	h->t = (dot_product(tmp[1], tmp[2]) / det);
	h->t_max = h->t;
	h->color = t->color;
	h->nml = normal;
	h->reflection = t->reflection;
	h->specular = t->specular;
	h->opacity = t->opacity;
	h->ref_index = t->ref_index;
	h->is_negativ = t->is_negativ;
	h->texture = t->texture;
}

static inline void		tri_tmp(t_triangle *triangle, t_ray *ray, t_vec *tmp)
{
	tmp[0] = vec_sub(triangle->v0, triangle->v1);
	tmp[1] = vec_sub(triangle->v0, triangle->v2);
	tmp[2] = cross_product(ray->dir, tmp[1]);
	tmp[3] = vec_sub(triangle->v0, ray->pos);
}

void					is_trian_hit(t_ray *ray, t_triangle *tri, t_hit *hit)
{
	t_vec	tmp[4];
	double	det;
	double	u;
	double	v;

	tri_tmp(tri, ray, tmp);
	det = dot_product(tmp[0], tmp[2]);
	u = dot_product(tmp[3], tmp[2]) / det;
	tmp[2] = cross_product(tmp[3], tmp[0]);
	v = dot_product(ray->dir, tmp[2]) / det;
	if ((dot_product(tmp[1], tmp[2]) / det) > PRECISION)
	{
		if (!((det > -PRECISION &&
			det < PRECISION) || u < PRECISION || u > 1.0 + PRECISION ||
			v < PRECISION || u + v > 1.0 + PRECISION))
		{
			tri_hit(tri, hit, tmp, det);
			find_edge(tri, ray, hit);
		}
		else
			hit->dist_from_center = 0.0;
	}
	hit->nml = normalize(hit->nml);
}
