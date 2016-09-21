/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_objects2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/15 14:19:35 by nbelouni          #+#    #+#             */
/*   Updated: 2016/09/21 14:39:37 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

t_triangle	*init_triangle(void)
{
	t_triangle	*triangle;

	if (!(triangle = (t_triangle *)malloc(sizeof(t_triangle))))
		return (NULL);
	triangle->v0 = init_vector(0, 0, 0);
	triangle->v1 = init_vector(0, 0, 0);
	triangle->v2 = init_vector(0, 0, 0);
	init_color(&(triangle->color), 0, 0, 0);
	triangle->specular = 0;
	triangle->reflection = 0;
	triangle->opacity = 1;
	triangle->ref_index = 1;
	triangle->texture = NONE;
	triangle->is_negativ = 0;
	return (triangle);
}

t_tetra		*init_tetra(void)
{
	t_tetra *tetra;

	if (!(tetra = (t_tetra *)malloc(sizeof(t_tetra))))
		return (NULL);
	tetra->v0 = init_vector(0, 0, 0);
	tetra->v1 = init_vector(0, 0, 0);
	tetra->v2 = init_vector(0, 0, 0);
	tetra->v3 = init_vector(0, 0, 0);
	init_color(&(tetra->color), 0, 0, 0);
	tetra->specular = 0;
	tetra->reflection = 0;
	tetra->opacity = 1;
	tetra->ref_index = 1;
	tetra->texture = NONE;
	tetra->is_negativ = 0;
	return (tetra);
}

t_elips		*init_elips(void)
{
	t_elips	*elips;

	if (!(elips = (t_elips *)malloc(sizeof(t_elips))))
		return (NULL);
	elips->radius = 0;
	elips->center = init_vector(0, 0, 0);
	elips->quad.a = 0;
	elips->quad.b = 0;
	elips->quad.c = 0;
	init_color(&(elips->color), 0, 0, 0);
	elips->specular = 0;
	elips->reflection = 0;
	elips->opacity = 1;
	elips->ref_index = 1;
	elips->is_negativ = 0;
	elips->texture = NONE;
	return (elips);
}
