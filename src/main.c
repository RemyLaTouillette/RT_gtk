/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sduprey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/07 00:15:41 by sduprey           #+#    #+#             */
/*   Updated: 2016/09/20 19:21:05 by sduprey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>
#include <image_buffer.h>

double	**create_tab_noise(void)
{
	int		x;
	int		y;
	double	**tab;

	y = 0;
	if (!(tab = (double **)malloc(sizeof(double *) * HEIGHT)))
		return (NULL);
	while (y < HEIGHT)
	{
		x = 0;
		if (!(tab[y] = (double *)malloc(sizeof(double) * WIDTH)))
			return (NULL);
		while (x < WIDTH)
		{
			tab[y][x] = (rand() % 32768) / 32768.0;
			x++;
		}
		y++;
	}
	return (tab);
}

GdkPixbuf			*gtk_new_image(unsigned char *data)
{
	GdkPixbuf		*pixbuf;
	GBytes			*buffer;

	buffer = NULL;
	pixbuf = NULL;
//	int i = 0;
//	while ((int)(data[i]) < 255 && (int)(data[i]) > 0)
//	{
//		i++;
//	}
	buffer = g_bytes_new(data, WIDTH * HEIGHT * 3);
	pixbuf = gdk_pixbuf_new_from_bytes(buffer, GDK_COLORSPACE_RGB, 0, 8, WIDTH, HEIGHT, 3 * WIDTH);
	if (!pixbuf)
		return (NULL);
	g_bytes_unref(buffer);
	buffer = NULL;
	return (pixbuf);
}

int		gtk_put_image_to_window(GtkImage *image, GdkPixbuf *pixbuf)
{
	gtk_image_clear(image);
	gtk_image_set_from_pixbuf(image, pixbuf);
	return (1);
}


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
//	save_bmp(e->buf);
// FONCTION TEST POUR POPUP ERROR
	test_error();
}

void		init_threads(t_thread *threads, t_scene *scene, t_env *e)
{
	int			i;
	t_pthread	pth[N_THREAD];
	t_mutex		mutex;

	pthread_mutex_init(&mutex, NULL);
	i = -1;
	while (++i < N_THREAD)
	{
		threads[i].scene = scene;
		threads[i].buf = e->buf;
		threads[i].env = e;
		threads[i].y_start = (WIDTH / N_THREAD) * i;
		threads[i].y_end = (WIDTH / N_THREAD) * (i + 1);
		threads[i].pth = pth[i];
		threads[i].mutex = &mutex;
	}
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
	pixbuf = gtk_new_image(e->buf);
	gtk_put_image_to_window(e->img, pixbuf);
	free(s);
	(void)app;
}

int		main(void)
{
	t_env			e;

	ui_init(&e);
	gtk_main();
	return (0);
}
