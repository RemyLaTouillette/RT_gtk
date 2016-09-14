/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perlin.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlepeche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/24 03:33:26 by tlepeche          #+#    #+#             */
/*   Updated: 2016/09/09 16:55:50 by tlepeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

double	smooth_noise(double x, double y, double **tab_noise)
{
	double	fract_x;
	double	fract_y;
	int		*n_x;
	int		*n_y;
	double	value;

	if (!(n_x = (int *)malloc(sizeof(int) * (2))))
		return (0.0);
	if (!(n_y = (int *)malloc(sizeof(int) * (2))))
		return (0.0);
	fract_x = x - (int)x;
	fract_y = y - (int)y;
	n_x[0] = ((int)x + WIDTH) % WIDTH;
	n_y[0] = ((int)y + HEIGHT) % HEIGHT;
	n_x[1] = (n_x[0] + WIDTH - 1) % WIDTH;
	n_y[1] = (n_y[0] + HEIGHT - 1) % HEIGHT;
	value = fract_x * fract_y * tab_noise[n_y[0]][n_x[0]];
	value += (1 - fract_x) * fract_y * tab_noise[n_y[0]][n_x[1]];
	value += fract_x * (1 - fract_y) * tab_noise[n_y[1]][n_x[0]];
	value += (1 - fract_x) * (1 - fract_y) * tab_noise[n_y[1]][n_x[1]];
	free(n_x);
	free(n_y);
	return (value);
}

double	turbulence(double x, double y, double res, double **tab_noise)
{
	double	value;
	double	init_res;

	value = 0.0;
	init_res = res;
	while (res >= 1)
	{
		value += smooth_noise(x / res, y / res, tab_noise) * res;
		res /= 2.0;
	}
	return (128 * value / init_res);
}

double	apply_marble_noise(int x, int y, double res, double **tab_noise)
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
	xy_val += turb_power * turbulence(x, y, res, tab_noise) / 256.0;
	sin_val = 256 * fabs(sin(xy_val * M_PI));
	return (sin_val);
}
