/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects_cmp3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlepeche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/16 15:05:33 by tlepeche          #+#    #+#             */
/*   Updated: 2016/09/16 15:23:36 by tlepeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

int	triangle_cmp(t_triangle *new, t_triangle *old)
{
	if (vec_cmp(new->v0, old->v0) == 1 &&
		vec_cmp(new->v1, old->v1) == 1 &&
		vec_cmp(new->v2, old->v2) == 1 &&
		color_cmp(new->color, old->color) == 1 &&
		new->specular == old->specular &&
		new->reflection == old->reflection &&
		new->opacity == old->opacity &&
		new->ref_index == old->ref_index &&
		new->is_negativ == old->is_negativ &&
		new->texture == old->texture)
		return (1);
	return (0);
}

int	para_cmp(t_parallelo *new, t_parallelo *old)
{
	if (vec_cmp(new->v0, old->v0) == 1 &&
		vec_cmp(new->v1, old->v1) == 1 &&
		vec_cmp(new->v2, old->v2) == 1 &&
		color_cmp(new->color, old->color) == 1 &&
		new->specular == old->specular &&
		new->reflection == old->reflection &&
		new->opacity == old->opacity &&
		new->ref_index == old->ref_index &&
		new->is_negativ == old->is_negativ &&
		new->texture == old->texture)
		return (1);
	return (0);
}

int	tetra_cmp(t_tetra *new, t_tetra *old)
{
	if (vec_cmp(new->v0, old->v0) == 1 &&
		vec_cmp(new->v1, old->v1) == 1 &&
		vec_cmp(new->v2, old->v2) == 1 &&
		vec_cmp(new->v3, old->v3) == 1 &&
		color_cmp(new->color, old->color) == 1 &&
		new->specular == old->specular &&
		new->reflection == old->reflection &&
		new->opacity == old->opacity &&
		new->ref_index == old->ref_index &&
		new->is_negativ == old->is_negativ &&
		new->texture == old->texture)
		return (1);
	return (0);
}
