/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhenne <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/04 06:11:33 by bhenne            #+#    #+#             */
/*   Updated: 2016/09/21 16:02:26 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>
#include <stdio.h>

t_color	checkerboard(t_color color, t_vec coord_hit)
{
	int		p[3];
	double	len;
	int		test;

	len = 5;
	p[0] = round(coord_hit.x * len);
	p[1] = round(coord_hit.y * len);
	p[2] = round(coord_hit.z * len);
	test = 0;
	test += p[0] % 2 == 0 ? 1 : 0;
	test += p[1] % 2 == 0 ? 1 : 0;
	test += p[2] % 2 == 0 ? 1 : 0;
	if (test % 2 == 0)
		mult_color(&color, 0.1);
	return (color);
}
