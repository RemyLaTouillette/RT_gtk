/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects_cmp2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlepeche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/16 15:05:39 by tlepeche          #+#    #+#             */
/*   Updated: 2016/09/16 15:23:14 by tlepeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

int	sphere_cmp(t_sphere *new, t_sphere *old)
{
	if (new->radius == old->radius &&
		vec_cmp(new->center, old->center) == 1 &&
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

int	cylinder_cmp(t_cylinder *new, t_cylinder *old)
{
	t_vec tmp_dir1;
	t_vec tmp_dir2;

	tmp_dir1 = normalize(new->dir);
	tmp_dir2 = normalize(old->dir);
	if (new->radius == old->radius &&
		vec_cmp(new->pos, old->pos) == 1 &&
		vec_cmp(tmp_dir1, tmp_dir2) == 1 &&
		new->length == old->length &&
		color_cmp(new->color, old->color) == 1 &&
		new->specular == old->specular &&
		new->reflection == old->reflection &&
		new->opacity == old->opacity &&
		new->ref_index == old->ref_index &&
		new->is_negativ == old->is_negativ &&
		new->texture == old->texture &&
		new->is_closed == old->is_closed)
		return (1);
	return (0);
}

int	cone_cmp(t_cone *new, t_cone *old)
{
	t_vec tmp_dir1;
	t_vec tmp_dir2;

	tmp_dir1 = normalize(new->dir);
	tmp_dir2 = normalize(old->dir);
	if (new->r == old->r &&
		vec_cmp(new->pos, old->pos) == 1 &&
		vec_cmp(tmp_dir1, tmp_dir2) == 1 &&
		new->len == old->len &&
		color_cmp(new->color, old->color) == 1 &&
		new->specular == old->specular &&
		new->reflection == old->reflection &&
		new->opacity == old->opacity &&
		new->ref_index == old->ref_index &&
		new->is_negativ == old->is_negativ &&
		new->texture == old->texture &&
		new->is_closed == old->is_closed)
		return (1);
	return (0);
}

int	elips_cmp(t_elips *new, t_elips *old)
{
	if (new->radius == old->radius &&
		vec_cmp(new->center, old->center) == 1 &&
		quad_cmp(new->quad, old->quad) == 1 &&
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

int	plane_cmp(t_plane *new, t_plane *old)
{
	t_vec tmp_dir1;
	t_vec tmp_dir2;

	tmp_dir1 = normalize(new->normal);
	tmp_dir2 = normalize(old->normal);
	if (vec_cmp(new->pos, old->pos) == 1 &&
		vec_cmp(tmp_dir1, tmp_dir2) == 1 &&
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
