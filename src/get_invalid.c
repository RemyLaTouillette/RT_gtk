/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_invalid.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/10 20:17:52 by nbelouni          #+#    #+#             */
/*   Updated: 2016/09/22 15:05:37 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

int		cyl_invalid(t_cylinder *cyl, t_vec **v, t_color *c)
{
	if (!v[0] || !c || !v[1])
	{
		if (!v[0])
			print_error("'pos' missing\n", 1);
		if (!c)
			print_error("'color' missing\n", 1);
		if (!v[1])
			print_error("'dir' missing\n", 1);
		return (1);
	}
	cyl->pos = *v[0];
	cyl->dir = *v[1];
	cyl->color = *c;
	if (cyl->is_closed == 0 && cyl->ref_index != 1)
	{
		print_error("'cylinder' : empty object cannot refract\n", 2);
		cyl->ref_index = 1;
	}
	free(v[0]);
	free(v[1]);
	free(c);
	return (0);
}

int		cone_invalid(t_cone *cyl, t_vec **v, t_color *c)
{
	if (!v[0] || !c || !v[1])
	{
		if (!v[0])
			print_error("'pos' missing\n", 1);
		if (!c)
			print_error("'color' missing\n", 1);
		if (!v[1])
			print_error("'dir' missing\n", 1);
		return (1);
	}
	cyl->pos = *v[0];
	cyl->dir = *v[1];
	cyl->color = *c;
	if (cyl->is_closed == 0 && cyl->ref_index != 1)
	{
		print_error("'cone' : empty object cannot refract\n", 2);
		cyl->ref_index = 1;
	}
	free(v[0]);
	free(v[1]);
	free(c);
	return (0);
}

int		elips_invalid(t_elips *elips, t_e_tool *tool)
{
	if (!tool->vec || !tool->quad || !tool->color)
	{
		if (!tool->vec)
			print_error("'vec' missing\n", 1);
		if (!tool->color)
			print_error("'color' missing\n", 1);
		if (!tool->quad)
			print_error("'quad' missing\n", 1);
		return (1);
	}
	elips->center = *tool->vec;
	elips->quad = *tool->quad;
	elips->color = *tool->color;
	free(tool->vec);
	free(tool->quad);
	free(tool->color);
	return (0);
}

int		triangle_invalid(t_triangle *triangle, t_vec *v[3], t_color *color)
{
	if (!v[0] || !v[1] || !v[2] || !color)
	{
		if (!v[0])
			print_error("'v0' missing", 1);
		if (!v[1])
			print_error("'v1' missing", 1);
		if (!v[2])
			print_error("'v2' missing", 1);
		if (!color)
			print_error("'color' missing", 1);
		return (1);
	}
	triangle->v0 = *v[0];
	triangle->v1 = *v[1];
	triangle->v2 = *v[2];
	triangle->color = *color;
	free(v[0]);
	free(v[1]);
	free(v[2]);
	free(color);
	return (0);
}

int		tetra_invalid(t_tetra *tetra, t_vec **v, t_color *color)
{
	if (!v[0] || !v[1] || !v[2] || !color || !v[3])
	{
		if (!v[0])
			print_error("'v0' missing", 1);
		if (!v[1])
			print_error("'v1' missing", 1);
		if (!v[2])
			print_error("'v2' missing", 1);
		if (!v[3])
			print_error("'v3' missing", 1);
		if (!color)
			print_error("'color' missing", 1);
		return (1);
	}
	tetra->v0 = *v[0];
	tetra->v1 = *v[1];
	tetra->v2 = *v[2];
	tetra->v3 = *v[3];
	tetra->color = *color;
	free(v[0]);
	free(v[1]);
	free(v[2]);
	free(v[3]);
	free(color);
	return (0);
}
