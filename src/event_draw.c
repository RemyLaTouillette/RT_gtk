/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_draw.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sduprey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/21 19:20:54 by sduprey           #+#    #+#             */
/*   Updated: 2016/09/26 20:33:46 by tlepeche         ###   ########.fr       */
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

void			apply_effect(t_env *e, t_scene *s)
{
	GdkPixbuf		*pixbuf;
	unsigned char	*ref;
	
	ref = e->buf;
	pixbuf = NULL;
	g_print("filter: %d\n", s->filter);
	if (s->filter != NONE)
		e->buf_tmp = sepia_filter(ref, s->filter);
	if (s->blur > 0.0)
	{
		if (e->buf_tmp)
		{
			ref = apply_blur(e->buf_tmp, s->blur);
			free(e->buf_tmp);
			e->buf_tmp = ref;
		}
		else
			e->buf_tmp = apply_blur(ref , s->blur);
	}
	if (s->is_dof == 1)
	{
		if (e->buf_tmp)
		{
			ref = apply_depth_of_field(e->buf_tmp, s->blur_array, s->dof);
			free(e->buf_tmp);
			e->buf_tmp = ref;
		}
		else
			e->buf_tmp = apply_depth_of_field(ref , s->blur_array, s->dof);
	}
	pixbuf = gtk_new_image(e->buf_tmp);
	gtk_put_image_to_window(e->img, pixbuf);
	free(e->buf_tmp);
	e->buf_tmp = NULL;
}

void			mount_image(t_env *e, t_scene *s)
{
	GdkPixbuf	*pixbuf;
	//int			effect;

	pixbuf = NULL;
	if (s->filter == NONE && s->blur == 0.0 && s->is_dof == 0)
	{
		g_print("no effect\n");
		pixbuf = gtk_new_image(e->buf);
		gtk_put_image_to_window(e->img, pixbuf);
	}
	else
	{
		g_print("effect\n");
		apply_effect(e, s);
		/*
		   if (s->filter != NONE)
		   {
		   e->buf_tmp = sepia_filter(e->buf, s->filter);
		   pixbuf = gtk_new_image(e->buf_tmp);
		   }
		   else
		   */
	}
}

t_scene			*singleton(t_scene *s)
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

void			check_scene(t_env *e)
{
	t_scene		*s;
	t_scene		*s2;
	char		*sname;
	char		*tmp;

	s2 = NULL;
	s = NULL;

	tmp = get_scene_name(e);
	sname = ft_strjoin("scenes/", tmp);
	free(tmp);
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
		{
			draw_image(e, s);
			mount_image(e, s);
		}
		else
		{
			if ((s2 != NULL && s->filter != s2->filter) || s2 == NULL)
				mount_image(e, s);
			else if ((s2 != NULL && (s->is_dof != s2->is_dof || s->dof != s2->dof)) || s2 == NULL)
				mount_image(e, s);
			else if ((s2 != NULL && s->blur != s2->blur) || s2 == NULL)
				mount_image(e, s);
		}
		s2 = singleton(s);
		g_object_unref(e->texture.picture);
		free_tabi(e->tab_noise, HEIGHT);
		s = NULL;
	}
	free(sname);
}
