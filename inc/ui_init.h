/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_init.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlepeche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/14 18:22:50 by tlepeche          #+#    #+#             */
/*   Updated: 2016/10/04 15:55:38 by tlepeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _UI_INIT_H
# define _UI_INIT_H

GdkPixbuf	*gtk_new_image(unsigned char *data);
int			gtk_put_image_to_window(GtkImage *image, GdkPixbuf *pixbuf);
void		click_draw(GtkApplication *app, gpointer user_data);
void		click_save(GtkApplication *app, gpointer user_data);
void		click_save2(GtkApplication *app, gpointer user_data);
void		click_quit(GtkApplication *app, gpointer user_data);
void		click_switch(GtkApplication *app, gboolean boo, gpointer user_data);
void		click_filter(GtkApplication *app, gpointer user_data);

int			get_switch_state(t_env *e, char *str);
char		**scene_finder(char *path);

t_vec		get_cam_pos_from_ui(t_env *e);
t_vec		get_cam_dir_from_ui(t_env *e);
int			get_switch_state(t_env *e, char *widget);
char		*get_scene_name(t_env *e);
void		set_values_from_ui(t_env *e, int bool);
double		get_range_value(t_env *e, char *widget);
t_color		get_rgba(t_env *e);

void		test_error(t_error *err);

void		set_values_from_scene(t_env *e, t_scene *s);
void		set_cam_pos_from_scene(t_env *e, t_scene *s);
void		set_cam_dir_from_scene(t_env *e, t_scene *s);
void		set_reflection_from_scene(t_env *e, t_scene *s);
void		set_ambient_color_from_scene(t_env *e, t_scene *s);
void		set_effect_from_scene(t_env *e, t_scene *s);

int			get_filter_name(t_env *e);

#endif
