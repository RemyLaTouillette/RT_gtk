/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parallelo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhenne <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/22 16:27:06 by bhenne            #+#    #+#             */
/*   Updated: 2016/09/20 17:23:35 by tlepeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

static inline void	para_hit(t_parallelo *p, t_hit *hit, t_vec *tmp, double det)
{
	t_vec normal;

	normal = normalize(cross_product(tmp[0], tmp[1]));
	hit->bool = 1;
	hit->type = PARA;
	hit->t = (dot_product(tmp[1], tmp[2]) / det);
	hit->color = p->color;
	hit->nml = scalar_product(normal, -1);
	hit->reflection = p->reflection;
	hit->specular = p->specular;
	hit->opacity = p->opacity;
	hit->ref_index = p->ref_index;
	hit->is_negativ = p->is_negativ;
	hit->texture = p->texture;
}

static inline void	para_tmp(t_parallelo *para, t_ray *ray, t_vec *tmp)
{
	tmp[0] = vec_sub(para->v0, para->v1);
	tmp[1] = vec_sub(para->v0, para->v2);
	tmp[2] = cross_product(ray->dir, tmp[1]);
	tmp[3] = vec_sub(para->v0, ray->pos);
}

void				is_parallelo_hit(t_ray *ray, t_parallelo *para, t_hit *hit)
{
	t_vec	tmp[4];
	double	det;
	double	u;
	double	v;

	para_tmp(para, ray, tmp);
	det = dot_product(tmp[0], tmp[2]);
	u = dot_product(tmp[3], tmp[2]) / det;
	tmp[2] = cross_product(tmp[3], tmp[0]);
	v = dot_product(ray->dir, tmp[2]) / det;
	if ((dot_product(tmp[1], tmp[2]) / det) > PRECISION)
	{
		if (det > -PRECISION && det < PRECISION)
			hit->bool = 0;
		else if (u < 0 || u > 1 || v < 0 || v > 1)
			hit->bool = 0;
		else
			para_hit(para, hit, tmp, det);
	}
}
