/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_draw.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sduprey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/21 19:20:54 by sduprey           #+#    #+#             */
/*   Updated: 2016/09/22 17:07:35 by sduprey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

// PROTO QUI N'ONT RIEN A FOUTTRE LA
void	init_threads(t_thread *t, t_scene *s, t_env *e);
double	**create_tab_noise(void);
void	save_jpeg(unsigned char *data);
void	check_scene(t_env *e);


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
		exit(0);
	s2 = parse("scenes/test_cyl");
	if (!(s = parse(sname)))
		print_error("No scene", 0);
	else
	{
		draw_image(e, s);
		mount_image(e, s);
	}
}


