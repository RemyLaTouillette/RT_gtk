/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_init.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlepeche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/14 18:22:50 by tlepeche          #+#    #+#             */
/*   Updated: 2016/09/14 18:28:40 by tlepeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _UI_INIT_H
# define _UI_INIT_H

GdkPixbuf	*gtk_new_image(unsigned char *data, int width, int height);
int			gtk_put_image_to_window(GtkImage *image, GdkPixbuf *pixbuf);
void		click_draw(GtkApplication *app, gpointer user_data);
void		click_save(GtkApplication *app, gpointer user_data);
void		click_quit(GtkApplication *app, gpointer user_data);
char		**scene_finder(char *path);

#endif
