/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_draw.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sduprey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/21 19:20:54 by sduprey           #+#    #+#             */
/*   Updated: 2016/09/29 19:51:44 by sduprey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

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

	pixbuf = NULL;
	if (s->filter == NONE && s->blur == 0.0 && s->is_dof == 0)
	{
		pixbuf = gtk_new_image(e->buf);
		gtk_put_image_to_window(e->img, pixbuf);
	}
	else
	{
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

t_scene				*singleton(t_scene *s)
{
	static t_scene *prev;

	if (s != NULL && prev != NULL)
	{
		free_scene(&prev);
		prev = s;
	}
	if (s != NULL && prev == NULL)
	{
		prev = s;
	}
	return (prev);
}

void				check_redraw(t_env *e, t_scene *s2)
{
	set_values_from_ui(e);
	if (scene_cmp(e->s, s2) == 0)
	{
		draw_image(e);
		mount_image(e, e->s);
	}
	else
		mount_image(e, e->s);
	s2 = singleton(e->s);
	//	g_object_unref(e->texture.picture);
	//	free_tabi(e->tab_noise, HEIGHT);
}

void				check_scene(t_env *e)
{
	t_scene			*s2;
	char			*sname;
	char			*tmp;

	s2 = NULL;
	e->s = NULL;
	tmp = get_scene_name(e);
	sname = ft_strjoin("scenes/", tmp);
	free(tmp);
	s2 = singleton(e->s);
	if (!(e->s = parse(sname)))
		print_error("No scene", 2);
	else
		check_redraw(e, s2);
	free(sname);
}
