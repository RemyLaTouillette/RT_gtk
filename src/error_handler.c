/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sduprey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/20 16:17:52 by sduprey           #+#    #+#             */
/*   Updated: 2016/09/21 16:03:34 by sduprey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

typedef struct	s_error
{
	int	nbr; // numero de l'error : pour faire pro :)
	int	crit; // criticite de l'erreur : 1 on quitte l'app, 0 on quitte pas
	char	*src; // source de l'erreur  (parser, initialisation, ...)
	char	*msg; // message de l'erreur;
}		t_error;

void	print_hello(GtkWidget *w, gpointer data)
{
	t_error	*err;

	(void)w;
	err = data;
	g_print("Hello error: %d\n", err->crit);
	if (err->crit == 1)
		gtk_main_quit();
}

void	test_error(/*t_error *err*/)
{
	t_error		*err;
	GtkWidget	*win_err;
	GtkWidget	*btn_ok;
	GtkWidget	*btn_box;
	GtkWidget	*src;
	GtkWidget	*msg;

	g_print("test_error()\n");
	// ERROR (tmp) n'a rien a foutre la
	err = (t_error *)malloc(sizeof(t_error));
	err->nbr = 575;
	err->crit = 0;
	err->src = ft_strdup(ft_strjoin("Hello error: ", ft_itoa(err->nbr)));
	err->msg = ft_strdup("This is an error :( Don't panic !");
	// WINDOW
	win_err = gtk_window_new(GTK_WINDOW_POPUP);
	gtk_window_set_title(GTK_WINDOW(win_err), "Error");
	gtk_window_set_position (GTK_WINDOW(win_err), GTK_WIN_POS_CENTER);
	gtk_window_set_default_size (GTK_WINDOW (win_err), 200, 200);
	// BUTTON BOX (tmp)
	btn_box = gtk_button_box_new (GTK_ORIENTATION_VERTICAL);
	gtk_container_add (GTK_CONTAINER (win_err), btn_box);
	// LABELS (src, msg)
	src = gtk_label_new(err->src);
	msg = gtk_label_new(err->msg);
	// BUTTON
	btn_ok = gtk_button_new_with_label("Ok");
	// SIGNALS CONNECT
	g_signal_connect (btn_ok, "clicked", G_CALLBACK (print_hello), err);
	g_signal_connect_swapped (btn_ok, "clicked", G_CALLBACK (gtk_widget_destroy), win_err);
	// ADD WIDGETS ON WINDOW
	gtk_container_add (GTK_CONTAINER (btn_box), src);
	gtk_container_add (GTK_CONTAINER (btn_box), msg);
	gtk_container_add (GTK_CONTAINER (btn_box), btn_ok);
	//
	//gtk_window_set_transient_for (GTK_WINDOW(win_err), NULL);
	gtk_window_set_modal (GTK_WINDOW (win_err), TRUE);
	// SHOW WINDOW
	gtk_widget_show_all(win_err);
}
