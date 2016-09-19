/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/08 03:49:13 by nbelouni          #+#    #+#             */
/*   Updated: 2016/09/19 19:15:25 by tlepeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

void	ray_tracing(t_ray *start, t_scene *scene, double noise, t_hit *pxl)
{
	t_vec	tmp;
	t_color	tmp_color;

	if (pxl->opacity < 1.0)
	{
		tmp_color = apply_refraction(start, scene, *pxl, noise);
		pxl->color = add_color(pxl->color, tmp_color);
	}
	if (pxl->texture == MARBLE)
		pxl->color = mult_color(pxl->color, noise / 255);
	if (pxl->texture == CHECKER)
	{
		tmp = vec_add(start->pos, scalar_product(start->dir, pxl->t));
		pxl->color = checkerboard(pxl->color, tmp);
	}
}

void	find_blur_dist(t_ray *start, t_hit *hit, t_cam cam, t_blur *blur)
{
	t_vec	tmp2;

	blur->p_obj = 0;
	tmp2 = scalar_product(start->dir, hit->t);
	tmp2 = vec_add(start->pos, tmp2);
	blur->t = tmp2.z;
	if (blur->t == cam.ray.pos.z)
		blur->t = 0;
	if (blur->t > 100)
		blur->t = 100;
}

void	finish_loop(t_scene *s, t_ray *start, t_hit *hit, t_color *fnl_clr)
{
	double	tmp;

	if (hit->reflection != 0)
	{
		start->pos = vec_add(start->pos, scalar_product(start->dir, hit->t));
		tmp = dot_product(start->dir, hit->nml) * 2.0;
		start->dir = vec_sub(scalar_product(hit->nml, tmp), start->dir);
		start->dir = normalize(start->dir);
	}
	fnl_clr[1].r *= s->ambient_color.r * s->ambient_index;
	fnl_clr[1].g *= s->ambient_color.g * s->ambient_index;
	fnl_clr[1].b *= s->ambient_color.b * s->ambient_index;
	if (!(s->is_real == CARTOON && is_black_edge(hit)))
		hit->color = add_color(hit->color, fnl_clr[1]);
	fnl_clr[0] = add_color(fnl_clr[0], hit->color);
}

void	complete_hit_color(t_scene *s, t_ray *start, t_hit *hit, double *tmp)
{
	double	reflet;

	if (s->is_real == CARTOON && is_black_edge(hit))
		hit->color = init_color(0, 0, 0);
	else
	{
		reflet = pow(hit->reflection, (int)tmp[1] * 3);
		hit->color = apply_light(s, *hit, start);
		hit->color = mult_color(hit->color, reflet);
		ray_tracing(start, s, tmp[0], hit);
	}
}

t_color	color_render(t_scene *scene, t_ray *start, double noise, t_blur *blur)
{
	t_color	clr[2];
	t_hit	pxl;
	double	tmp[2];

	tmp[0] = noise;
	tmp[1] = -1;
	clr[0] = init_color(0, 0, 0);
	while (++tmp[1] < (int)(scene->reflection))
	{
		if ((int)tmp[1] == 0 || pxl.reflection != 0)
		{
			pxl = find_closest_object(scene->objects, start);
			clr[1] = pxl.color;
			if (pxl.bool == 1)
				complete_hit_color(scene, start, &pxl, tmp);
			if (pxl.bool == 1 && blur && (int)tmp[1] == 0)
				find_blur_dist(start, &pxl, scene->cam, blur);
			if (pxl.bool == 0)
				break ;
			finish_loop(scene, start, &pxl, clr);
		}
		test_blur((int)tmp[1], &pxl, blur);
	}
	return ((scene->is_real == CARTOON) ? cartoon(clr[0]) : clr[0]);
}
