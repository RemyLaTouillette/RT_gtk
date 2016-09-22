/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_draw.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sduprey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/21 19:20:54 by sduprey           #+#    #+#             */
/*   Updated: 2016/09/22 19:28:10 by sduprey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

void			draw_image(t_env *e, t_scene *s)
{
	t_thread	threads[N_THREAD];
	int			i;

	init_threads(threads, s, e);
	i = -1;
	while (++i < N_THREAD)
	{
		if (pthread_create(&(threads[i].pth), NULL, draw_scene,
					&threads[i]) != 0)
			print_error("Creating threads failed", 1);
	}
	i = -1;
	while (++i < N_THREAD)
	{
		if (pthread_join(threads[i].pth, NULL) != 0)
			print_error("Joining threads failed", 1);
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
		pixbuf = gtk_new_image(e->buf);
	gtk_put_image_to_window(e->img, pixbuf);
}

t_scene			*singleton(t_scene *s)
{
	static t_scene *prev;

	if (s != NULL && prev != NULL)
		*prev = *s;
	if (s != NULL && prev == NULL)
	{
		prev = (t_scene *)malloc(sizeof(t_scene));
		*prev = *s;
	}
	return (prev);
}

void			check_scene(t_env *e)
{
	t_scene		*s;
	t_scene		*s2;
	char		*sname;

	s2 = NULL;
	s = NULL;
	sname = ft_strjoin("scenes/", get_scene_name(e));
	if (!(e->tab_noise = create_tab_noise()))
		print_error("Noise loading error", 1);
	if (!(e->texture.picture = get_texture()))
		print_error("Texture loading error", 1);
	s2 = singleton(s);
	if (!(s = parse(sname)))
		print_error("No scene", 0);
	else
	{
		set_values_from_ui(e, s);
		if (scene_cmp(s, s2) == 0)
			draw_image(e, s);
		if ((s2 != NULL && s->filter != s2->filter) || s2 == NULL)
			mount_image(e, s);
	}
	s2 = singleton(s);
	free(s);
}
