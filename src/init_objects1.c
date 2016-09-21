/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_objects1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/15 14:18:45 by nbelouni          #+#    #+#             */
/*   Updated: 2016/09/21 14:47:43 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

t_sphere	*init_sphere(void)
{
	t_sphere	*sphere;

	if (!(sphere = (t_sphere *)malloc(sizeof(t_sphere))))
		return (NULL);
	sphere->radius = 0;
	sphere->center = init_vector(0, 0, 0);
	init_color(&(sphere->color), 0, 0, 0);
	sphere->specular = 0;
	sphere->reflection = 0;
	sphere->opacity = 1;
	sphere->ref_index = 1;
	sphere->is_negativ = 0;
	sphere->texture = NONE;
	return (sphere);
}

t_plane		*init_plane(void)
{
	t_plane	*plane;

	if (!(plane = (t_plane *)malloc(sizeof(t_plane))))
		return (NULL);
	plane->pos = init_vector(0, 0, 0);
	plane->normal = init_vector(0, 0, 0);
	init_color(&(plane->color), 0, 0, 0);
	plane->specular = 0;
	plane->reflection = 0;
	plane->opacity = 1;
	plane->ref_index = 1;
	plane->is_negativ = 0;
	plane->texture = NONE;
	return (plane);
}

t_cylinder	*init_cylinder(void)
{
	t_cylinder	*cylinder;

	if (!(cylinder = (t_cylinder *)malloc(sizeof(t_cylinder))))
		return (NULL);
	cylinder->radius = 0;
	cylinder->pos = init_vector(0, 0, 0);
	cylinder->dir = init_vector(0, 0, 0);
	init_color(&(cylinder->color), 0, 0, 0);
	cylinder->length = 0;
	cylinder->specular = 0;
	cylinder->reflection = 0;
	cylinder->opacity = 1;
	cylinder->ref_index = 1;
	cylinder->is_negativ = 0;
	cylinder->texture = NONE;
	cylinder->is_closed = 0;
	return (cylinder);
}

t_cone		*init_cone(void)
{
	t_cone	*cone;

	if (!(cone = (t_cone *)malloc(sizeof(t_cone))))
		return (NULL);
	cone->r = 0;
	cone->pos = init_vector(0, 0, 0);
	cone->dir = init_vector(0, 0, 0);
	init_color(&(cone->color), 0, 0, 0);
	cone->len = 0;
	cone->specular = 0;
	cone->reflection = 0;
	cone->opacity = 1;
	cone->ref_index = 1;
	cone->is_negativ = 0;
	cone->texture = NONE;
	cone->is_closed = 0;
	return (cone);
}

t_parallelo	*init_para(void)
{
	t_parallelo	*para;

	if (!(para = (t_parallelo *)malloc(sizeof(t_parallelo))))
		return (NULL);
	para->v0 = init_vector(0, 0, 0);
	para->v1 = init_vector(0, 0, 0);
	para->v2 = init_vector(0, 0, 0);
	init_color(&(para->color), 0, 0, 0);
	para->specular = 0;
	para->reflection = 0;
	para->opacity = 1;
	para->ref_index = 1;
	para->texture = NONE;
	para->is_negativ = 0;
	return (para);
}
