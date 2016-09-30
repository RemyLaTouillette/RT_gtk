/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_draw.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sduprey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/21 19:20:54 by sduprey           #+#    #+#             */
/*   Updated: 2016/09/30 19:20:35 by tlepeche         ###   ########.fr       */
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
	g_print("s->is_dof = %d\n", s->is_dof);
	if (s->filter == NONE && s->blur == 0.0 && s->is_dof == 0 && s->aa == 0)
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
		prev = s;
	return (prev);
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
	{
		set_values_from_ui(e);
		if (scene_cmp(e->s, s2) == 0)
			draw_image(e);
		else
		{
		//	e->s->blur_array = s2->blur_array;
		//	ligne du dessus fonctionne pas lorsque l'on clique a repetition sur 
		//	draw_scene mais probleme resolu si on fait un copie du tablo de l'ancienne
		//	scene dans la nouvelle
		}
		mount_image(e, e->s);
		s2 = singleton(e->s);
	}
	free(sname);
}
