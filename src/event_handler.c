/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sduprey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/21 18:34:19 by sduprey           #+#    #+#             */
/*   Updated: 2016/09/21 18:47:25 by sduprey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

// PROTO QUI N'ONT RIEN A FOUTTRE LA
void	init_threads(t_thread *t, t_scene *s, t_env *e);
double	**create_tab_noise(void);

void click_quit(GtkApplication *app, gpointer user_data)
{
	(void)app;
	(void)user_data;
	gtk_main_quit();
}

void	click_save(GtkApplication *app, gpointer user_data)
{
	t_env	*e;

	(void)app;
	e = user_data;
	save_bmp2(e->buf);
//	save_bmp(e->buf);
// FONCTION TEST POUR POPUP ERROR
//	test_error();
}

void click_draw(GtkApplication *app, gpointer user_data)
{
	t_scene		*s;
	t_scene		*s2;
	GdkPixbuf	*pixbuf;
	t_env		*e;
	t_thread	threads[N_THREAD];
	int			i;
	char		*sname;

	e = user_data;
	sname = ft_strjoin("scenes/", get_scene_name(e));
	if (!(e->tab_noise = create_tab_noise()))
		exit(0);
	s2 = parse("scenes/test_cyl");
	if (!(s = parse(sname)))
		ft_putendl("No scene\n");
	else
	{
		set_values_from_ui(e, s);
		init_threads(threads, s, e);
		i = -1;
		while (++i < N_THREAD)
		{
			if (pthread_create(&(threads[i].pth), NULL, draw_scene, &threads[i]) != 0)
			{
				ft_putendl("Creating threads failed\n");
				exit(0);
			}
		}
		i = -1;
		while (++i < N_THREAD)
		{
			if (pthread_join(threads[i].pth, NULL) != 0)
			{
				ft_putendl("Joining threads failed\n");
				exit(0);
			}
		}
	}
	gtk_new_image(e->buf);
	if (s->filter != NONE)
	{
		e->buf_tmp = sepia_filter(e->buf, s->filter);
		pixbuf = gtk_new_image(e->buf_tmp);
	}
	else
	{
		pixbuf = gtk_new_image(e->buf);
	}
	gtk_put_image_to_window(e->img, pixbuf);
	free(s);
	(void)app;
}
