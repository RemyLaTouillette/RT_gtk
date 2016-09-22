/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_draw.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sduprey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/21 19:20:54 by sduprey           #+#    #+#             */
/*   Updated: 2016/09/22 18:13:47 by tlepeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

void			draw_image(t_env *e, t_scene *s)
{
	t_thread	threads[N_THREAD];
	int			i;

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

void			mount_image(t_env *e, t_scene *s)
{
	GdkPixbuf	*pixbuf;

	pixbuf = NULL;
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
}

void			check_scene(t_env *e)
{
	t_scene		*s;
	t_scene		*s2;
	char		*sname;

	sname = ft_strjoin("scenes/", get_scene_name(e));
	if (!(e->tab_noise = create_tab_noise()))
		print_error("Noise loading error", 1);
	if (!(e->texture.picture = get_texture()))
		print_error("Texture loading error", 1);
	s2 = parse("scenes/test_cyl");
	if (!(s = parse(sname)))
		print_error("No scene", 0);
	else
	{
		draw_image(e, s);
		mount_image(e, s);
	}
}
