/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlepeche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/21 06:54:08 by tlepeche          #+#    #+#             */
/*   Updated: 2016/09/21 16:02:39 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

void		check_color(t_color *color)
{
	if (color->r < 0)
		color->r = 0;
	else if (color->r > 255)
		color->r = 255;
	if (color->g < 0)
		color->g = 0;
	else if (color->g > 255)
		color->g = 255;
	if (color->b < 0)
		color->b = 0;
	else if (color->b > 255)
		color->b = 255;
}

void		add_color(t_color *a, t_color *b)
{
	a->r += b->r;
	a->g += b->g;
	a->b += b->b;
	check_color(a);
}

void		init_color(t_color *res, int r, int g, int b)
{
	res->r = r;
	res->g = g;
	res->b = b;
	check_color(res);
}

void		mult_color(t_color *ref, double coef)
{
	ref->r *= coef;
	ref->g *= coef;
	ref->b *= coef;
	check_color(ref);
}
