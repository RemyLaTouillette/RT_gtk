/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sduprey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/21 18:34:19 by sduprey           #+#    #+#             */
/*   Updated: 2016/10/03 19:55:22 by tlepeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

void			click_draw(GtkApplication *app, gpointer user_data)
{
	t_env		*e;

	(void)app;
	e = user_data;
	check_scene(e);
}

void			click_switch(GtkApplication *app, gpointer user_data)
{
	t_env		*e;
	GObject		*o;
	gboolean	state;

	(void)app;
	e = user_data;
	if (e->s)
	{
		o = gtk_builder_get_object(e->builder, "btn_modif");
		state = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(o));
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
}

void			click_filter(GtkApplication *app, gpointer data)
{
	t_env		*e;

	(void)app;
	e = data;
	set_values_from_ui(e);
	if (e->s != NULL)
		mount_image(e, e->s);
}
