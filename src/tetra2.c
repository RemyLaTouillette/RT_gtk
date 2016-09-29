/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tetra.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlepeche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/11 18:08:12 by tlepeche          #+#    #+#             */
/*   Updated: 2016/09/29 18:59:00 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

void	tetra_hit(t_tetra *tetra, t_hit *hit)
{
	hit->type = TETRA;
	hit->color = tetra->color;
	hit->reflection = tetra->reflection;
	hit->specular = tetra->specular;
	hit->opacity = tetra->opacity;
	hit->ref_index = tetra->ref_index;
	hit->is_negativ = tetra->is_negativ;
	hit->texture = tetra->texture;
}

void	triangle(t_triangle *tri, t_tetra *tetra)
{
	tri->color = tetra->color;
	tri->reflection = tetra->reflection;
	tri->specular = tetra->specular;
	tri->opacity = tetra->opacity;
	tri->ref_index = tetra->ref_index;
	tri->is_negativ = tetra->is_negativ;
	tri->texture = tetra->texture;
}

void	ajust_point(t_vec *v1, t_vec *v2, t_vec *v3, double n)
{
	v1->x += n;
	v1->x += n;
	v1->y += n;
	v2->z += n;
	v2->x += n;
	v2->y += n;
	v3->z += n;
	v3->y += n;
	v3->z += n;
}

void	get_face_hit(t_hit *face, t_hit *hit)
{
	hit->bool = 1;
	if (hit->t == 0.0)
	{
		hit->t = face->t;
		hit->nml = face->nml;
		hit->dist_from_center = face->dist_from_center;
	}
	else if (hit->t_max == 0.0)
	{
		hit->t_max = face->t;
		hit->nml_max = face->nml;
		hit->radius = face->dist_from_center;
	}
}
