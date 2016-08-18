/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sduprey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/15 03:54:29 by sduprey           #+#    #+#             */
/*   Updated: 2016/08/15 08:28:22 by sduprey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <gtk/gtk.h>
#include <rtv1.h>

GdkPixbuf			*gtk_new_image(unsigned char *data, int width, int height)
{
	GdkPixbuf		*pixbuf;
	GBytes			*buf;

	buf = NULL;
	pixbuf = NULL;
	buf = g_bytes_new(data, width * height * 3);
	if (!(pixbuf = gdk_pixbuf_new_from_bytes(buf, GDK_COLORSPACE_RGB, 0, 8, width, height, 3 * width)))
		return (NULL);
	g_bytes_unref(buf);
	buf = NULL;
	return (pixbuf);
}

void				gtk_put_pixel(GdkPixbuf *pixbuf, int x, int y, int color)
{
	int				width;
	int				height;
	int				rowstride;
	int				n_channels;
	unsigned char	*buf;
	unsigned char	*p;

	n_channels = gdk_pixbuf_get_n_channels(pixbuf);
	width = gdk_pixbuf_get_width(pixbuf);
	height = gdk_pixbuf_get_height(pixbuf);
	rowstride = gdk_pixbuf_get_rowstride(pixbuf);
	buf = gdk_pixbuf_get_pixels(pixbuf);
	p = buf + y * rowstride + x * n_channels;
	p[0] = (color & 0xFF0000) >> 16;
	p[1] = (color & 0x00FF00) >> 8;
	p[2] = (color & 0xFF);
}

int					gtk_put_image_to_window(GtkImage *img, GdkPixbuf *pixbuf)
{
	gtk_image_clear(img);
	gtk_image_set_from_pixbuf(img, pixbuf);
	return (1);
}
/*
static void			print_hello (GtkWidget *widget, gpointer data)
{
	(void)widget;
	(void)data;
	g_print("Hello World !\n");
}*/

static void			activate(GtkApplication *app, gpointer usr_data)
{
	GtkWidget		*win;
	//GtkWidget		*btn;
	//GtkWidget		*btn_box;

	(void)usr_data;
	win = gtk_application_window_new (app);
	//gtk_window_set_decorated(GTK_WINDOW (win), FALSE);
	//
	//gtk_window_set_type_hint(GTK_WINDOW(win), GDK_WINDOW_TYPE_HINT_NORMAL);
	gtk_window_set_type_hint(GTK_WINDOW(win), GDK_WINDOW_TYPE_HINT_DIALOG);
	//gtk_window_set_type_hint(GTK_WINDOW(win), GDK_WINDOW_TYPE_HINT_MENU);
	//gtk_window_set_type_hint(GTK_WINDOW(win), GDK_WINDOW_TYPE_HINT_TOOLBAR);
	//gtk_window_set_type_hint(GTK_WINDOW(win), GDK_WINDOW_TYPE_HINT_SPLASHSCREEN);
	//gtk_window_set_type_hint(GTK_WINDOW(win), GDK_WINDOW_TYPE_HINT_UTILITY);
	//gtk_window_set_type_hint(GTK_WINDOW(win), GDK_WINDOW_TYPE_HINT_DOCK);
	//gtk_window_set_type_hint(GTK_WINDOW(win), GDK_WINDOW_TYPE_HINT_DESKTOP);
	//
	gtk_window_set_title(GTK_WINDOW (win), "Window");
	gtk_window_set_default_size(GTK_WINDOW (win), WIDTH, HEIGHT);
	gtk_window_set_resizable(GTK_WINDOW (win), FALSE);
	//gtk_window_set_decorated(GTK_WINDOW (win), FALSE);
	//btn_box = gtk_button_box_new (GTK_ORIENTATION_HORIZONTAL);
	//gtk_container_add (GTK_CONTAINER (win), btn_box);

	//btn = gtk_button_new_with_label ("Hello world !");
	//g_signal_connect(btn, "clicked", G_CALLBACK (print_hello), NULL);
	//g_signal_connect_swapped (btn, "clicked", G_CALLBACK (gtk_widget_destroy), win);
	//gtk_container_add (GTK_CONTAINER (btn_box), btn);
	//
	GdkPixbuf	*pixbuf;
	int			w;
	int			h;
	unsigned char	*data;

	GtkImage		*img;


	w = 1920;
	h = 1080;
	data = (unsigned char *)malloc(sizeof(unsigned char) * w * h * 3);
	int i = 0;
	while (i < w * h)
	{
		data[i] = (unsigned char)0x0000FF;
		i++;
	}
	pixbuf = NULL;
	img = NULL;
	pixbuf = gtk_new_image(data, w, h);
	img = GTK_IMAGE (gtk_image_new_from_pixbuf (pixbuf));
	gtk_put_image_to_window(GTK_IMAGE (img), pixbuf);
	gtk_container_add (GTK_CONTAINER (win), GTK_WIDGET (img));



	gtk_widget_show_all (win);
}

int					main(int ac, char **av)
{
	GtkApplication	*app;
	int				status;

	app = gtk_application_new("org.gtk.example", G_APPLICATION_FLAGS_NONE);
	g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
	status = g_application_run(G_APPLICATION (app), ac, av);
	g_object_unref (app);
	return (status);
}
