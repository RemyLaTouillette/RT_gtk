/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/13 22:39:57 by nbelouni          #+#    #+#             */
/*   Updated: 2016/08/25 16:09:52 by tlepeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _LIGHT_H
# define _LIGHT_H

# include <scene.h>
# include <ray.h>

# define DIFFUSE	1
# define PARALLEL	2
# define DIRECT		3

typedef struct	s_light
{
	int			type;
	t_vec		pos;
	t_vec		look_at;
	t_color		color;
	double		angle;
}				t_light;

t_color			apply_light(t_scene *scene, t_hit curr_pixel, t_ray *cam_ray);

#endif
