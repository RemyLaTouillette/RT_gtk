/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sduprey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/20 16:17:52 by sduprey           #+#    #+#             */
/*   Updated: 2016/10/04 14:27:34 by tlepeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

#include <unistd.h>

char	*join(char *s1, char *s2, char *s3)
{
	char	*tmp;
	char	*new;

	if (!(tmp = ft_strjoin(s1, s2)))
		return (NULL);
	if (!(new = ft_strjoin(tmp, s3)))
		return (NULL);
	free(tmp);
	return (new);
}

void	critical_error(t_error *err)
{
	ft_putendl(err->msg);
	exit(0);
}

void	common_error(t_error *err)
{
	GtkBuilder	*builder;
	GObject		*win_err;
	GObject		*btn_ok;
	GObject		*msg;

	builder = gtk_builder_new_from_file("ui/builder.error.ui");
	win_err = gtk_builder_get_object(builder, "win_err");
	gtk_window_set_position(GTK_WINDOW(win_err), GTK_WIN_POS_CENTER);
	gtk_window_set_default_size(GTK_WINDOW(win_err), 200, 200);
	msg = gtk_builder_get_object(builder, "lbl_msg");
	gtk_label_set_text(GTK_LABEL(msg), err->msg);
	btn_ok = gtk_builder_get_object(builder, "btn_ok");
	g_signal_connect_swapped(btn_ok, "clicked",
			G_CALLBACK(gtk_widget_destroy), win_err);
	gtk_widget_show_all(GTK_WIDGET(win_err));
}

void	print_error(char *msg, int crit)
{
	t_error *err;

	err = (t_error *)malloc(sizeof(t_error));
	err->crit = crit;
	err->msg = msg;
	if (crit == 0)
		critical_error(err);
	else
		common_error(err);
	free(err);
}
