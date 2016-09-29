/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sduprey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/21 18:34:19 by sduprey           #+#    #+#             */
/*   Updated: 2016/09/29 20:25:24 by sduprey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

void			click_save(GtkApplication *app, gpointer user_data)
{
	t_env		*e;

	(void)app;
	e = user_data;
	save_jpeg(e->buf);
}

void			click_save2(GtkApplication *app, gpointer data)
{
	t_env		*e;

	(void)app;
	e = data;
	save_bmp(e->buf);
}

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
	gchar		*sname;
	t_scene		*s;

	(void)app;
	e = user_data;
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
	{
		o = gtk_builder_get_object(e->builder, "cmb_scene");
		sname = gtk_combo_box_text_get_active_text((GTK_COMBO_BOX_TEXT(o)));
		if ((s = parse(ft_strjoin("scenes/", sname))))
			set_values_from_scene(e, s);
	}
}

void			click_filter(GtkApplication *app, gpointer data)
{
	t_env		*e;

	(void)app;
	e = data;
	set_values_from_ui(e);
	mount_image(e, e->s);
}
