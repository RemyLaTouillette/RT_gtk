/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sduprey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/07 00:15:41 by sduprey           #+#    #+#             */
/*   Updated: 2016/09/28 19:58:24 by sduprey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>
#include <image_buffer.h>

double			**create_tab_noise(void)
{
	int			x;
	int			y;
	double		**tab;

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

GdkPixbuf		*gtk_new_image(unsigned char *data)
{
	GdkPixbuf	*pixbuf;
	GBytes		*buffer;

	buffer = NULL;
	pixbuf = NULL;
	buffer = g_bytes_new(data, WIDTH * HEIGHT * 3);
	pixbuf = gdk_pixbuf_new_from_bytes(buffer, GDK_COLORSPACE_RGB, 0, 8,
			WIDTH, HEIGHT, 3 * WIDTH);
	if (!pixbuf)
		return (NULL);
	g_bytes_unref(buffer);
	buffer = NULL;
	return (pixbuf);
}

int				gtk_put_image_to_window(GtkImage *image, GdkPixbuf *pixbuf)
{
	gtk_image_clear(image);
	gtk_image_set_from_pixbuf(image, pixbuf);
	return (1);
}

void			init_threads(t_thread *threads, t_env *e)
{
	int			i;
	t_pthread	pth[N_THREAD];
	t_mutex		mutex;

	pthread_mutex_init(&mutex, NULL);
	i = -1;
	while (++i < N_THREAD)
	{
		threads[i].scene = e->s;
		threads[i].buf = e->buf;
		threads[i].buf_tmp = e->buf_tmp;
		threads[i].env = e;
		threads[i].y_start = (WIDTH / N_THREAD) * i;
		threads[i].y_end = (WIDTH / N_THREAD) * (i + 1);
		threads[i].pth = pth[i];
		threads[i].mutex = &mutex;
	}
}

int				main(void)
{
	t_env		e;

	ui_init(&e);
	gtk_main();
	return (0);
}
