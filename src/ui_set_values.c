/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_set_values.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sduprey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/17 17:08:14 by sduprey           #+#    #+#             */
/*   Updated: 2016/09/17 20:01:16 by sduprey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

void			set_values_from_ui(t_env *e, t_scene *s)
{
	GObject		*o;
	GdkRGBA		*color;
	gboolean	state;

	o = gtk_builder_get_object(e->builder, "btn_modif");
	state = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(o));
	if (state)
	{
		// CAM POS
		o = gtk_builder_get_object(e->builder, "scale_cam_pos_x");
		s->cam.ray.pos.x = gtk_range_get_value(GTK_RANGE(o));
		o = gtk_builder_get_object(e->builder, "scale_cam_pos_y");
		s->cam.ray.pos.y = gtk_range_get_value(GTK_RANGE(o));
		o = gtk_builder_get_object(e->builder, "scale_cam_pos_z");
		s->cam.ray.pos.z = gtk_range_get_value(GTK_RANGE(o));
		// CAM DIR
		o = gtk_builder_get_object(e->builder, "scale_cam_dir_x");
		s->cam.ray.dir.x = gtk_range_get_value(GTK_RANGE(o));
		o = gtk_builder_get_object(e->builder, "scale_cam_dir_y");
		s->cam.ray.dir.y = gtk_range_get_value(GTK_RANGE(o));
		o = gtk_builder_get_object(e->builder, "scale_cam_dir_z");
		s->cam.ray.dir.z = gtk_range_get_value(GTK_RANGE(o));
		// LOOP
		o = gtk_builder_get_object(e->builder, "scale_loop");
		s->reflection = gtk_range_get_value(GTK_RANGE(o));
		// AMBIENT LIGHTING
		color = (GdkRGBA *)malloc(sizeof(GdkRGBA));
		o = gtk_builder_get_object(e->builder, "btn_color");
		gtk_color_chooser_get_rgba (GTK_COLOR_CHOOSER(o), color);
		s->ambient_color.r = color->red  * 255;
		s->ambient_color.g = color->green * 255;
		s->ambient_color.b = color->blue * 255;
		//printf("%f %f %f\n", s->ambient_color.r, s->ambient_color.g, s->ambient_color.b);
		o = gtk_builder_get_object(e->builder, "scale_color");
		s->ambient_index = gtk_range_get_value(GTK_RANGE(o)) == 0 ? REALISTIC : CARTOON;
		// EFFECT
		//// CARTOON
		o = gtk_builder_get_object(e->builder, "switch_cartoon");
		s->is_real = gtk_switch_get_state(GTK_SWITCH(o));
		//// DOF
		o = gtk_builder_get_object(e->builder, "switch_dof");
		s->is_dof = gtk_switch_get_state(GTK_SWITCH(o));
		o = gtk_builder_get_object(e->builder, "scale_dof");
		s->dof = gtk_range_get_value(GTK_RANGE(o));
		o = gtk_builder_get_object(e->builder, "scale_blur");
		s->blur = gtk_range_get_value(GTK_RANGE(o));
		// FILTER
	}
}
