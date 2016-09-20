/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhenne <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/16 08:42:55 by bhenne            #+#    #+#             */
/*   Updated: 2016/09/20 17:23:20 by tlepeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

static inline void	tri_hit(t_triangle *tri, t_hit *hit, t_vec *tmp, double det)
{
	t_vec	normal;

	normal = cross_product(tmp[0], tmp[1]);
	hit->bool = 1;
	hit->type = TRIAN;
	hit->t = (dot_product(tmp[1], tmp[2]) / det);
	hit->t_max = hit->t;
	hit->color = tri->color;
	hit->nml = normal;
	hit->reflection = tri->reflection;
	hit->specular = tri->specular;
	hit->opacity = tri->opacity;
	hit->ref_index = tri->ref_index;
	hit->is_negativ = tri->is_negativ;
	hit->texture = tri->texture;
}

static inline void	tri_tmp(t_triangle *triangle, t_ray *ray, t_vec *tmp)
{
	tmp[0] = vec_sub(triangle->v0, triangle->v1);
	tmp[1] = vec_sub(triangle->v0, triangle->v2);
	tmp[2] = cross_product(ray->dir, tmp[1]);
	tmp[3] = vec_sub(triangle->v0, ray->pos);
}

void				is_trian_hit(t_ray *ray, t_triangle *triangle, t_hit *hit)
{
	t_vec	tmp[4];
	double	det;
	double	u;
	double	v;

	tri_tmp(triangle, ray, tmp);
	det = dot_product(tmp[0], tmp[2]);
	u = dot_product(tmp[3], tmp[2]) / det;
	tmp[2] = cross_product(tmp[3], tmp[0]);
	v = dot_product(ray->dir, tmp[2]) / det;
	if ((dot_product(tmp[1], tmp[2]) / det) > PRECISION)
	{
		if (!((det > -PRECISION &&
			det < PRECISION) || u < 0 || u > 1 || v < 0 ||
			u + v > 1))
			tri_hit(triangle, hit, tmp, det);
	}
	hit->nml = normalize(hit->nml);
}
