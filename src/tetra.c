/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tetra.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlepeche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/11 18:08:12 by tlepeche          #+#    #+#             */
/*   Updated: 2016/09/21 16:07:54 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

static inline void	tri_coord(t_triangle *tri, t_vec v0, t_vec v1, t_vec v2)
{
	tri->v0 = v0;
	tri->v1 = v1;
	tri->v2 = v2;
}

static inline void	switch_dist(t_hit *hit)
{
	t_vec	tmp_vec;
	double	tmp;

	hit->nml = normalize(hit->nml);
	hit->nml_max = normalize(hit->nml_max);
	if (hit->t > hit->t_max)
	{
		tmp = hit->t;
		hit->t = hit->t_max;
		hit->t_max = tmp;
		tmp_vec = hit->nml;
		hit->nml = hit->nml_max;
		hit->nml_max = tmp_vec;
	}
}

static inline void	finish_hit(t_hit *hit, t_tetra *tetra, t_ray *ray)
{
	switch_dist(hit);
	if (hit->t_max == 0)
	{
		hit->t_max = hit->t;
		hit->nml_max = hit->nml;
	}
	if (dot_product(ray->dir, hit->nml) > 0)
		hit->nml = scalar_product(hit->nml, -1);
	if (dot_product(ray->dir, hit->nml) < 0 && tetra->opacity != 1 &&
			hit->t == hit->t_max)
	{
		hit->nml = scalar_product(hit->nml, -1);
		hit->nml_max = hit->nml;
	}
	if (dot_product(ray->dir, hit->nml_max) < 0)
		hit->nml_max = scalar_product(hit->nml_max, -1);
}

static inline void	find_hit(t_hit *f, t_ray *ray, t_tetra *tetra, t_hit *hit)
{
	*hit = f[0];
	hit->t = 0.0;
	hit->t_max = 0.0;
	hit->bool = 0;
	if (f[0].bool == 1)
		get_face_hit(&f[0], hit);
	if (f[1].bool == 1)
		get_face_hit(&f[1], hit);
	if (f[2].bool == 1)
		get_face_hit(&f[2], hit);
	if (f[3].bool == 1)
		get_face_hit(&f[3], hit);
	if (hit->bool == 1)
		finish_hit(hit, tetra, ray);
}

void				is_tetra_hit(t_ray *ray, t_tetra *tetra, t_hit *hit)
{
	t_hit		face[4];
	t_triangle	tri;

	triangle(&tri, tetra);
	tri_coord(&tri, tetra->v0, tetra->v1, tetra->v2);
	is_trian_hit(ray, &tri, &face[0]);
	tri_coord(&tri, tetra->v0, tetra->v1, tetra->v3);
	is_trian_hit(ray, &tri, &face[1]);
	tri_coord(&tri, tetra->v0, tetra->v3, tetra->v2);
	is_trian_hit(ray, &tri, &face[2]);
	tri_coord(&tri, tetra->v1, tetra->v2, tetra->v3);
	is_trian_hit(ray, &tri, &face[3]);
	find_hit(face, ray, tetra, hit);
	tetra_hit(tetra, hit);
}
