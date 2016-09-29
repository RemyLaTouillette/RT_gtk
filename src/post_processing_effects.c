/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   post_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sduprey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/28 17:42:54 by sduprey           #+#    #+#             */
/*   Updated: 2016/09/29 19:50:04 by sduprey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

void	draw_blur_effect(unsigned char *ref, t_thread *t, int size, t_iter iter)
{
	apply_blur(ref, t->buf_tmp, t->scene->blur, iter);
	ft_memcpy(ref, t->buf_tmp, size);
}

void	draw_dof_effect(unsigned char *ref, t_thread *t, int size, t_iter iter)
{
	apply_depth_of_field(ref, t->buf_tmp, t->scene, iter);
	ft_memcpy(ref, t->buf_tmp, size);
}

void	draw_filter_effect(unsigned char *ref, t_thread *t, int size, t_iter it)
{
	sepia_filter(ref, t->buf_tmp, t->scene->filter, it);
	ft_memcpy(ref, t->buf_tmp, size);
}

void	*apply_effect(void *data)
{
	unsigned char	*ref;
	t_thread		*t;
	int				size;
	t_iter			iter;

	t = ((t_thread *)(data));
	iter.i = t->y_start;
	iter.j = t->y_end;
	size = WIDTH * HEIGHT * 3;
	if (!(ref = (unsigned char *)malloc(sizeof(unsigned char) * size)))
		return (NULL);
	ft_memcpy(ref, t->buf, size);
	if (t->scene->blur > 0.0)
		draw_blur_effect(ref, t, size, iter);
	if (t->scene->is_dof == 1)
		draw_dof_effect(ref, t, size, iter);
	if (t->scene->filter)
		draw_filter_effect(ref, t, size, iter);
	free(ref);
	ref = NULL;
	return (data);
}

void	threads_effects(t_env *e)
{
	t_thread		threads[N_THREAD];
	int				i;

	e->buf_tmp = new_image_buffer();
	if (e->buf_tmp == NULL)
		return ;
	init_threads(threads, e);
	i = -1;
	while (++i < N_THREAD)
		if (pthread_create(&(threads[i].pth), NULL, apply_effect,
					&threads[i]) != 0)
			print_error("Creating threads failed", 1);
	i = -1;
	while (++i < N_THREAD)
		if (pthread_join(threads[i].pth, NULL) != 0)
			print_error("Joining threads failed", 1);
}
