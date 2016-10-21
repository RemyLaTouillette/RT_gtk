/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlepeche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/14 18:22:22 by tlepeche          #+#    #+#             */
/*   Updated: 2016/10/21 16:30:35 by tlepeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>
#include <ui_init.h>

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
		free_tab(scenes);
	}
}

void			ui_init_callback(t_env *e)
{
	GObject		*o;

	o = gtk_builder_get_object(e->builder, "window");
	g_signal_connect(o, "destroy", G_CALLBACK(gtk_main_quit), NULL);
	o = gtk_builder_get_object(e->builder, "btn_draw");
	g_signal_connect(o, "clicked", G_CALLBACK(click_draw), e);
	o = gtk_builder_get_object(e->builder, "btn_quit");
	g_signal_connect(o, "clicked", G_CALLBACK(gtk_main_quit), e);
	o = gtk_builder_get_object(e->builder, "btn_save");
	g_signal_connect(o, "clicked", G_CALLBACK(click_save), e);
	o = gtk_builder_get_object(e->builder, "btn_save2");
	g_signal_connect(o, "clicked", G_CALLBACK(click_save2), e);
	o = gtk_builder_get_object(e->builder, "switch_modif");
	g_signal_connect(o, "state_set", G_CALLBACK(click_switch), e);
	o = gtk_builder_get_object(e->builder, "btn_filter");
	g_signal_connect(o, "clicked", G_CALLBACK(click_filter), e);
}

double			*ui_init_array(void)
{
	int		i;
	double	*tab;

	if (!(tab = (double *)malloc(sizeof(double) * WIDTH * HEIGHT)))
		return (NULL);
	i = 0;
	while (i < WIDTH * HEIGHT)
	{
		tab[i] = 0.0;
		i++;
	}
	return (tab);
}

void			ui_init(t_env *e)
{
	gtk_init(NULL, NULL);
	e->builder = gtk_builder_new();
	if (gtk_builder_add_from_file(e->builder, "ui/builder.ui", NULL) != 1)
		print_error("Error: builder not found", 0);
	e->win = gtk_builder_get_object(e->builder, "window");
	ui_init_img(e);
	ui_init_scenes(e, "scenes");
	ui_init_callback(e);
	if (!(e->tab_noise = create_tab_noise()))
		print_error("Noise loading error", 0);
	if (!(e->texture.picture = get_texture()))
		print_error("Texture loading error", 0);
	if (!(e->blur_array = ui_init_array()))
		print_error("UI initialisation error", 0);
	e->s = NULL;
}
