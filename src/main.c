/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sduprey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/07 00:15:41 by sduprey           #+#    #+#             */
/*   Updated: 2016/09/20 15:48:49 by tlepeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>
#include <image_buffer.h>

double	**create_tab_noise(void)
{
	int		x;
	int		y;
	double	**tab;

	y = 0;
	if (!(tab = (double **)malloc(sizeof(double *) * HEIGHT)))
		return (NULL);
	while (y < HEIGHT)
	{
		x = 0;
		if (!(tab[y] = (double *)malloc(sizeof(double) * WIDTH)))
			return (NULL);
		while (x < WIDTH)
		{
			tab[y][x] = (rand() % 32768) / 32768.0;
			x++;
		}
		y++;
	}
	return (tab);
}

GdkPixbuf			*gtk_new_image(unsigned char *data)
{
	GdkPixbuf		*pixbuf;
	GBytes			*buffer;

	buffer = NULL;
	pixbuf = NULL;
	int i = 0;
	while ((int)(data[i]) < 255 && (int)(data[i]) > 0)
	{
		i++;
	}
	buffer = g_bytes_new(data, WIDTH * HEIGHT * 3);
	pixbuf = gdk_pixbuf_new_from_bytes(buffer, GDK_COLORSPACE_RGB, 0, 8, WIDTH, HEIGHT, 3 * WIDTH);
	if (!pixbuf)
		return (NULL);
	g_bytes_unref(buffer);
	buffer = NULL;
	return (pixbuf);
}

int		gtk_put_image_to_window(GtkImage *image, GdkPixbuf *pixbuf)
{
	gtk_image_clear(image);
	gtk_image_set_from_pixbuf(image, pixbuf);
	return (1);
}


void click_quit(GtkApplication *app, gpointer user_data)
{
	(void)app;
	(void)user_data;
	gtk_main_quit();
}

// proto tmp qui n'a rien a foutre la
void	test_error(void);

void	click_save(GtkApplication *app, gpointer user_data)
{
	t_env	*e;

	(void)app;
	e = user_data;
//	save_bmp(e->buf);
// FONCTION TEST POUR POPUP ERROR
	test_error();
}

void		init_threads(t_thread *threads, t_scene *scene, t_env *e)
{
	int			i;
	t_pthread	pth[N_THREAD];
	t_mutex		mutex;

	pthread_mutex_init(&mutex, NULL);
	i = -1;
	while (++i < N_THREAD)
	{
		threads[i].scene = scene;
		threads[i].buf = e->buf;
		threads[i].env = e;
		threads[i].y_start = (WIDTH / N_THREAD) * i;
		threads[i].y_end = (WIDTH / N_THREAD) * (i + 1);
		threads[i].pth = pth[i];
		threads[i].mutex = &mutex;
	}
}

void click_draw(GtkApplication *app, gpointer user_data)
{

	t_scene		*s;
	GdkPixbuf	*pixbuf;
	t_env		*e;
	t_thread	threads[N_THREAD];
	int			i;
	GObject		*o;
	gchar		*c;
	gchar		*sname;
	gdouble val;
	char	*hey;
	gboolean dof;


	e = user_data;

	o = gtk_builder_get_object(e->builder, "cmb_scene");
	sname = gtk_combo_box_text_get_active_text (GTK_COMBO_BOX_TEXT(o));

	if (!(e->tab_noise = create_tab_noise()))
		exit(0);

	/* TODO
	if get_cam_pos_from_ui return NULL, keep parser values else get ui values
	if get_cam_dir_from_ui return NULL, keep parser values else get ui values

	get scene name

	get cartoon mode on/off
	get filter
	get dof
	get light
	get loop
	*/


	e->mode = get_switch_state(e, "switch_cartoon");

	// CARTOON
	o = gtk_builder_get_object(e->builder, "switch_cartoon");
	gboolean carto;
	carto = gtk_switch_get_state(GTK_SWITCH(o));


	// FILTE
	o = gtk_builder_get_object(e->builder, "cmb_filter");
	c = gtk_combo_box_text_get_active_text (GTK_COMBO_BOX_TEXT(o));

	// DOF
	o = gtk_builder_get_object(e->builder, "switch_dof");
	dof = gtk_switch_get_state(GTK_SWITCH(o));
	// focus
	o = gtk_builder_get_object(e->builder, "scale_focus");
	val = gtk_range_get_value(GTK_RANGE(o));
	// blur
	o = gtk_builder_get_object(e->builder, "scale_blur");
	val = gtk_range_get_value(GTK_RANGE(o));

	// LIGHTING
	GdkRGBA *color;


	color = (GdkRGBA *)malloc(sizeof(GdkRGBA));
	o = gtk_builder_get_object(e->builder, "btn_color");
	gtk_color_chooser_get_rgba(GTK_COLOR_CHOOSER(o), color);

	hey = ft_strjoin("scenes/", sname);

	t_scene *s2;
	s2 = parse("scenes/test_cyl");
	if (!(s = parse(hey)))
		ft_putendl("No scene\n");
	else
	{
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

/*	
	o = gtk_builder_get_object(e->builder, "btn_draw");
	gtk_widget_set_sensitive (GTK_WIDGET(o), FALSE);
*/
	o = gtk_builder_get_object(e->builder, "lbl_info");
	gtk_label_set_text (GTK_LABEL(o), "Hey !");

	gtk_new_image(e->buf);
	pixbuf = gtk_new_image(e->buf);
	gtk_put_image_to_window(e->img, pixbuf);
free(s);
	(void)app;
}

int		main(void)
{
	t_env			e;

	ui_init(&e);
	gtk_main();
	return (0);
}
