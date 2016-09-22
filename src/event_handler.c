/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sduprey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/21 18:34:19 by sduprey           #+#    #+#             */
/*   Updated: 2016/09/22 17:04:03 by tlepeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

// PROTO QUI N'ONT RIEN A FOUTRE LA
void	init_threads(t_thread *t, t_scene *s, t_env *e);
double	**create_tab_noise(void);
void	save_jpeg(unsigned char *data);
void	check_scene(t_env *e);

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

	e = data;
	(void)app;
	save_bmp(e->buf);
}

void			click_draw(GtkApplication *app, gpointer user_data)
{
	t_env		*e;

	e = user_data;
	check_scene(e);
	(void)app;
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
