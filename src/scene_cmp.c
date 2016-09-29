/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_cmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlepeche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/16 13:17:21 by tlepeche          #+#    #+#             */
/*   Updated: 2016/09/29 16:02:44 by sduprey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

int		cam_cmp(t_cam new_cam, t_cam old_cam)
{
	if (ray_cmp(new_cam.ray, old_cam.ray) == 1 &&
		vec_cmp(new_cam.look_at, old_cam.look_at) == 1 &&
		new_cam.w == old_cam.w &&
		new_cam.h == old_cam.h &&
		new_cam.d == old_cam.d)
		return (1);
	return (0);
}

int		scene_cmp(t_scene *new_scene, t_scene *old_scene)
{
	if (new_scene == NULL || old_scene == NULL)
		return (0);
	if (new_scene->is_real != old_scene->is_real ||
		new_scene->ambient_index != old_scene->ambient_index ||
		color_cmp(new_scene->ambient_color, old_scene->ambient_color) == 0 ||
		new_scene->reflection != old_scene->reflection ||
		new_scene->w != old_scene->w || new_scene->h != old_scene->h)
		return (0);
	if (cam_cmp(new_scene->cam, old_scene->cam) == 0)
		return (0);
	if (objects_cmp(new_scene->objects, old_scene->objects) == 0)
		return (0);
	if (lights_cmp(new_scene->lights, old_scene->lights) == 0)
		return (0);
	return (1);
}
