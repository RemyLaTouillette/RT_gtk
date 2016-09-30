/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   depth_of_field.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/22 14:28:30 by nbelouni          #+#    #+#             */
/*   Updated: 2016/09/30 19:21:12 by tlepeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

int			set_color(void *img, t_color *c, double *blur_array, int *n)
{
	if (n[2] >= 0 && n[2] < HEIGHT * WIDTH &&
	blur_array[n[5] * HEIGHT + n[6]] <= blur_array[n[2]])
	{
		if (n[3] >= 0 && n[3] < WIDTH && n[4] >= 0 && n[4] < HEIGHT)
		{
			c[n[0]] = get_pixel_from_buffer(img, n[3], n[4]);
			n[0]++;
		}
	}
	return (0);
}

int			magic_init(t_color **mixed_color, int blur_lvl, int *n, t_iter iter)
{
	if (!(*mixed_color = new_color_array(blur_lvl)))
		return (0);
	n[0] = 0;
	n[1] = 0;
	n[5] = iter.i;
	n[6] = iter.j;
	return (1);
}

t_color		depth_of_field(void *img, int blur_lvl, t_iter iter, double *array)
{
	t_iter	i;
	t_color	*mixed_color;
	int		n[7];

	if (!magic_init(&mixed_color, blur_lvl, n, iter))
		return (mixed_color[0]);
	i.i = -1;
	while (++i.i < blur_lvl * 2 + 1)
	{
		i.j = -1;
		while (++i.j < blur_lvl * 2 + 1)
		{
			n[3] = n[5] - blur_lvl + i.i;
			n[4] = n[6] - blur_lvl + i.j;
			n[2] = n[3] * HEIGHT + n[4];
			set_color(img, mixed_color, array, n);
		}
	}
	return (mix_color(mixed_color, n[0]));
}

void		apply_depth_of_field(void *b, void *n, t_scene *s, t_iter *iter)
{
	int		blur_lvl;
	t_color	new_color;
	t_iter	i;

	i.j = -1;
	while (++i.j < HEIGHT)
	{
		i.i = iter->i - 1;
		while (++i.i < iter->j)
		{
			blur_lvl = ((int)(fabs(s->dof - s->blur_array[i.i * HEIGHT +
							i.j]))) * 2;
			if (blur_lvl > 10)
				blur_lvl = 10;
			if (blur_lvl > 0)
				new_color = depth_of_field(b, blur_lvl, i, s->blur_array);
			else
				new_color = get_pixel_from_buffer(b, i.i, i.j);
			put_pixel_on_buffer(n, i.i, i.j, new_color);
		}
	}
}
