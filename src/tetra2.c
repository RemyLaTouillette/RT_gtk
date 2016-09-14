/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tetra.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlepeche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/11 18:08:12 by tlepeche          #+#    #+#             */
/*   Updated: 2016/09/14 16:13:01 by tlepeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

void	complete_tetra_hit(t_tetra *tetra, t_hit *hit)
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

void	complete_triangle(t_triangle *tri, t_tetra *tetra)
{
	tri->color = tetra->color;
	tri->reflection = tetra->reflection;
	tri->specular = tetra->specular;
	tri->opacity = tetra->opacity;
	tri->ref_index = tetra->ref_index;
	tri->is_negativ = tetra->is_negativ;
	tri->texture = tetra->texture;
}

void	get_face_hit(t_hit face, t_hit *hit)
{
	hit->bool = 1;
	if (hit->t == 0.0)
	{
		hit->t = face.t;
		hit->point_norm = face.point_norm;
	}
	else
	{
		hit->t_max = face.t;
		hit->point_norm_max = face.point_norm;
	}
}
