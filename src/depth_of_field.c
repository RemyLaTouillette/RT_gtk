/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   depth_of_field.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/22 14:28:30 by nbelouni          #+#    #+#             */
/*   Updated: 2016/09/26 21:40:14 by tlepeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

int			set_color(void *img, t_color *c, t_blur *blur_array, int *n)
{
	if (n[2] >= 0 && n[2] < HEIGHT * WIDTH &&
	blur_array[n[5] * HEIGHT + n[6]].t <= blur_array[n[2]].t)
	{
		if (n[3] >= 0 || n[3] < WIDTH || n[4] >= 0 || n[4] < HEIGHT)
		{
			c[n[0]] = get_pixel_from_buffer(img, n[3], n[4]);
			if (c[n[0]].r == 0 && c[n[0]].g == 0 && c[n[0]].b == 0)
				n[1]++;
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

t_color		depth_of_field(void *img, int blur_lvl, t_iter iter, t_blur *array)
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
	if (n[0] == n[1])
	{
		free(mixed_color);
		return (mixed_color[0]);
	}
	return (mix_color(mixed_color, n[0]));
}

void		*apply_depth_of_field(void *img, t_blur *array, double dof)
{
	void	*blurred_img;
	int		blur_lvl;
	t_color	new_color;
	t_iter	i;

	printf("dof : %f\n", dof);
	if (!(blurred_img = new_image_buffer()))
		return (NULL);
	i.i = -1;
	while (++i.i < WIDTH)
	{
		i.j = -1;
		while (++i.j < HEIGHT)
		{
			blur_lvl = ((int)(fabs(dof - array[i.i * HEIGHT + i.j].t))) * 2;
			if (blur_lvl > 10)
				blur_lvl = 10;
			if (blur_lvl > 0)
				new_color = depth_of_field(img, blur_lvl, i, array);
			else
				new_color = get_pixel_from_buffer(img, i.i, i.j);
			put_pixel_on_buffer(blurred_img, i.i, i.j, new_color);
		}
	}
	return (blurred_img);
}
