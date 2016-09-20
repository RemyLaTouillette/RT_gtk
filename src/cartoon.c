/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cartoon.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/02 12:10:14 by nbelouni          #+#    #+#             */
/*   Updated: 2016/09/20 14:15:38 by tlepeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

double	define_color(double color)
{
	int		color_ref;

	color_ref = 256 * 0.25;
	if (color < color_ref)
		color = 0;
	if (color <= color_ref * 2 && color > color_ref)
		color = 256 / 3;
	if (color <= color_ref * 3 && color > color_ref * 2)
		color = 256 / 3 * 2;
	else if (color > color_ref * 3)
		color = 255;
	return (color);
}

t_color	cartoon(t_color color)
{
	color.r = define_color(color.r);
	color.g = define_color(color.g);
	color.b = define_color(color.b);
	return (color);
}

int		is_dir(t_vec v)
{
	if (v.x == 0 && v.y == 0 && v.z == 0)
		return (0);
	return (1);
}

int		is_same_dir(t_vec v, t_vec ref)
{
	if (v.x == ref.x && v.y == ref.y && v.z == ref.z)
		return (1);
	v = scalar_product(v, -1);
	if (v.x == ref.x && v.y == ref.y && v.z == ref.z)
		return (1);
	return (0);
}

int		is_black_edge(t_hit *hit)
{
	double	dist_min_max;
	double	edge_scale;

	if (hit->type == CONE)
		edge_scale = (hit->radius * hit->dist_from_center / hit->length) * 0.5;
	else
		edge_scale = hit->radius > 0.0 ? hit->radius * 0.5 : 0;
	if (hit->type == CYLINDER)
		hit->length *= 0.5;
	dist_min_max = hit->t_max - hit->t;
	if (dist_min_max < edge_scale && dist_min_max > PRECISION &&
	((is_dir(hit->dir) && !is_same_dir(hit->nml_max, hit->dir) &&
	!is_same_dir(hit->nml, hit->dir)) || !is_dir(hit->dir)))
		return (1);
	if (hit->type != PLANE && hit->length > 0)
	{
		if (hit->length >= hit->dist_from_center &&
		hit->length - hit->dist_from_center <= hit->length / 100)
			return (1);
	}
	return (0);
}
