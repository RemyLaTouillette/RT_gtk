/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/08 03:49:13 by nbelouni          #+#    #+#             */
/*   Updated: 2016/09/17 18:42:22 by tlepeche         ###   ########.fr       */
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
	if (hit->bool == 1)
	{
		tmp2 = scalar_product(start->dir, hit->t);
		tmp2 = vec_add(start->pos, tmp2);
		blur->t = tmp2.z;
		if (blur->t == cam.ray.pos.z)
			blur->t = 0;
		if (blur->t > 100)
			blur->t = 100;
	}
	else
		blur->t = 10;
}

void	finish_loop(t_scene *s, t_ray *start, t_hit *hit, t_color *fnl_clr)
{
	t_color	ambient;
	double	tmp;

	ambient = init_color(0, 0, 0);
	if (hit->reflection != 0)
	{
		start->pos = vec_add(start->pos, scalar_product(start->dir, hit->t));
		tmp = dot_product(start->dir, hit->point_norm) * 2.0;
		start->dir = vec_sub(scalar_product(hit->point_norm, tmp), start->dir);
		start->dir = normalize(start->dir);
	}
	if (s->ambient_index >= 0 && s->ambient_index <= 10)
		ambient = mult_color(s->ambient_color, s->ambient_index);
	if (!(s->is_real == CARTOON && is_black_edge(hit)))
		hit->color = add_color(hit->color, ambient);
	*fnl_clr = add_color(*fnl_clr, hit->color);
}

void	complete_hit_color(t_scene *s, t_ray *start, t_hit *hit, double noise)
{
	double	reflet;

	if (s->is_real == CARTOON && is_black_edge(hit))
		hit->color = init_color(0, 0, 0);
	else
	{
		reflet = pow(hit->reflection, s->r * 3);
		hit->color = apply_light(s, *hit, start);
		hit->color = mult_color(hit->color, reflet);
		ray_tracing(start, s, noise, hit);
	}
}

t_color	color_render(t_scene *scene, t_ray *start, double noise, t_blur *blur)
{
	t_color	fnl_clr;
	t_hit	pxl;

	scene->r = -1;
	fnl_clr = init_color(0, 0, 0);
	while (scene->r++ < scene->reflection)
	{
		if (scene->r == 0 || pxl.reflection != 0)
		{
			pxl = find_closest_object(scene->objects, start);
			if (pxl.bool == 1)
			{
				complete_hit_color(scene, start, &pxl, noise);
				if (blur && scene->r == 0)
					find_blur_dist(start, &pxl, scene->cam, blur);
			}
			else
				break ;
			finish_loop(scene, start, &pxl, &fnl_clr);
		}
		if ((scene->r == 0 || pxl.reflection != 0) && pxl.bool == 0 && blur)
			blur->t = 100;
		fnl_clr = (scene->is_real == CARTOON) ? cartoon(fnl_clr) : fnl_clr;
	}
	return (fnl_clr);
}
