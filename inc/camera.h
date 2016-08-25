/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sduprey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/10 03:20:28 by sduprey           #+#    #+#             */
/*   Updated: 2016/08/25 16:03:22 by tlepeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _CAMERA_H
# define _CAMERA_H

# include <vector.h>
# include <ray.h>

typedef struct	s_cam
{
	t_ray		ray;
	t_vec		look_at;
	double		w;
	double		h;
	double		d;
}				t_cam;

t_cam			init_camera(t_vec pos, t_vec look);
t_vec			calc_vec_dir(int x, int y, t_cam cam, t_vec look);

#endif
