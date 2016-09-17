/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/08 03:49:13 by nbelouni          #+#    #+#             */
/*   Updated: 2016/09/15 18:20:57 by tlepeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>
#include <stdio.h>
#include <image_buffer.h>

void	apply_ambient(t_color *color, t_scene *scene)
{
	if (scene->ambient_index >= 0 && scene->ambient_index <= 10)
	{
		color->r *= scene->ambient_color.r * scene->ambient_index;
		color->g *= scene->ambient_color.g * scene->ambient_index;
		color->b *= scene->ambient_color.b * scene->ambient_index;
	}
}

void	find_new_start(t_ray *start, t_hit hit)
{
	double	tmp;

	start->pos = vec_add(start->pos, scalar_product(start->dir, hit.t));
	tmp = dot_product(start->dir, hit.point_norm) * 2.0;
	start->dir = vec_sub(scalar_product(hit.point_norm, tmp), start->dir);
	start->dir = normalize(start->dir);
}

t_color	ray_tracing(t_ray *start, t_scene *scene, double noise, t_hit drawn_pixel, double r)
{
	double	reflet;
	t_vec	tmp;

	reflet = pow(drawn_pixel.reflection, r * 3);
	drawn_pixel.color = apply_light(scene, drawn_pixel, start);
	drawn_pixel.color = mult_color(drawn_pixel.color, reflet);
	if (drawn_pixel.opacity < 1.0)
		drawn_pixel.color = add_color(drawn_pixel.color,
				apply_refraction(start, scene, drawn_pixel, noise));
	if (drawn_pixel.texture == MARBLE)
		drawn_pixel.color = mult_color(drawn_pixel.color, noise / 255);
	if (drawn_pixel.texture == CHECKER)
	{
		tmp = vec_add(start->pos, scalar_product(start->dir, drawn_pixel.t));
		drawn_pixel.color = checkerboard(drawn_pixel.color, tmp);
	}
	return (drawn_pixel.color);
}

void	find_blur_dist(t_ray *start, t_hit drawn_pixel, t_cam cam, t_blur *blur)
{
	t_vec	tmp2;

	blur->p_obj = 0;
	if (drawn_pixel.bool == 1)
	{
		tmp2 = scalar_product(start->dir, drawn_pixel.t);
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

t_color	color_render(t_scene *scene, t_ray *start, double noise, t_blur *blur)
{
	t_color	final_color;
	t_hit	drawn_pixel;
	t_color	ambient;
	int		r;

	r = 0;
	final_color = init_color(0, 0, 0);
	while (r < 3)
	{
		if (r == 0 || drawn_pixel.reflection != 0)
		{
			drawn_pixel = find_closest_object(scene->objects, start);
			apply_ambient(&ambient, scene);
			if (drawn_pixel.bool == 1)
			{
				if (scene->is_real == CARTOON && is_black_edge(&drawn_pixel))
					drawn_pixel.color = init_color(0, 0, 0);
				else
					drawn_pixel.color = ray_tracing(start, scene, noise, drawn_pixel, r);
				if (blur && r == 0)
					find_blur_dist(start, drawn_pixel, scene->cam, blur);
			}
			else
			{
				if (blur)
					blur->t = 100;
				break ;
			}
			find_new_start(start, drawn_pixel);
			if (!(scene->is_real == CARTOON && is_black_edge(&drawn_pixel)))
				drawn_pixel.color = add_color(drawn_pixel.color, ambient);
			final_color = add_color(final_color, drawn_pixel.color);
		}
		if (scene->is_real == CARTOON)
			final_color = cartoon(final_color);
		r++;
	}
	return (final_color);
}

t_ray	init_start_ray(t_cam cam, int x, int y)
{
	t_ray ray;

	ray.pos = cam.ray.pos;
	ray.dir = calc_vec_dir(x, y, cam, cam.look_at);
	ray.dir = normalize(ray.dir);
	return (ray);
}

void	*draw_scene(void *data)
{
	int		x;
	int		y;
	t_ray	start;
	t_color final_color;
	double	noise;

	x = ((t_thread *)(data))->y_start - 1;
	while (++x < ((t_thread *)(data))->y_end)
	{
		y = -1;
		while (++y < HEIGHT)
		{
			noise = apply_marble_noise(x, y, 50,
					((t_thread *)(data))->env->tab_noise);
			start = init_start_ray(((t_thread *)(data))->scene->cam, x, y);
			final_color = color_render(((t_thread *)(data))->scene, &start,
					noise,
					&(((t_thread*)(data))->scene->blur_array[x * HEIGHT + y]));
			put_pixel_on_buffer(((unsigned char *)(((t_thread *)(data))->buf)),
					x, y, final_color);
		}
		((t_thread *)(data))->env->x = x;
	}
	return (data);
}
