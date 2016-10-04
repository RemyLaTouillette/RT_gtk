/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   post_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sduprey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/28 17:42:54 by sduprey           #+#    #+#             */
/*   Updated: 2016/10/04 16:28:11 by tlepeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

void	choose_and_apply(unsigned char *ref, t_thread *t, int size, t_iter *it)
{
	memcpy(ref, t->buf, size);
	if (t->scene->blur > 0.0)
	{
		apply_blur(ref, t->buf_tmp, t->scene->blur, it);
		memcpy(ref, t->buf_tmp, size);
	}
	if (t->scene->is_dof == 1)
	{
		apply_depth_of_field(ref, t->buf_tmp, t->scene, it);
		memcpy(ref, t->buf_tmp, size);
	}
	if (t->scene->aa == 1)
	{
		aa(ref, t->buf_tmp, it);
		memcpy(ref, t->buf_tmp, size);
	}
	if (t->scene->filter)
	{
		sepia_filter(ref, t->buf_tmp, t->scene->filter, it);
		memcpy(ref, t->buf_tmp, size);
	}
}

void	*apply_effect(void *data)
{
	unsigned char	*ref;
	t_thread		*t;
	t_iter			iter;

	t = ((t_thread *)(data));
	iter.i = t->y_start;
	iter.j = t->y_end;
	if (!(ref = (unsigned char *)malloc(sizeof(unsigned char) *
					(WIDTH * HEIGHT * 3))))
		return (NULL);
	choose_and_apply(ref, t, WIDTH * HEIGHT * 3, &iter);
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
		print_error("Creating new image failed", 1);
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
