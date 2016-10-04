/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_get_values_from_scene.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sduprey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/21 16:25:31 by sduprey           #+#    #+#             */
/*   Updated: 2016/10/04 16:24:10 by tlepeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

void		set_cam_pos_from_scene(t_env *e, t_scene *s)
{
	GObject	*o;

	o = gtk_builder_get_object(e->builder, "scale_cam_pos_x");
	gtk_range_set_value(GTK_RANGE(o), s->cam.ray.pos.x);
	o = gtk_builder_get_object(e->builder, "scale_cam_pos_y");
	gtk_range_set_value(GTK_RANGE(o), s->cam.ray.pos.y);
	o = gtk_builder_get_object(e->builder, "scale_cam_pos_z");
	gtk_range_set_value(GTK_RANGE(o), s->cam.ray.pos.z);
}

void		set_cam_dir_from_scene(t_env *e, t_scene *s)
{
	GObject	*o;

	o = gtk_builder_get_object(e->builder, "scale_cam_dir_x");
	gtk_range_set_value(GTK_RANGE(o), 180 / M_PI * s->cam.look_at.x);
	o = gtk_builder_get_object(e->builder, "scale_cam_dir_y");
	gtk_range_set_value(GTK_RANGE(o), 180 / M_PI * s->cam.look_at.y);
	o = gtk_builder_get_object(e->builder, "scale_cam_dir_z");
	gtk_range_set_value(GTK_RANGE(o), 180 / M_PI * s->cam.look_at.z);
}

void		set_reflection_from_scene(t_env *e, t_scene *s)
{
	GObject	*o;

	o = gtk_builder_get_object(e->builder, "scale_loop");
	gtk_range_set_value(GTK_RANGE(o), s->reflection);
}

void		set_ambient_color_from_scene(t_env *e, t_scene *s)
{
	GObject	*o;
	GdkRGBA	*rgba;

	rgba = (GdkRGBA *)malloc(sizeof(GdkRGBA));
	if (rgba != NULL)
	{
		rgba->red = s->ambient_color.r / 255;
		rgba->green = s->ambient_color.g / 255;
		rgba->blue = s->ambient_color.b / 255;
		rgba->alpha = 1.0;
		o = gtk_builder_get_object(e->builder, "btn_color");
		gtk_color_chooser_set_rgba(GTK_COLOR_CHOOSER(o), rgba);
	}
	o = gtk_builder_get_object(e->builder, "scale_color");
	gtk_range_set_value(GTK_RANGE(o), s->ambient_index);
	gdk_rgba_free(rgba);
}

void		set_effect_from_scene(t_env *e, t_scene *s)
{
	GObject	*o;
	int		mode;

	mode = s->is_real == REALISTIC ? 0 : 1;
	o = gtk_builder_get_object(e->builder, "switch_cartoon");
	gtk_switch_set_state(GTK_SWITCH(o), mode);
	o = gtk_builder_get_object(e->builder, "switch_dof");
	gtk_switch_set_state(GTK_SWITCH(o), s->is_dof);
	o = gtk_builder_get_object(e->builder, "scale_focus");
	gtk_range_set_value(GTK_RANGE(o), s->dof);
	o = gtk_builder_get_object(e->builder, "scale_blur");
	gtk_range_set_value(GTK_RANGE(o), s->blur);
	o = gtk_builder_get_object(e->builder, "switch_aa");
	gtk_switch_set_state(GTK_SWITCH(o), s->aa);
}
