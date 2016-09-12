/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sduprey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/07 00:15:41 by sduprey           #+#    #+#             */
/*   Updated: 2016/09/12 17:39:38 by sduprey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

#include <image_buffer.h>

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

static void click_quit(GtkApplication *app, gpointer user_data)
{
	(void)app;
	(void)user_data;
	g_print("btn_click_quit()\n");
	gtk_main_quit();
}

static void	click_save(GtkApplication *app, gpointer user_data)
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

int	pulse_pbar(void *data);

static void click_draw(GtkApplication *app, gpointer user_data)
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
	g_print("%s\n", sname);

	// CAM POS
	o = gtk_builder_get_object(e->builder, "scale_cam_pos_x");
	val = gtk_range_get_value(GTK_RANGE(o));
	g_print("cam pos x: %f\n", val);
	
	o = gtk_builder_get_object(e->builder, "scale_cam_pos_y");
	val = gtk_range_get_value(GTK_RANGE(o));
	g_print("cam pos y: %f\n", val);

	o = gtk_builder_get_object(e->builder, "scale_cam_pos_z");
	val = gtk_range_get_value(GTK_RANGE(o));
	g_print("cam pos z: %f\n", val);

	// CAM DIR
	o = gtk_builder_get_object(e->builder, "scale_cam_dir_x");
	val = gtk_range_get_value(GTK_RANGE(o));
	g_print("cam dir x: %f\n", val);
	
	o = gtk_builder_get_object(e->builder, "scale_cam_dir_y");
	val = gtk_range_get_value(GTK_RANGE(o));
	g_print("cam dir y: %f\n", val);

	o = gtk_builder_get_object(e->builder, "scale_cam_dir_z");
	val = gtk_range_get_value(GTK_RANGE(o));
	g_print("cam dir z: %f\n", val);

	// CARTOON
	o = gtk_builder_get_object(e->builder, "switch_cartoon");
	gboolean carto;
	carto = gtk_switch_get_state(GTK_SWITCH(o));
	g_print("cartoon: %d\n", carto);


	// FILTER
	o = gtk_builder_get_object(e->builder, "cmb_filter");
	c = gtk_combo_box_text_get_active_text (GTK_COMBO_BOX_TEXT(o));
	g_print("filter: %s\n", c);

	// DOF
	o = gtk_builder_get_object(e->builder, "switch_dof");
	gboolean dof;
	dof = gtk_switch_get_state(GTK_SWITCH(o));
	g_print("dof: %d\n", dof);
	// focus
	o = gtk_builder_get_object(e->builder, "scale_focus");
	val = gtk_range_get_value(GTK_RANGE(o));
	g_print("focus: %f\n", val);
	// blur
	o = gtk_builder_get_object(e->builder, "scale_blur");
	val = gtk_range_get_value(GTK_RANGE(o));
	g_print("blur: %f\n", val);

	// LIGHTING
	GdkRGBA *color;


	color = (GdkRGBA *)malloc(sizeof(GdkRGBA));
	o = gtk_builder_get_object(e->builder, "btn_color");
	gtk_color_chooser_get_rgba(GTK_COLOR_CHOOSER(o), color);
	g_print("red: %f\n", color->red);
	g_print("green: %f\n", color->green);
	g_print("blue: %f\n", color->blue);



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
	GObject		*win;
	GObject		*o;
	GdkPixbuf		*pixbuf;
	t_env			e;
	//t_scene			*s;

	(void)click_draw;
	(void)click_quit;

	gtk_init(NULL, NULL);

	e.builder = gtk_builder_new_from_file("ui/builder.c.ui");

	win = gtk_builder_get_object(e.builder, "window");
	g_signal_connect(win, "destroy", G_CALLBACK(gtk_main_quit), NULL);

	e.img = gtk_builder_get_object(e.builder, "img");
	e.buf = new_image_buffer(WIDTH, HEIGHT);
	pixbuf = gtk_new_image(e.buf, WIDTH, HEIGHT);
	gtk_put_image_to_window(GTK_IMAGE(e.img), pixbuf);
	

	o = gtk_builder_get_object(e.builder, "btn_draw");
	g_signal_connect(o, "clicked", G_CALLBACK(click_draw), &e);
	o = gtk_builder_get_object(e.builder, "btn_quit");
	g_signal_connect(o, "clicked", G_CALLBACK(click_quit), &e);

	o = gtk_builder_get_object(e.builder, "btn_save");
	g_signal_connect(o, "clicked", G_CALLBACK(click_save), &e);

	// VAS CHERCHER LES SCENES
	
	DIR	*dir = NULL;
	struct dirent *pika = NULL;

	o = gtk_builder_get_object(e.builder, "cmb_scene");


	//gtk_combo_box_text_append_text

	dir = opendir("/nfs/2014/s/sduprey/42/Projects/RT_gtk.git/scenes");
	if (dir == NULL)
	{
		printf("gros NULL\n");
	}
	else
	{
		printf("cc\n");
		while ((pika = readdir(dir)) != NULL)
		{
			if (ft_strcmp(pika->d_name, ".") && ft_strcmp(pika->d_name, ".."))
			{
				printf("Hello: %s\n", pika->d_name);
				gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(o), pika->d_name);
			}
		}
	closedir(dir);
	}

	gtk_main();
	return (0);
}
