/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_invalid.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/10 20:17:52 by nbelouni          #+#    #+#             */
/*   Updated: 2016/09/11 17:02:05 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

int		cyl_invalid(t_cylinder *cyl, t_vec **v, t_color *c)
{
	if (!v[0] || !c || !v[1])
	{
		if (!v[0])
			ft_putendl("'pos' missing\n");
		if (!c)
			ft_putendl("'color' missing\n");
		if (!v[1])
			ft_putendl("'dir' missing\n");
		return (1);
	}
	cyl->pos = *v[0];
	cyl->dir = *v[1];
	cyl->color = *c;
	if (cyl->is_closed == 0 && cyl->ref_index != 1)
	{
		ft_putendl("'cylinder' : empty object cannot refract\n");
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
			ft_putendl("'pos' missing\n");
		if (!c)
			ft_putendl("'color' missing\n");
		if (!v[1])
			ft_putendl("'dir' missing\n");
		return (1);
	}
	cyl->pos = *v[0];
	cyl->dir = *v[1];
	cyl->color = *c;
	if (cyl->is_closed == 0 && cyl->ref_index != 1)
	{
		ft_putendl("'cone' : empty object cannot refract\n");
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
			ft_putendl("'vec' missing\n");
		if (!tool->color)
			ft_putendl("'color' missing\n");
		if (!tool->quad)
			ft_putendl("'quad' missing\n");
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
			ft_putendl("'v0' missing");
		if (!v[1])
			ft_putendl("'v1' missing");
		if (!v[2])
			ft_putendl("'v2' missing");
		if (!color)
			ft_putendl("'color' missing");
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
