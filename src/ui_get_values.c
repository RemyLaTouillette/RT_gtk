/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_get_values.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sduprey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/14 18:07:38 by sduprey           #+#    #+#             */
/*   Updated: 2016/10/03 17:31:50 by tlepeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

t_vec			get_cam_pos_from_ui(t_env *e)
{
	GObject		*o;
	double		x;
	double		y;
	double		z;

	o = gtk_builder_get_object(e->builder, "scale_cam_pos_x");
	x = gtk_range_get_value(GTK_RANGE(o));
	o = gtk_builder_get_object(e->builder, "scale_cam_pos_y");
	y = gtk_range_get_value(GTK_RANGE(o));
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

	o = gtk_builder_get_object(e->builder, "scale_cam_dir_x");
	x = gtk_range_get_value(GTK_RANGE(o));
	o = gtk_builder_get_object(e->builder, "scale_cam_dir_y");
	y = gtk_range_get_value(GTK_RANGE(o));
	o = gtk_builder_get_object(e->builder, "scale_cam_dir_z");
	z = gtk_range_get_value(GTK_RANGE(o));
	return (init_vector(deg_to_rad(x), deg_to_rad(y), deg_to_rad(z)));
}

int				get_switch_state(t_env *e, char *widget)
{
	GObject		*o;
	gboolean	state;

	o = gtk_builder_get_object(e->builder, widget);
	state = gtk_switch_get_state(GTK_SWITCH(o));
	return (state);
}

char			*get_scene_name(t_env *e)
{
	GObject		*o;
	char		*s;

	o = gtk_builder_get_object(e->builder, "cmb_scene");
	s = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(o));
	return (s);
}

int				get_filter_name(t_env *e)
{
	GObject		*o;
	char		*s;
	int			filter;

	o = gtk_builder_get_object(e->builder, "cmb_filter");
	s = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(o));
	if (ft_strcmp(s, "Sepia") == 0)
		filter = SEPIA;
	else if (ft_strcmp(s, "B&W") == 0)
		filter = NOIR_BLANC;
	else
		filter = NONE;
	free(s);
	return (filter);
}
