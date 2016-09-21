/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sduprey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/21 18:34:19 by sduprey           #+#    #+#             */
/*   Updated: 2016/09/21 18:59:15 by sduprey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

// PROTO QUI N'ONT RIEN A FOUTTRE LA
void	init_threads(t_thread *t, t_scene *s, t_env *e);
double	**create_tab_noise(void);

void			click_quit(GtkApplication *app, gpointer user_data)
{
	(void)app;
	(void)user_data;
	gtk_main_quit();
}

void			click_save(GtkApplication *app, gpointer user_data)
{
	t_env		*e;

	(void)app;
	e = user_data;
	save_bmp2(e->buf);
//	save_bmp(e->buf);
// FONCTION TEST POUR POPUP ERROR
//	test_error();
}

void			click_draw(GtkApplication *app, gpointer user_data)
{
	t_scene		*s;
	t_scene		*s2;
	GdkPixbuf	*pixbuf;
	t_env		*e;
	t_thread	threads[N_THREAD];
	int			i;
	char		*sname;

	e = user_data;
	sname = ft_strjoin("scenes/", get_scene_name(e));
	if (!(e->tab_noise = create_tab_noise()))
		exit(0);
	s2 = parse("scenes/test_cyl");
	if (!(s = parse(sname)))
		ft_putendl("No scene\n");
	else
	{
		set_values_from_ui(e, s);
		init_threads(threads, s, e);
		i = -1;
		while (++i < N_THREAD)
		{
			if (pthread_create(&(threads[i].pth), NULL, draw_scene, &threads[i]) != 0)
			{
				ft_putendl("Creating threads failed\n");
				exit(0);
			}
		}
		i = -1;
		while (++i < N_THREAD)
		{
			if (pthread_join(threads[i].pth, NULL) != 0)
			{
				ft_putendl("Joining threads failed\n");
				exit(0);
			}
		}
	}
	gtk_new_image(e->buf);
	if (s->filter != NONE)
	{
		e->buf_tmp = sepia_filter(e->buf, s->filter);
		pixbuf = gtk_new_image(e->buf_tmp);
	}
	else
	{
		pixbuf = gtk_new_image(e->buf);
	}
	gtk_put_image_to_window(e->img, pixbuf);
	free(s);
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
