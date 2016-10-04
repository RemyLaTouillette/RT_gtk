/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_set_values.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sduprey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/17 17:08:14 by sduprey           #+#    #+#             */
/*   Updated: 2016/10/04 17:04:20 by tlepeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

void			set_values_from_ui(t_env *e, int bool)
{
	gboolean	state;

	state = get_switch_state(e, "switch_modif");
	if (!e->s)
		return ;
	if (state && bool)
	{
		e->s->cam.ray.pos = get_cam_pos_from_ui(e);
		e->s->cam.look_at = get_cam_dir_from_ui(e);
		e->s->reflection = get_range_value(e, "scale_loop");
		e->s->ambient_color = get_rgba(e);
		e->s->ambient_index = get_range_value(e, "scale_color");
		e->s->is_real = get_switch_state(e, "switch_cartoon") == 0 ?
			REALISTIC : CARTOON;
	}
	e->s->is_dof = get_switch_state(e, "switch_dof");
	e->s->dof = get_range_value(e, "scale_focus");
	e->s->blur = get_range_value(e, "scale_blur");
	e->s->filter = get_filter_name(e);
	e->s->aa = get_switch_state(e, "switch_aa");
}

void			set_values_from_scene(t_env *e, t_scene *s)
{
	set_cam_pos_from_scene(e, s);
	set_cam_dir_from_scene(e, s);
	set_reflection_from_scene(e, s);
	set_ambient_color_from_scene(e, s);
	set_effect_from_scene(e, s);
}
