/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sduprey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/15 00:36:12 by sduprey           #+#    #+#             */
/*   Updated: 2016/08/15 03:06:25 by sduprey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

#include <stdio.h>

t_hit	is_triangle_hit(t_ray *ray, t_triangle *tri)
{
	t_hit	hit;
	t_vec	e1;
	t_vec	e2;
	t_vec	p1;
	t_vec	p2;
	double	det;
	double	rev;
	double	v[3];


	// init hit
	hit.bool = 0;
	hit.color = tri->color;
	hit.specular = tri->specular;
	hit.ref_index = tri->ref_index;
	hit.reflection = tri->reflection;
	hit.opacity = tri->opacity;
	hit.is_negativ = tri->is_negativ;
	hit.texture = tri->texture;

//	printf("triangle ici\n");
	e1 = vec_sub(tri->dir, tri->dir2); // dir2, tri->dir
	e2 = vec_sub(tri->dir, tri->dir3); // dir3, tri->dir
	p1 = cross_product(e1, ray->dir);
	det = dot_product(e1, p1);
	if (det > -0.000001 && det < 0.000001)
		return (hit);
	rev = 1.0 / det;
	p2 = vec_sub(tri->dir, ray->pos);
	v[0] = dot_product(p1, p2) * rev;
	if (v[0] < 0 || v[0] > 1)
		return (hit);
	return (hit);
	p2 = cross_product(p2, e1);
	v[1] = dot_product(ray->dir, p2) * rev;
	if (v[1] < 0 || v[0] + v[1] > 1)
		return (hit);
	v[2] = dot_product(ray->dir, p2) * rev;
	if (v[2] > 0.000001)
	{
		hit.t = v[2];
		printf("triangle op\n\n");
		hit.bool = 1;
	}
	return (hit);
}
