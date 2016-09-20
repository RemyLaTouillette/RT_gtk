/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlepeche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/14 18:22:22 by tlepeche          #+#    #+#             */
/*   Updated: 2016/09/20 20:14:34 by sduprey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>
#include <ui_init.h>

void			click_switch(GtkApplication *app, gpointer user_data)
{
	t_env		*e;
	GObject		*o;
	gboolean	state;
	gchar		*sname;
	t_scene		*s;
	GdkRGBA		*color;
	int			mode;

	(void)app;
	e = user_data;
	o = gtk_builder_get_object(e->builder, "btn_modif");
	state = gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (o));
	o = gtk_builder_get_object(e->builder, "frm_cam");
	gtk_widget_set_sensitive (GTK_WIDGET(o), state);
	o = gtk_builder_get_object(e->builder, "frm_effect");
	gtk_widget_set_sensitive (GTK_WIDGET(o), state);
	o = gtk_builder_get_object(e->builder, "frm_light");
	gtk_widget_set_sensitive (GTK_WIDGET(o), state);
	if (state)
	{
		o = gtk_builder_get_object(e->builder, "cmb_scene");
		sname = gtk_combo_box_text_get_active_text((GTK_COMBO_BOX_TEXT(o)));
		if ((s = parse(ft_strjoin("scenes/", sname))))
		{
			// CAM POS
			o = gtk_builder_get_object(e->builder, "scale_cam_pos_x");
			gtk_range_set_value (GTK_RANGE (o), s->cam.ray.pos.x);
			o = gtk_builder_get_object(e->builder, "scale_cam_pos_y");
			gtk_range_set_value (GTK_RANGE (o), s->cam.ray.pos.y);
			o = gtk_builder_get_object(e->builder, "scale_cam_pos_z");
			gtk_range_set_value (GTK_RANGE (o), s->cam.ray.pos.z);
			// CAM DIR
			o = gtk_builder_get_object(e->builder, "scale_cam_dir_x");
			gtk_range_set_value (GTK_RANGE (o), s->cam.ray.dir.x);
			o = gtk_builder_get_object(e->builder, "scale_cam_dir_y");
			gtk_range_set_value (GTK_RANGE (o), s->cam.ray.dir.y);
			o = gtk_builder_get_object(e->builder, "scale_cam_dir_z");
			gtk_range_set_value (GTK_RANGE (o), s->cam.ray.dir.z);
			// REFLECTION
			o = gtk_builder_get_object(e->builder, "scale_loop");
			gtk_range_set_value (GTK_RANGE (o), s->reflection);
			// AMBIENT LIGHTING
			//// COLOR
			color = (GdkRGBA *)malloc(sizeof(GdkRGBA));
			color->red = s->ambient_color.r / 255;
			color->green = s->ambient_color.g / 255;
			color->blue = s->ambient_color.b / 255;
			color->alpha = 1.0;
			o = gtk_builder_get_object(e->builder, "btn_color");
			gtk_color_chooser_set_rgba(GTK_COLOR_CHOOSER(o), color);	
			//// INDEX
			o = gtk_builder_get_object(e->builder, "scale_color");
			gtk_range_set_value(GTK_RANGE(o), s->ambient_index);
			// CARTOON
			o = gtk_builder_get_object(e->builder, "switch_cartoon");
			mode = s->is_real == 1 ? 0 : 1;
			gtk_switch_set_state (GTK_SWITCH(o), mode);
			// DOF
			o = gtk_builder_get_object(e->builder, "switch_dof");
			gtk_switch_set_state (GTK_SWITCH(o), s->is_dof);
			//// FOCUS
			o = gtk_builder_get_object(e->builder, "scale_focus");
			gtk_range_set_value(GTK_RANGE(o), s->dof);	
			//// BLUR
			o = gtk_builder_get_object(e->builder, "scale_blur");
			gtk_range_set_value(GTK_RANGE(o), s->blur);
		}
	}
}

int	get_filter_name(t_env *);

void	click_filter(GtkApplication *app, gpointer data)
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
		return;
	}
	pixbuf = gtk_new_image(e->buf_tmp);
	gtk_put_image_to_window(e->img, pixbuf);
}


void	ui_init_img(t_env *e)
{
	GdkPixbuf	*pixbuf;

	e->img = gtk_builder_get_object(e->builder, "img");
	e->buf = new_image_buffer();
	pixbuf = gtk_new_image(e->buf);
	gtk_put_image_to_window(GTK_IMAGE(e->img), pixbuf);
}

void	ui_init_scenes(t_env *e, char *path)
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
	}
	free_tab(scenes);
}

void	ui_init_callback(t_env *e)
{
	GObject		*win;
	GObject		*btn_draw;
	GObject		*btn_save;
	GObject		*btn_quit;
	GObject		*btn_switch;
	GObject		*btn_filter;

	win = gtk_builder_get_object(e->builder, "window");
	g_signal_connect(win, "destroy", G_CALLBACK(gtk_main_quit), NULL);
	btn_draw = gtk_builder_get_object(e->builder, "btn_draw");
	g_signal_connect(btn_draw, "clicked", G_CALLBACK(click_draw), e);
	btn_quit = gtk_builder_get_object(e->builder, "btn_quit");
	g_signal_connect(btn_quit, "clicked", G_CALLBACK(click_quit), e);
	btn_save = gtk_builder_get_object(e->builder, "btn_save");
	g_signal_connect(btn_save, "clicked", G_CALLBACK(click_save), e);
	btn_switch = gtk_builder_get_object(e->builder, "btn_modif");
	g_signal_connect(btn_switch, "clicked", G_CALLBACK(click_switch), e);
	btn_switch = gtk_builder_get_object(e->builder, "cmb_scene");
	g_signal_connect(btn_switch, "changed", G_CALLBACK(click_switch), e);
	btn_filter = gtk_builder_get_object(e->builder, "btn_filter");
	g_signal_connect(btn_filter, "clicked", G_CALLBACK(click_filter), e);
	
}

void	ui_init(t_env *e)
{
	gtk_init(NULL, NULL);
	e->builder = gtk_builder_new_from_file("ui/builder.ui");
	ui_init_img(e);
	ui_init_scenes(e, "scenes");
	ui_init_callback(e);
}
