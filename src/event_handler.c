/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sduprey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/21 18:34:19 by sduprey           #+#    #+#             */
/*   Updated: 2016/10/04 17:48:46 by tlepeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

void	click_save(GtkApplication *app, gpointer user_data)
{
	t_env		*e;

	(void)app;
	e = user_data;
	save_jpeg(e->buf);
}

void	click_save2(GtkApplication *app, gpointer data)
{
	t_env		*e;

	(void)app;
	e = data;
	save_bmp(e->buf);
}

void	click_draw(GtkApplication *app, gpointer user_data)
{
	t_env		*e;

	(void)app;
	e = user_data;
	check_scene(e);
}

void	click_switch(GtkApplication *app, gboolean state, gpointer user_data)
{
	t_env		*e;
	GObject		*o;

	e = user_data;
	o = gtk_builder_get_object(e->builder, "switch_modif");
	gtk_switch_set_state(GTK_SWITCH(o), state);
	if (e->s)
	{
		o = gtk_builder_get_object(e->builder, "frm_cam");
		gtk_widget_set_sensitive(GTK_WIDGET(o), state);
		o = gtk_builder_get_object(e->builder, "frm_light");
		gtk_widget_set_sensitive(GTK_WIDGET(o), state);
		o = gtk_builder_get_object(e->builder, "frm_cartoon");
		gtk_widget_set_sensitive(GTK_WIDGET(o), state);
		o = gtk_builder_get_object(e->builder, "frm_reflect");
		gtk_widget_set_sensitive(GTK_WIDGET(o), state);
		if (state)
			set_values_from_scene(e, e->s);
	}
	(void)app;
}

void	click_filter(GtkApplication *app, gpointer data)
{
	t_env		*e;

	(void)app;
	e = data;
	set_values_from_ui(e, 0);
	if (e->s != NULL)
		mount_image(e, e->s);
}
