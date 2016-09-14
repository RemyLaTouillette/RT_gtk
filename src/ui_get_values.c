/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_get_values.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sduprey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/14 18:07:38 by sduprey           #+#    #+#             */
/*   Updated: 2016/09/14 19:03:13 by sduprey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

t_vec			get_cam_pos_from_ui(t_env *e)
{
	GObject		*o;
	double		x;
	double		y;
	double		z;

	// TODO: check override, else return NULL ?
	// X
	o = gtk_builder_get_object(e->builder, "scale_cam_pos_x");
	x = gtk_range_get_value(GTK_RANGE(o));
	// Y
	o = gtk_builder_get_object(e->builder, "scale_cam_pos_y");
	y = gtk_range_get_value(GTK_RANGE(o));
	// Z
	o = gtk_builder_get_object(e->builder, "scale_cam_pos_z");
	z = gtk_range_get_value(GTK_RANGE(o));
	return (init_vector(x, y, z));
}

t_vec			get_cam_dir_from_ui(t_env *e)
{
	GObject		*o;
	double		x;
	double		y;
	double		z;

	// TODO: check override, else return NULL ?
	// X
	o = gtk_builder_get_object(e->builder, "scale_cam_dir_x");
	x = gtk_range_get_value(GTK_RANGE(o));
	// Y
	o = gtk_builder_get_object(e->builder, "scale_cam_dir_y");
	y = gtk_range_get_value(GTK_RANGE(o));
	// Z
	o = gtk_builder_get_object(e->builder, "scale_cam_dir_z");
	z = gtk_range_get_value(GTK_RANGE(o));
	return (init_vector(x, y, z));
}
/*
int				cartoon_mode_is_active(t_env *e)
{
	GObject		*o;
	gboolean	active;

	o = gtk_builder_get_object(e->builder, "switch_cartoon");
	active = gtk_switch_get_state(GTK_SWITCH(o));
	if (active)
		return (1);
	return (0);
}
*/
int				get_switch_state(t_env *e, char *widget)
{
	GObject		*o;
	gboolean	state;

	o = gtk_builder_get_object(e->builder, widget);
	state = gtk_switch_get_state(GTK_SWITCH(o));
	return (state);
}
/*
int				get_draw_mode(t_env *e)
{
	GObject		*o;

	o = gtk_builder_get_object(e->builder, "")
}
*/
char			*get_scene_name(t_env *e)
{
	GObject		*o;
	char		*s;

	o = gtk_builder_get_object(e->builder, "cmb_scene");
	s = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(o));
	return (s);
}
