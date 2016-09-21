/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/08 03:49:13 by nbelouni          #+#    #+#             */
/*   Updated: 2016/09/21 16:00:21 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

static inline void	ray_tracing(t_ray *start, t_scene *s, double n, t_hit *pxl)
{
	t_vec	tmp;
	t_color	tmp_color;

	if (pxl->opacity < 1.0)
	{
		tmp_color = apply_refraction(start, s, pxl, n);
		add_color(&pxl->color, &tmp_color);
	}
	if (pxl->texture == MARBLE)
		mult_color(&pxl->color, n / 255);
	if (pxl->texture == CHECKER)
	{
		tmp = vec_add(start->pos, scalar_product(start->dir, pxl->t));
		pxl->color = checkerboard(pxl->color, tmp);
	}
}

static inline void	find_blur_dist(t_ray *st, t_hit *hit, t_cam cam, t_blur *b)
{
	t_vec	tmp2;

	b->p_obj = 0;
	tmp2 = scalar_product(st->dir, hit->t);
	tmp2 = vec_add(st->pos, tmp2);
	b->t = tmp2.z;
	if (b->t == cam.ray.pos.z)
		b->t = 0;
	if (b->t > 100)
		b->t = 100;
}

static inline void	finish_loop(t_scene *s, t_ray *st, t_hit *hit, t_color *clr)
{
	double	tmp;

	if (hit->reflection != 0)
	{
		st->pos = vec_add(st->pos, scalar_product(st->dir, hit->t));
		tmp = dot_product(st->dir, hit->nml) * 2.0;
		st->dir = vec_sub(scalar_product(hit->nml, tmp), st->dir);
		st->dir = normalize(st->dir);
	}
	clr[1].r *= s->ambient_color.r * s->ambient_index;
	clr[1].g *= s->ambient_color.g * s->ambient_index;
	clr[1].b *= s->ambient_color.b * s->ambient_index;
	if (!(s->is_real == CARTOON && is_black_edge(hit)))
		add_color(&hit->color, &clr[1]);
	add_color(&clr[0], &hit->color);
}

static inline void	hit_color(t_scene *s, t_ray *st, t_hit *hit, double *tmp)
{
	double	reflet;

	if (s->is_real == CARTOON && is_black_edge(hit))
		init_color(&(hit->color), 0, 0, 0);
	else
	{
		reflet = pow(hit->reflection, (int)tmp[1] * 3);
		hit->color = apply_light(s, hit, st);
		mult_color(&hit->color, reflet);
		ray_tracing(st, s, tmp[0], hit);
	}
}

t_color				color_render(t_scene *s, t_ray *st, double n, t_blur *blur)
{
	t_color	clr[2];
	t_hit	pxl;
	double	tmp[2];

	tmp[0] = n;
	tmp[1] = -1;
	init_color(&clr[0], 0, 0, 0);
	while (++tmp[1] < (int)(s->reflection))
	{
		if ((int)tmp[1] == 0 || pxl.reflection != 0)
		{
			find_closest_object(s->objects, st, &pxl);
			clr[1] = pxl.color;
			if (pxl.bool == 1)
				hit_color(s, st, &pxl, tmp);
			if (pxl.bool == 1 && blur && (int)tmp[1] == 0)
				find_blur_dist(st, &pxl, s->cam, blur);
			if (pxl.bool == 0)
				break ;
			finish_loop(s, st, &pxl, clr);
		}
		test_blur((int)tmp[1], &pxl, blur);
	}
	return ((s->is_real == CARTOON) ? cartoon(&clr[0]) : clr[0]);
}
