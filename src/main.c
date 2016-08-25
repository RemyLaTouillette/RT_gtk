/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sduprey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/07 00:15:41 by sduprey           #+#    #+#             */
/*   Updated: 2016/08/25 14:16:46 by nbelouni         ###   ########.fr       */
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

typedef struct	s_ui
{
	GtkWidget	*win;
	GtkWidget	*grid;
	GtkWidget	*frame;
	GtkWidget	*btn_draw;
	GtkWidget	*btn_quit;
	GtkWidget	*lst_scenes;
	GtkWidget	*radio1;
	GtkWidget	*radio2;
	GtkWidget	*btn_color;
	GtkWidget	*check1;
	GtkWidget	*scale;
	GtkWidget	*progress;
	GtkWidget	*img;
}				t_ui;

static void click_quit(GtkApplication *app, gpointer user_data)
{
	(void)app;
	(void)user_data;
	g_print("btn_click_quit()\n");
	gtk_main_quit();
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

static void click_draw(GtkApplication *app, gpointer user_data)
{

	t_scene		*s;
	GdkPixbuf	*pixbuf;
	t_env		*e;
	t_thread	threads[N_THREAD];
	int			i;
	GObject		*o;

	g_print("btn_click_draw()\n");
	e = user_data;
	if (!(s = parse("scenes/test_cartoon")))
		printf("No scene\n");
	else
	{
		write_scene(*s);
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

	
	o = gtk_builder_get_object(e->builder, "btn_draw");
	gtk_widget_set_sensitive (GTK_WIDGET(o), FALSE);

	//g_idle_add(pulse_pbar, &e);

	gtk_new_image(e->buf, WIDTH, HEIGHT);
	pixbuf = gtk_new_image(e->buf, WIDTH, HEIGHT);
	gtk_put_image_to_window(e->img, pixbuf);

	(void)app;
	(void)user_data;
}

int		main(void)
{
	//t_ui	ui;
	//GtkBuilder	*builder;
	GObject		*win;
	GObject		*v;
	GObject		*w;
	GObject			*o;
	//GObject			*img;
	//unsigned char	*buf;
	GdkPixbuf		*pixbuf;
	t_env			e;
//	t_scene			*s;


	gtk_init(NULL, NULL);
	(void)v;
	(void)w;

	(void)click_draw;

//	s = parse("scene/scene1");

	e.builder = gtk_builder_new_from_file ("./ui/builder.c.ui");
	win = gtk_builder_get_object (e.builder, "window");
	g_signal_connect (win, "destroy", G_CALLBACK (gtk_main_quit), NULL);

	e.img = gtk_builder_get_object(e.builder, "img");
	e.buf = new_image_buffer(WIDTH, HEIGHT);
	pixbuf = gtk_new_image(e.buf, WIDTH, HEIGHT);
	gtk_put_image_to_window(GTK_IMAGE(e.img), pixbuf);

	o = gtk_builder_get_object(e.builder, "btn_draw");
	g_signal_connect(o, "clicked", G_CALLBACK(click_draw), &e);

	o = gtk_builder_get_object(e.builder, "btn_quit");
	g_signal_connect(o, "clicked", G_CALLBACK(click_quit), &e);


	//o = gtk_builder_get_object(e.builder, "pbar");
	//gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(o), 0.0);
	//g_timeout_add(300, pulse_pbar, o);
	//printf("pouet\n");
	//gtk_progress_bar_set_pulse_step(GTK_PROGRESS_BAR(o), 0.0);
	//gtk_progress_bar_pulse(GTK_PROGRESS_BAR(o));
	/*
	int i;
	double j;
	i = 0;
	while (i < 100)
	{
		j = (double)i / (double)100;
		gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(o), j);
		printf("i=%f\n", j);
		i++;
		//sleep(1);
	}
*/
/*
	double step;
	double new_val;

	step = gtk_progress_bar_get_fraction(GTK_PROGRESS_BAR(o));
	//gtk_progress_bar_pulse(GTK_PROGRESS_BAR(o));

	new_val = 0.0;//step + 0.1;

	gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(o), new_val);
	//step = gtk_progress_bar_get_pulse_step(GTK_PROGRESS_BAR(o));
	//printf("fraction = %f\n", step);
	
	//gtk_progress_bar_pulse(GTK_PROGRESS_BAR(o));
	//step = gtk_progress_bar_get_pulse_step(GTK_PROGRESS_BAR(o));
	//printf("fraction = %f\n", step);
*/	

/*
	// Set combo box text
	w = gtk_builder_get_object(builder, "lst_scenes");
	gtk_combo_box_text_append (GTK_COMBO_BOX_TEXT(w), "s1", "Scene 1");
	gtk_combo_box_text_append (GTK_COMBO_BOX_TEXT(w), "s2", "Scene 2");
	gtk_combo_box_text_append (GTK_COMBO_BOX_TEXT(w), "s3", "Scene 3");
	gtk_combo_box_set_active_id (GTK_COMBO_BOX(w), "s1");
	
	v = gtk_builder_get_object(builder, "radio1");

	w = gtk_builder_get_object(builder, "radio2");
	gtk_radio_button_join_group (GTK_RADIO_BUTTON(v), NULL);
	gtk_radio_button_join_group (GTK_RADIO_BUTTON(w), GTK_RADIO_BUTTON(v));
	//gtk_widget_set_visible (GTK_WIDGET(v), 1);
*/

	/*
	// Init window
	ui.win = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title (GTK_WINDOW (ui.win), "RT with gtk+");
	gtk_window_set_resizable (GTK_WINDOW (ui.win), 0);
	gtk_window_set_default_size (GTK_WINDOW (ui.win), 640, 480);

	// Init grid
	ui.grid = gtk_grid_new();
	gtk_container_add(GTK_CONTAINER (ui.win), ui.grid);

	// Init frame
	ui.frame = gtk_frame_new("Settings");
	gtk_grid_attach(GTK_GRID(ui.grid), ui.frame, 0, 0, 10, 10);

	// Init button "Draw"
	ui.btn_draw = gtk_button_new_with_label("Draw");
	//gtk_grid_attach(GTK_GRID (ui.grid), ui.btn_draw, 0, 0, 10, 10);
	gtk_container_add(GTK_CONTAINER(ui.frame), ui.btn_draw);
	g_signal_connect(ui.btn_draw, "clicked", G_CALLBACK (click_draw), NULL);

	// Init button "Quit"
	ui.btn_quit = gtk_button_new_with_label("Quit");
	//gtk_grid_attach(GTK_GRID (ui.grid), ui.btn_quit, 0, 10, 10, 10);
	g_signal_connect(ui.btn_quit, "clicked", G_CALLBACK (click_quit), NULL);
	gtk_container_add(GTK_CONTAINER(ui.frame), ui.btn_quit);

	// Init combo box text "Scenes"
	ui.lst_scenes = gtk_combo_box_text_new();
	gtk_combo_box_text_append (GTK_COMBO_BOX_TEXT(ui.lst_scenes), "s1", "Scene 1");
	gtk_combo_box_text_append (GTK_COMBO_BOX_TEXT(ui.lst_scenes), "s2", "Scene 2");
	gtk_combo_box_text_append (GTK_COMBO_BOX_TEXT(ui.lst_scenes), "s3", "Scene 3");
	gtk_combo_box_set_active_id (GTK_COMBO_BOX(ui.lst_scenes), "s1");
	//gtk_grid_attach(GTK_GRID (ui.grid), ui.lst_scenes, 0, 90, 10, 10);

	// Init radio buttons
	ui.radio1 = gtk_radio_button_new_with_label (NULL, "Hum ...");
	ui.radio2 = gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON(ui.radio1), "Yeah !");
	//gtk_grid_attach(GTK_GRID (ui.grid), ui.radio1, 0, 100, 10, 10);
	//gtk_grid_attach(GTK_GRID (ui.grid), ui.radio2, 0, 110, 10, 10);

	// Init color button
	ui.btn_color = gtk_color_button_new ();
	//gtk_grid_attach(GTK_GRID (ui.grid), ui.btn_color, 0, 120, 10, 10);

	// init check button
	ui.check1 = gtk_check_button_new_with_label ("Heu ...");
	//gtk_grid_attach(GTK_GRID (ui.grid), ui.check1, 0, 130, 10, 10);

	// Init scale
	ui.scale = gtk_scale_new (GTK_ORIENTATION_HORIZONTAL,
			gtk_adjustment_new (0, -10, 10, 1, 1, 1));
	//gtk_grid_attach(GTK_GRID (ui.grid), ui.scale, 0, 140, 10, 10);

	// Init progress bar
	ui.progress = gtk_progress_bar_new ();
	//gtk_grid_attach(GTK_GRID (ui.grid), ui.progress, 0, 150, 10, 10);
	gtk_progress_bar_pulse (GTK_PROGRESS_BAR(ui.progress));

	GdkPixbuf		*pixbuf;
	unsigned char	*buf;

	ui.img = gtk_image_new();
	buf = new_image_buffer(WIDTH, HEIGHT);
	pixbuf = gtk_new_image(buf, WIDTH, HEIGHT);
	gtk_put_image_to_window(GTK_IMAGE(ui.img), pixbuf);
	gtk_grid_attach(GTK_GRID (ui.grid), ui.img, 150, 0, 10, 10);
	*/

	//
	gtk_main();
	return (0);
}
