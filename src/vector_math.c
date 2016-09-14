/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_math.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhenne <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/08 02:18:07 by bhenne            #+#    #+#             */
/*   Updated: 2016/09/09 15:07:40 by tlepeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_vec	vec_rot_y(t_vec a, double angle)
{
	t_vec res;

	res.x = a.z * sin(angle) + a.x * cos(angle);
	res.y = a.y;
	res.z = a.z * cos(angle) - a.x * sin(angle);
	return (res);
}

t_vec	vec_rot_x(t_vec a, double angle)
{
	t_vec res;

	res.x = a.x;
	res.y = a.y * cos(angle) - a.z * sin(angle);
	res.z = a.y * sin(angle) + a.z * cos(angle);
	return (res);
}

t_vec	vec_rot_z(t_vec a, double angle)
{
	t_vec res;

	res.x = a.x * cos(angle) - a.y * sin(angle);
	res.y = a.x * sin(angle) + a.y * cos(angle);
	res.z = a.z;
	return (res);
}

double	c2(double x)
{
	double a;

	a = cos(x);
	return (a * a);
}

double	s2(double x)
{
	double a;

	a = sin(x);
	return (a * a);
}
