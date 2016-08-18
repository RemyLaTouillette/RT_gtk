/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sduprey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/07 00:15:41 by sduprey           #+#    #+#             */
/*   Updated: 2016/08/18 19:52:57 by sduprey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

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
	//ft_putendl("ICI");
	//	ft_putnbr(ft_strlen((char *)data));
	//ft_putnbr(i);
	//ft_putendl("\n");
	//ft_putnbr(width * height * 3);
	//ft_putendl("\n");
	buffer = g_bytes_new(data, width * height * 3);
	ft_putendl("ou pas");
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
/*
   static void			activate(GtkApplication *app, gpointer user_data)
   {
   GtkWidget		*win;
//GtkWidget		*img;
//unsigned char	*buf;
//GdkPixbuf		*pixbuf;

if (!user_data)
{
ft_putendl("Error: new_image_buffer");
exit(0);
}
//pixbuf = gtk_new_image((unsigned char *)user_data, WIDTH, HEIGHT);
//img = gtk_image_new_from_pixbuf (pixbuf);
//
win = gtk_application_window_new(app);
gtk_window_set_title(GTK_WINDOW(win), "Window");
gtk_window_set_default_size(GTK_WINDOW(win), WIDTH, HEIGHT);

//gtk_container_add (GTK_CONTAINER (win), img);

gtk_widget_show_all(win);
}

static void	print_hello (GtkWidget *widget, gpointer data)
{
(void)widget;
(void)data;
g_print ("Hello Raytrace\n");
}

int					main(int ac, char** av)
{
// Gtk objects
GtkApplication	*app;
GtkBuilder		*builder;
GObject			*lst;
GObject			*window;
GObject			*button;
//
t_env			e;
t_scene			*scene;
int				status;

scene = NULL;
(void)ac;
(void)av;
if (ac != 2)
{
ft_putendl("No file");
return (0);
}

// BUILDER

gtk_init(NULL, NULL);

builder = gtk_builder_new();
gtk_builder_add_from_file (builder, "ui/builder.ui", NULL);

/ Connect signal handlers to the constructed widgets. /
window = gtk_builder_get_object (builder, "window");
g_signal_connect (window, "destroy", G_CALLBACK (gtk_main_quit), NULL);

g_signal_connect(window, "activate", G_CALLBACK (activate), NULL);

button = gtk_builder_get_object (builder, "trace");
g_signal_connect (button, "clicked", G_CALLBACK (print_hello), NULL);

button = gtk_builder_get_object (builder, "button2");
g_signal_connect (button, "clicked", G_CALLBACK (print_hello), NULL);

button = gtk_builder_get_object (builder, "quit");
g_signal_connect (button, "clicked", G_CALLBACK (gtk_main_quit), NULL);


lst = gtk_builder_get_object(builder, "grid");

// COMBO BOX
GtkWidget		*p_combo;
GtkListStore	*p_model;
GtkCellRenderer	*p_cell;
GtkTreeIter		iter;

p_model = gtk_list_store_new(2, G_TYPE_INT, G_TYPE_STRING);
p_combo = gtk_combo_box_new_with_model(GTK_TREE_MODEL (p_model));
//gtk_box_pack_start (GTK_BOX (p_vbox), p_combo, TRUE, TRUE, 0);
p_cell = gtk_cell_renderer_text_new ();
gtk_cell_layout_pack_start (GTK_CELL_LAYOUT (p_combo), p_cell, FALSE);
gtk_cell_layout_set_attributes (
		GTK_CELL_LAYOUT (p_combo),
		p_cell, "text", 0,
		NULL
		);

p_cell = gtk_cell_renderer_text_new ();
gtk_cell_layout_pack_start (GTK_CELL_LAYOUT (p_combo), p_cell, FALSE);
gtk_cell_layout_set_attributes (
		GTK_CELL_LAYOUT (p_combo),
		p_cell, "text", 1,
		NULL
		);

//

for (int i = 0; i < 10; i++)
{
	Ajpout d'un nouvel element dans le magasin. 
		gtk_list_store_append (p_model, & iter);

	// On rempli le nouvel element. 
	gtk_list_store_set (
			p_model, & iter,
			0, i + 1, 1, " - Element...",
			-1
			);
}


//
*        * On affiche un element par defaut. L'index commence à zero.
//               

gtk_container_add(GTK_CONTAINER (window), GTK_WIDGET (lst));

gtk_combo_box_set_active (GTK_COMBO_BOX (p_combo), 2);





lst = gtk_builder_get_object(builder, "select");

//	g_signal_connect(app, "activate", G_CALLBACK(activate), e.img);

gtk_main ();


if (!(scene = parse(av[1])))
{
	ft_putendl("Error: parse");
	return (0);
}
e.img = new_image_buffer(WIDTH, HEIGHT);
if (e.img == NULL)
{
	ft_putendl("img NULL");
	return (0);
}
//draw_scene(&e, scene);
// init GTK
app = gtk_application_new("org.gtk.example", G_APPLICATION_FLAGS_NONE);
//g_signal_connect(app, "activate", G_CALLBACK(activate), e.img);
status = g_application_run(G_APPLICATION(app), 0, NULL);
g_object_unref(app);
//
//free_node_list(&(scene->objects));
//free_node_list(&(scene->lights));
//free(scene);
return (status);
}
*/

#include <sys/wait.h>
#define APP_ID "RT.test"
/*
   static void	gtk_exit(GtkApplication *app, gpointer user_data)
   {
   (void)app;
   (void)user_data;
   g_print("gtk_exit()\n");
   g_application_quit(G_APPLICATION (user_data));
//g_application_quit(G_APPLICATION (app));
}

static void	draw(GtkApplication *app, gpointer user_data)
{
(void)app;
(void)user_data;
g_print("draw()\n");
}
*/

/*
   static void	activate(GtkApplication *app, gpointer user_data)
   {*/
/*
   GtkWidget	*win;
   GtkWidget	*grid;
   GtkWidget	*btn;
   (void)user_data;
   (void)app;
   g_print("activate\n");

// Init windo
win = gtk_application_window_new(app);
gtk_window_set_title(GTK_WINDOW(win), "Menu");
gtk_window_set_default_size(GTK_WINDOW(win), 200, 200);

// Init grid
grid = gtk_grid_new();

// Init button "Draw"
btn = gtk_button_new_with_label ("Draw");
gtk_grid_attach(GTK_GRID (grid), btn, 0, 0, 10, 10);
g_signal_connect(btn, "clicked", G_CALLBACK (draw), app);

// Init button "Quit"
btn = gtk_button_new_with_label ("Quit");
gtk_grid_attach(GTK_GRID (grid), btn, 0, 10, 10, 10);
g_signal_connect(btn, "clicked", G_CALLBACK (gtk_exit), app);

// Init combo box


gtk_container_add (GTK_CONTAINER (win), grid);
//gtk_container_add (GTK_CONTAINER (win), img);
gtk_widget_show_all(win);
*/
//}

static void btn_click_quit(GtkApplication *app, gpointer user_data)
{
	(void)app;
	(void)user_data;
	g_print("btn_click_quit()\n");
	gtk_main_quit();
}

static void btn_click_draw(GtkApplication *app, gpointer user_data)
{
	(void)app;
	(void)user_data;
	g_print("btn_click_draw()\n");
}

int		main(void)
{
	GtkWidget	*win;
	GtkWidget	*grid;
	GtkWidget	*btn;

	gtk_init(NULL, NULL);

	// Init window
	win = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title (GTK_WINDOW (win), "RT with gtk+");
	gtk_window_set_resizable (GTK_WINDOW (win), 0);
	gtk_window_set_default_size (GTK_WINDOW (win), 640, 480);

	// Init grid
	grid = gtk_grid_new();
	gtk_container_add(GTK_CONTAINER (win), grid);

	// Init button "Draw"
	btn = gtk_button_new_with_label("Draw");
	gtk_grid_attach(GTK_GRID (grid), btn, 0, 0, 10, 10);
	g_signal_connect(btn, "clicked", G_CALLBACK (btn_click_draw), NULL);


	// Init button "Quit"
	btn = gtk_button_new_with_label("Quit");
	gtk_grid_attach(GTK_GRID (grid), btn, 0, 10, 10, 10);
	g_signal_connect(btn, "clicked", G_CALLBACK (btn_click_quit), NULL);

	gtk_widget_show_all(win);
	gtk_main();
	return (0);
}
