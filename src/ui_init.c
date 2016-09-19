/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlepeche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/14 18:22:22 by tlepeche          #+#    #+#             */
/*   Updated: 2016/09/19 21:17:09 by tlepeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>
#include <ui_init.h>
/*
void			click_switch(GtkApplication *app, gpointer user_data)
{
	t_env		*e;
	GObject		*o;
	gboolean	state;
	gchar		*sname;
	t_scene		*s;
	GdkRGBA		*color;

	(void)app;
	e = user_data;
	g_print("click_switch()\n");
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
		g_print("get values form %s\n", sname);
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
			gtk_switch_set_state (GTK_SWITCH(o), s->is_real);
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
*/
void	ui_init_callback(t_env *e)
{
	GObject		*win;
	GObject		*btn_draw;
	GObject		*btn_save;
	GObject		*btn_quit;
//	GObject		*btn_switch;

	ft_putendl("ui_init_callback()");
	win = gtk_builder_get_object(e->builder, "window");
	g_signal_connect(win, "destroy", G_CALLBACK(gtk_main_quit), NULL);
	btn_draw = gtk_builder_get_object(e->builder, "btn_draw");
	g_signal_connect(btn_draw, "clicked", G_CALLBACK(click_draw), e);
	btn_quit = gtk_builder_get_object(e->builder, "btn_quit");
	g_signal_connect(btn_quit, "clicked", G_CALLBACK(click_quit), e);
	btn_save = gtk_builder_get_object(e->builder, "btn_save");
	g_signal_connect(btn_save, "clicked", G_CALLBACK(click_save), e);

	/*btn_switch = gtk_builder_get_object(e->builder, "btn_modif");
	g_signal_connect(btn_switch, "clicked", G_CALLBACK(click_switch), e);

	btn_switch = gtk_builder_get_object(e->builder, "cmb_scene");
	g_signal_connect(btn_switch, "changed", G_CALLBACK(click_switch), e);*/

}


void	ui_init_img(t_env *e)
{
	GdkPixbuf	*pixbuf;

	ft_putendl("ui_init_img()");
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

void	ui_init(t_env *e)
{
	ft_putendl("ui_init()");
	gtk_init(NULL, NULL);
	e->builder = gtk_builder_new_from_file("ui/builder.c.ui");
	ui_init_img(e);
	ui_init_scenes(e, "scenes");
	ui_init_callback(e);
}
