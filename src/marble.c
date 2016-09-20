/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   marble.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlepeche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/20 12:38:46 by tlepeche          #+#    #+#             */
/*   Updated: 2016/09/20 12:43:35 by tlepeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

static inline double	smooth_noise(double x, double y, double **t)
{
	double	fract_x;
	double	fract_y;
	int		n_x[2];
	int		n_y[2];
	double	value;

	fract_x = x - (int)x;
	fract_y = y - (int)y;
	n_x[0] = ((int)x + WIDTH) % WIDTH;
	n_y[0] = ((int)y + HEIGHT) % HEIGHT;
	n_x[1] = (n_x[0] + WIDTH - 1) % WIDTH;
	n_y[1] = (n_y[0] + HEIGHT - 1) % HEIGHT;
	value = fract_x * fract_y * t[n_y[0]][n_x[0]];
	value += (1 - fract_x) * fract_y * t[n_y[0]][n_x[1]];
	value += fract_x * (1 - fract_y) * t[n_y[1]][n_x[0]];
	value += (1 - fract_x) * (1 - fract_y) * t[n_y[1]][n_x[1]];
	return (value);
}

static inline double	turbulence(double x, double y, double res, double **t)
{
	double	value;
	double	init_res;

	value = 0.0;
	init_res = res;
	while (res >= 1)
	{
		value += smooth_noise(x / res, y / res, t) * res;
		res *= 0.5;
	}
	return (128 * value / init_res);
}

double					apply_marble_noise(int x, int y, double res, double **t)
{
	double	x_period;
	double	y_period;
	double	turb_power;
	double	xy_val;
	double	sin_val;

	x_period = 1.0;
	y_period = 30.0;
	turb_power = 10.0;
	xy_val = x * x_period / WIDTH;
	xy_val += y * y_period / HEIGHT;
	xy_val += turb_power * turbulence(x, y, res, t) / 256.0;
	sin_val = 256 * fabs(sin(xy_val * M_PI));
	return (sin_val);
}
