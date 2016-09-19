/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_init.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlepeche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/14 18:22:50 by tlepeche          #+#    #+#             */
/*   Updated: 2016/09/19 21:14:57 by tlepeche         ###   ########.fr       */
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

#endif
