/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlepeche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/14 18:22:22 by tlepeche          #+#    #+#             */
/*   Updated: 2016/09/21 17:00:05 by sduprey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>
#include <ui_init.h>

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
	o = gtk_builder_get_object(e->builder, "frm_effect");
	gtk_widget_set_sensitive(GTK_WIDGET(o), state);
	o = gtk_builder_get_object(e->builder, "frm_light");
	gtk_widget_set_sensitive(GTK_WIDGET(o), state);
	if (state)
	{
		o = gtk_builder_get_object(e->builder, "cmb_scene");
		sname = gtk_combo_box_text_get_active_text((GTK_COMBO_BOX_TEXT(o)));
		if ((s = parse(ft_strjoin("scenes/", sname))))
		{
			set_values_from_scene(e, s);
		}
	}
}

void			click_filter(GtkApplication *app, gpointer data)
{
	t_env		*e;
	GdkPixbuf	*pixbuf;
	int			filter;

	(void)app;
	e = data;
	e->img = gtk_builder_get_object(e->builder, "img");
	filter = get_filter_name(e);
	e->buf_tmp = sepia_filter(e->buf, filter);
	if (e->buf_tmp == NULL)
	{
		g_print("Error\n");
		return ;
	}
	pixbuf = gtk_new_image(e->buf_tmp);
	gtk_put_image_to_window(e->img, pixbuf);
}

void			ui_init_img(t_env *e)
{
	GdkPixbuf	*pixbuf;

	e->img = gtk_builder_get_object(e->builder, "img");
	e->buf = new_image_buffer();
	pixbuf = gtk_new_image(e->buf);
	gtk_put_image_to_window(GTK_IMAGE(e->img), pixbuf);
}

void			ui_init_scenes(t_env *e, char *path)
{
	GObject		*o;
	char		**scenes;
	int			i;

	scenes = scene_finder(path);
	if (scenes != NULL)
	{
		o = gtk_builder_get_object(e->builder, "cmb_scene");
		i = 0;
		while (scenes[i] != NULL)
		{
			gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(o), scenes[i++]);
		}
	}
	free_tab(scenes);
}

void			ui_init_callback(t_env *e)
{
	GObject		*o;

	o = gtk_builder_get_object(e->builder, "window");
	g_signal_connect(o, "destroy", G_CALLBACK(gtk_main_quit), NULL);
	o = gtk_builder_get_object(e->builder, "btn_draw");
	g_signal_connect(o, "clicked", G_CALLBACK(click_draw), e);
	o = gtk_builder_get_object(e->builder, "btn_quit");
	g_signal_connect(o, "clicked", G_CALLBACK(click_quit), e);
	o = gtk_builder_get_object(e->builder, "btn_save");
	g_signal_connect(o, "clicked", G_CALLBACK(click_save), e);
	o = gtk_builder_get_object(e->builder, "btn_modif");
	g_signal_connect(o, "clicked", G_CALLBACK(click_switch), e);
	o = gtk_builder_get_object(e->builder, "cmb_scene");
	g_signal_connect(o, "changed", G_CALLBACK(click_switch), e);
	o = gtk_builder_get_object(e->builder, "btn_filter");
	g_signal_connect(o, "clicked", G_CALLBACK(click_filter), e);
}

void			ui_init(t_env *e)
{
	gtk_init(NULL, NULL);
	e->builder = gtk_builder_new_from_file("ui/builder.ui");
	e->win = gtk_builder_get_object(e->builder, "window");
	ui_init_img(e);
	ui_init_scenes(e, "scenes");
	ui_init_callback(e);
}
