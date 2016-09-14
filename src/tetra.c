/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tetra.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlepeche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/11 18:08:12 by tlepeche          #+#    #+#             */
/*   Updated: 2016/09/14 16:12:44 by tlepeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

void	complete_tri_coord(t_triangle *tri, t_vec v0, t_vec v1, t_vec v2)
{
	tri->v0 = v0;
	tri->v1 = v1;
	tri->v2 = v2;
}

void	switch_dist(t_hit *hit)
{
	t_vec	tmp_vec;
	double	tmp;

	hit->point_norm = normalize(hit->point_norm);
	hit->point_norm_max = normalize(hit->point_norm_max);
	if (hit->t > hit->t_max)
	{
		tmp = hit->t;
		hit->t = hit->t_max;
		hit->t_max = tmp;
		tmp_vec = hit->point_norm;
		hit->point_norm = hit->point_norm_max;
		hit->point_norm_max = tmp_vec;
	}
}

void	finish_hit(t_hit *hit, t_tetra *tetra, t_ray *ray)
{
	switch_dist(hit);
	if (hit->t_max == 0)
	{
		hit->t_max = hit->t;
		hit->point_norm_max = hit->point_norm;
	}
	if (dot_product(ray->dir, hit->point_norm) > 0)
		hit->point_norm = scalar_product(hit->point_norm, -1);
	if (dot_product(ray->dir, hit->point_norm) < 0 && tetra->opacity != 1 &&
			hit->t == hit->t_max)
	{
		hit->point_norm = scalar_product(hit->point_norm, -1);
		hit->point_norm_max = hit->point_norm;
	}
	if (dot_product(ray->dir, hit->point_norm_max) < 0)
		hit->point_norm_max = scalar_product(hit->point_norm_max, -1);
}

t_hit	find_tetra_hit(t_hit *face, t_ray *ray, t_tetra *tetra)
{
	t_hit	hit;

	hit = face[0];
	hit.t = 0.0;
	hit.t_max = 0.0;
	hit.bool = 0;
	if (face[0].bool == 1)
		get_face_hit(face[0], &hit);
	if (face[1].bool == 1)
		get_face_hit(face[1], &hit);
	if (face[2].bool == 1)
		get_face_hit(face[2], &hit);
	if (face[3].bool == 1)
		get_face_hit(face[3], &hit);
	if (hit.bool == 1)
		finish_hit(&hit, tetra, ray);
	return (hit);
}

t_hit	is_tetra_hit(t_ray *ray, t_tetra *tetra)
{
	t_hit		hit;
	t_hit		*face;
	t_triangle	tri;

	if (!(face = (t_hit *)malloc(sizeof(t_hit) * (4))))
		return (init_hit());
	complete_triangle(&tri, tetra);
	complete_tri_coord(&tri, tetra->v0, tetra->v1, tetra->v2);
	face[0] = is_trian_hit(ray, &tri);
	complete_tri_coord(&tri, tetra->v0, tetra->v1, tetra->v3);
	face[1] = is_trian_hit(ray, &tri);
	complete_tri_coord(&tri, tetra->v0, tetra->v3, tetra->v2);
	face[2] = is_trian_hit(ray, &tri);
	complete_tri_coord(&tri, tetra->v1, tetra->v2, tetra->v3);
	face[3] = is_trian_hit(ray, &tri);
	hit = find_tetra_hit(face, ray, tetra);
	complete_tetra_hit(tetra, &hit);
	free(face);
	return (hit);
}
