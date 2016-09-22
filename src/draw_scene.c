/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/08 03:49:13 by nbelouni          #+#    #+#             */
/*   Updated: 2016/09/22 16:48:21 by tlepeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

void				test_blur(int r, t_hit *pxl, t_blur *blur)
{
	if ((r == 0 || pxl->reflection != 0) && pxl->bool == 0 && blur)
		blur->t = 100;
}

void				find_blur_dist(t_ray *st, t_hit *hit, t_cam *cam, t_blur *b)
{
	t_vec	tmp2;

	b->p_obj = 0;
	tmp2 = scalar_product(st->dir, hit->t);
	tmp2 = vec_add(st->pos, tmp2);
	b->t = tmp2.z;
	if (b->t == cam->ray.pos.z)
		b->t = 0;
	if (b->t > 100)
		b->t = 100;
}

static inline t_ray	init_start_ray(t_cam cam, int x, int y)
{
	t_ray ray;

	ray.pos = cam.ray.pos;
	ray.dir = calc_vec_dir(x, y, cam, cam.look_at);
	ray.dir = normalize(ray.dir);
	return (ray);
}

void				*draw_scene(void *data)
{
	int		x;
	int		y;
	t_ray	start;
	t_color final_color;
	t_text	texture;

	x = ((t_thread *)(data))->y_start - 1;
	while (++x < ((t_thread *)(data))->y_end)
	{
		y = -1;
		while (++y < HEIGHT)
		{
			texture.noise = apply_marble_noise(x, y, 50,
					((t_thread *)(data))->env->tab_noise);
			texture.texture = ((t_thread*)(data))->env->texture;
			start = init_start_ray(((t_thread *)(data))->scene->cam, x, y);
			final_color = color_render(((t_thread *)(data))->scene, &start,
					&texture,
					&(((t_thread*)(data))->scene->blur_array[x * HEIGHT + y]));
			put_pixel_on_buffer(((unsigned char *)(((t_thread *)(data))->buf)),
					x, y, final_color);
		}
		((t_thread *)(data))->env->x = x;
	}
	return (data);
}
