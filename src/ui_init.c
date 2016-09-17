/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/15 15:13:37 by nbelouni          #+#    #+#             */
/*   Updated: 2016/09/16 15:07:38 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

// proto tmp
GdkPixbuf	*gtk_new_image(unsigned char *, int, int);
int		gtk_put_image_to_window(GtkImage *, GdkPixbuf *);
void		click_draw(GtkApplication *, gpointer);
void		click_save(GtkApplication *, gpointer);
void		click_quit(GtkApplication *, gpointer);
char		**scene_finder(char *path);
//

void			ui_init_callback(t_env *e)
{
	GObject		*win;
	GObject		*btn_draw;
	GObject		*btn_save;
	GObject		*btn_quit;

	ft_putendl("ui_init_callback()");
	win = gtk_builder_get_object(e->builder, "window");
	g_signal_connect(win, "destroy", G_CALLBACK(gtk_main_quit), NULL);
	btn_draw = gtk_builder_get_object(e->builder, "btn_draw");
	g_signal_connect(btn_draw, "clicked", G_CALLBACK(click_draw), e);
	btn_quit = gtk_builder_get_object(e->builder, "btn_quit");
	g_signal_connect(btn_quit, "clicked", G_CALLBACK(click_quit), e);
	btn_save = gtk_builder_get_object(e->builder, "btn_save");
	g_signal_connect(btn_save, "clicked", G_CALLBACK(click_save), e);
}

void			ui_init_img(t_env *e)
{
	GdkPixbuf	*pixbuf;

	ft_putendl("ui_init_img()");
	e->img = gtk_builder_get_object(e->builder, "img");
	e->buf = new_image_buffer(WIDTH, HEIGHT);
	pixbuf = gtk_new_image(e->buf, WIDTH, HEIGHT);
	gtk_put_image_to_window(GTK_IMAGE(e->img), pixbuf);
}

void			ui_init_scenes(t_env *e, char *path)
{
	GObject		*o;
	char		**scenes;
	int		i;

	scenes = scene_finder(path);
	if (scenes != NULL)
	{
		o = gtk_builder_get_object(e->builder, "cmb_scene");
		i = 0;
		while (scenes[i] != NULL)
		{
			printf("%d - %s\n", i, scenes[i]);
			gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(o), scenes[i++]);
		}
	}
	// T'as pas free, t'as rien compris ... ((char **)scenes)
}

void			ui_init(t_env *e)
{
	ft_putendl("ui_init()");
	gtk_init(NULL, NULL);
	e->builder = gtk_builder_new_from_file("ui/builder.c.ui");
	// probleme de securite : gtk abort auto
	/*
	if (e->builder == NULL)
	{
		ft_putendl("Error: builder not found !");
	}
	*/
	ui_init_img(e);
	ui_init_scenes(e, "scenes");
	ui_init_callback(e);
}
