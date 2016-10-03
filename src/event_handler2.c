/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handler2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlepeche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/03 19:15:13 by tlepeche          #+#    #+#             */
/*   Updated: 2016/10/03 19:15:27 by tlepeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

void			click_save(GtkApplication *app, gpointer user_data)
{
	t_env		*e;

	(void)app;
	e = user_data;
	save_jpeg(e->buf);
}

void			click_save2(GtkApplication *app, gpointer data)
{
	t_env		*e;

	(void)app;
	e = data;
	save_bmp(e->buf);
}
