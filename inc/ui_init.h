/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_init.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlepeche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/14 18:22:50 by tlepeche          #+#    #+#             */
/*   Updated: 2016/09/20 19:37:59 by sduprey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _UI_INIT_H
# define _UI_INIT_H

GdkPixbuf	*gtk_new_image(unsigned char *data);
int			gtk_put_image_to_window(GtkImage *image, GdkPixbuf *pixbuf);
void		click_draw(GtkApplication *app, gpointer user_data);
void		click_save(GtkApplication *app, gpointer user_data);
void		click_quit(GtkApplication *app, gpointer user_data);
int			get_switch_state(t_env *e, char *str);
char		**scene_finder(char *path);


t_vec		get_cam_pos_from_ui(t_env *e);
t_vec		get_cam_dir_from_ui(t_env *e);
int			get_switch_state(t_env *e, char *widget);
char		*get_scene_name(t_env *e);
void		set_values_from_ui(t_env *e, t_scene *s);
double		get_range_value(t_env *e, char *widget);
t_color		get_rgba(t_env *e);

void		test_error(void);

#endif
