/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/08 03:49:13 by nbelouni          #+#    #+#             */
/*   Updated: 2016/09/28 17:40:15 by tlepeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

static inline void	apply_texture(t_ray *st, t_text *t, t_hit *pxl, t_color *c)
{
	t_vec	tmp;

	*c = pxl->color;
	if (pxl->bool == 1)
	{
		if (pxl->texture == MARBLE)
			mult_color(&pxl->color, t->noise / 255);
		tmp = vec_add(st->pos, scalar_product(st->dir, pxl->t));
		if (pxl->texture == CHECKER)
			pxl->color = checkerboard(pxl->color, tmp);
		if (pxl->texture == TEXTURE && pxl->type == SPHERE && pxl->opacity == 1)
		{
			pxl->color = colortexture(pxl->color, vec_sub(pxl->pos, tmp),
					t->texture, pxl->dist_from_center);
			mult_color(&pxl->color, (double)(1.0 / 255));
		}
	}
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

static inline int	hit_color(t_scene *s, t_ray *st, t_hit *hit, double *t)
{
	if (s->is_real == CARTOON && is_black_edge(hit))
	{
		init_color(&(hit->color), 0, 0, 0);
		return (0);
	}
	else
	{
		hit->color = apply_light(s, hit, st);
		mult_color(&hit->color, t[2]);
		return (1);
	}
}

static inline void	refraction(t_scene *s, t_ray *st, t_text *text, t_hit *hit)
{
	t_color	tmp_color;

	if (hit->opacity < 1.0)
	{
		tmp_color = apply_refraction(st, s, hit, text);
		add_color(&hit->color, &tmp_color);
	}
}

t_color				color_render(t_scene *s, t_ray *st, t_text *t, double *blur)
{
	t_color	clr[2];
	t_hit	pxl;
	double	tmp[3];

	tmp[0] = t->noise;
	tmp[1] = -1;
	init_color(&clr[0], 0, 0, 0);
	while (++tmp[1] < (int)(s->reflection))
	{
		if ((int)tmp[1] == 0 || pxl.reflection != 0)
		{
			tmp[2] = pow(pxl.reflection, (int)tmp[1] * 3);
			find_closest_object(s->objects, st, &pxl);
			apply_texture(st, t, &pxl, &clr[1]);
			if (pxl.bool == 1 && hit_color(s, st, &pxl, tmp) == 1)
				refraction(s, st, t, &pxl);
			if (pxl.bool == 1 && blur && (int)tmp[1] == 0)
				find_blur_dist(st, &pxl, &s->cam, blur);
			if (pxl.bool == 0)
				break ;
			finish_loop(s, st, &pxl, clr);
		}
		test_blur((int)tmp[1], &pxl, blur);
	}
	return ((s->is_real == CARTOON) ? cartoon(&clr[0]) : clr[0]);
}
