/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sduprey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/07 00:15:41 by sduprey           #+#    #+#             */
/*   Updated: 2016/09/11 16:03:11 by nbelouni         ###   ########.fr       */
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

GdkPixbuf			*gtk_new_image(unsigned char *data, int width, int height)
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
	buffer = g_bytes_new(data, width * height * 3);
	pixbuf = gdk_pixbuf_new_from_bytes(buffer, GDK_COLORSPACE_RGB, 0, 8, width, height, 3 * width);
	if (!pixbuf)
		return (NULL);
	g_bytes_unref(buffer);
	buffer = NULL;
	return (pixbuf);
}

void				gtk_put_pixel(GdkPixbuf *pixbuf, int x, int y, int color)
{
	int				width;
	int				height;
	int				rowstride;
	int				n_channels;
	unsigned char	*buffer;
	unsigned char	*p;

	n_channels = gdk_pixbuf_get_n_channels(pixbuf);
	width = gdk_pixbuf_get_width(pixbuf);
	height = gdk_pixbuf_get_height(pixbuf);
	rowstride = gdk_pixbuf_get_rowstride(pixbuf);
	buffer = gdk_pixbuf_get_pixels(pixbuf);
	p = buffer + y * rowstride + x * n_channels;
	p[0] = (color & 0xFF0000) >> 16;
	p[1] = (color & 0x00FF00) >> 8;
	p[2] = (color & 0xFF);
}

int		gtk_put_image_to_window(GtkImage *image, GdkPixbuf *pixbuf)
{
	gtk_image_clear(image);
	gtk_image_set_from_pixbuf(image, pixbuf);
	return (1);
}

#include <sys/wait.h>
#define APP_ID "RT.test"

void click_quit(GtkApplication *app, gpointer user_data)
{
	(void)app;
	(void)user_data;
	g_print("btn_click_quit()\n");
	gtk_main_quit();
}

void	click_save(GtkApplication *app, gpointer user_data)
{
	t_env	*e;

	(void)app;
	g_print("click_save()\n");
	e = user_data;
	save_bmp(e->buf);
}

#include <stdio.h>

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

	g_print("btn_click_draw()\n");
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

	// CARTOON
	o = gtk_builder_get_object(e->builder, "switch_cartoon");
	gboolean carto;
	carto = gtk_switch_get_state(GTK_SWITCH(o));


	// FILTER
	o = gtk_builder_get_object(e->builder, "cmb_filter");
	c = gtk_combo_box_text_get_active_text (GTK_COMBO_BOX_TEXT(o));

	// DOF
	o = gtk_builder_get_object(e->builder, "switch_dof");
	gboolean dof;
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


	//if (!(s = parse("../test/scenes/scene_bug_transparence")))
	
	char	*hey;

	hey = ft_strjoin("scenes/", sname);
	g_print("%s\n", hey);

	if (!(s = parse(hey)))
		printf("No scene\n");
	else
	{
		init_threads(threads, s, e);
		i = -1;
		while (++i < N_THREAD)
		{
			if (pthread_create(&(threads[i].pth), NULL, draw_scene, &threads[i]) != 0)
				printf("FAIL1\n");
		}
		i = -1;
		while (++i < N_THREAD)
		{
			if (pthread_join(threads[i].pth, NULL) != 0)
				printf("FAIL2\n");
		}
	}


/*	
	o = gtk_builder_get_object(e->builder, "btn_draw");
	gtk_widget_set_sensitive (GTK_WIDGET(o), FALSE);
*/
	o = gtk_builder_get_object(e->builder, "lbl_info");
	gtk_label_set_text (GTK_LABEL(o), "Hey !");

	gtk_new_image(e->buf, WIDTH, HEIGHT);
	pixbuf = gtk_new_image(e->buf, WIDTH, HEIGHT);
	gtk_put_image_to_window(e->img, pixbuf);

	(void)app;
	(void)user_data;
}
int		main(void)
{
	t_env			e;

	ui_init(&e);
	gtk_main();
	return (0);
}
