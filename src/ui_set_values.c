/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_set_values.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sduprey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/17 17:08:14 by sduprey           #+#    #+#             */
/*   Updated: 2016/09/20 20:10:47 by sduprey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

void			set_values_from_ui(t_env *e, t_scene *s)
{
	GObject		*o;
	gboolean	state;

	o = gtk_builder_get_object(e->builder, "btn_modif");
	state = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(o));
	if (state)
	{
		s->cam.ray.pos = get_cam_pos_from_ui(e);
		s->cam.ray.dir = get_cam_dir_from_ui(e);
		s->reflection = get_range_value(e, "scale_loop");
		s->ambient_color = get_rgba(e);
		s->ambient_index = get_range_value(e, "scale_color");
		s->is_real = get_switch_state(e, "switch_cartoon") == 0 ?
			REALISTIC : CARTOON;
		s->is_dof = get_switch_state(e, "switch_dof");
		s->dof = get_range_value(e, "scale_focus");
		s->blur = get_range_value(e, "scale_blur");
		//s->filter = get_filter_name(e);
	}
}
