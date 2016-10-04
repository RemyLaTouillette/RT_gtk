/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_draw.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sduprey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/21 19:20:54 by sduprey           #+#    #+#             */
/*   Updated: 2016/10/04 16:32:52 by tlepeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

t_scene				*singleton(t_scene *s)
{
	static t_scene *prev;

	if (s != NULL && prev != NULL)
	{
		free_scene(&prev);
		prev = s;
	}
	if (s != NULL && prev == NULL)
		prev = s;
	return (prev);
}

void				draw_image(t_env *e)
{
	t_thread		threads[N_THREAD];
	int				i;

	init_threads(threads, e);
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

void				mount_image(t_env *e, t_scene *s)
{
	GdkPixbuf		*pixbuf;
	int				i;

	pixbuf = NULL;
	if (s->filter == NONE && s->blur == 0.0 && s->is_dof == 0 && s->aa == 0)
	{
		pixbuf = gtk_new_image(e->buf);
		gtk_put_image_to_window(e->img, pixbuf);
	}
	else
	{
		i = -1;
		while (++i < WIDTH * HEIGHT)
			e->s->blur_array[i] = e->blur_array[i];
		threads_effects(e);
		pixbuf = gtk_new_image(e->buf_tmp);
		gtk_put_image_to_window(e->img, pixbuf);
		if (e->buf_tmp)
		{
			free(e->buf_tmp);
			e->buf_tmp = NULL;
		}
	}
}

static inline void	draw(t_env *e, t_scene *s2)
{
	int	i;

	i = 0;
	set_values_from_ui(e, 1);
	if (scene_cmp(e->s, s2) == 0)
	{
		draw_image(e);
		i = -1;
		while (++i < WIDTH * HEIGHT)
			e->blur_array[i] = e->s->blur_array[i];
	}
	mount_image(e, e->s);
}

void				check_scene(t_env *e)
{
	t_scene			*s2;
	char			*sname;
	char			*tmp;

	e->s = NULL;
	tmp = get_scene_name(e);
	sname = ft_strjoin("scenes/", tmp);
	s2 = singleton(NULL);
	free(tmp);
	if (!(e->s = parse(sname)))
		print_error("No scene", 2);
	else
	{
		draw(e, s2);
		s2 = singleton(e->s);
	}
	free(sname);
}
