/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sduprey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/10 03:20:20 by sduprey           #+#    #+#             */
/*   Updated: 2016/08/08 06:23:37 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>
#include <stdio.h>

t_cam		init_camera(t_vec pos, t_vec look)
{
	t_cam	cam;

	cam.ray.pos = pos;
	cam.ray.dir.x = 0;
	cam.ray.dir.y = 0;
	cam.ray.dir.z = 0;
	cam.look_at = look;
	cam.d = 1.0f;
	cam.h = 0.28f;
	cam.w = 0.5f;
	return (cam);
}

t_vec		calc_vec_dir(int x, int y, t_cam cam, t_vec look)
{
	double	x_indent;
	double	y_indent;
	t_vec	res;
	t_vec	tmp;

	x_indent = cam.w / (double)WIDTH;
	y_indent = cam.h / (double)HEIGHT;

	res.x = ((x - (double)WIDTH/2.0) * x_indent);
	res.y = ((y - (double)HEIGHT/2.0) * y_indent);
	res.z = cam.d;
//	printf("res: x = %.2f, y = %.2f, z = %.2f\n", res.x, res.y, res.z);
	// calcul pour faire une rotation sur l'axe des z;

	tmp = vec_rot_x(res, look.x);
	tmp = vec_rot_y(tmp, look.y);
	tmp = vec_rot_z(tmp, look.z);

	return (tmp);
}
