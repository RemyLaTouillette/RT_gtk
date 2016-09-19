/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blur.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/13 01:45:04 by nbelouni          #+#    #+#             */
/*   Updated: 2016/09/19 21:16:06 by tlepeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

t_color		mix_color(t_color *mixed_color, int n_color)
{
	t_color	new_color;
	int		x;

	x = 0;
	new_color = mixed_color[x];
	while (++x < n_color)
	{
		new_color.r += mixed_color[x].r;
		new_color.g += mixed_color[x].g;
		new_color.b += mixed_color[x].b;
	}
	new_color.r /= n_color;
	new_color.g /= n_color;
	new_color.b /= n_color;
	check_color(&new_color);
	free(mixed_color);
	return (new_color);
}

t_color		*new_color_array(int blur_lvl)
{
	int		x;
	int		max;
	t_color	*mixed_color;

	max = (blur_lvl * 2 + 1) * (blur_lvl * 2 + 1);
	if (!(mixed_color = (t_color *)malloc(sizeof(t_color) * max)))
		return (NULL);
	x = -1;
	while (++x < max)
		mixed_color[x] = init_color(0, 0, 0);
	return (mixed_color);
}

t_color		get_mixed_color(void *e, int b, int i, int j)
{
	int		x;
	int		y;
	int		n;
	t_color	*tmp;

	if (!(tmp = new_color_array(b)))
		return (init_color(0, 0, 0));
	x = -1;
	n = 0;
	while (++x < b * 2 + 1)
	{
		y = -1;
		while (++y < b * 2 + 1)
		{
			if (i - b + x >= 0 && i - b + x < WIDTH &&
			j - b + y >= 0 && j - b + y < HEIGHT)
			{
				tmp[n] = get_pixel_from_buffer(e, i - b + x, j - b + y);
				n++;
			}
		}
	}
	return (mix_color(tmp, n));
}

void		*apply_blur(void *img, int blur_lvl)
{
	int				i;
	int				j;
	t_color			new_color;
	unsigned char	*blurred_img;

	if (blur_lvl <= 0)
		return (img);
	if (!(blurred_img = new_image_buffer()))
		return (NULL);
	i = -1;
	while (++i < WIDTH)
	{
		j = -1;
		while (++j < HEIGHT)
		{
			new_color = get_mixed_color(img, blur_lvl, i, j);
			put_pixel_on_buffer(blurred_img, i, j, new_color);
		}
	}
	return (blurred_img);
}
