/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aa.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/15 17:36:50 by nbelouni          #+#    #+#             */
/*   Updated: 2016/09/16 17:00:47 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

t_color		get_median_value(t_color *av, int max)
{
	int		i;
	int		modif;
	int		a;
	int		b;
	t_color	tmp;

	modif = 1;
	while (modif)
	{
		modif = 0;
		i = 0;
		while (++i < max)
		{
			a = av[i - 1].r + av[i - 1].g + av[i - 1].b;
			b = av[i].r + av[i].g + av[i].b;
			if (a > b)
			{
				modif = 1;
				tmp = av[i - 1];
				av[i - 1] = av[i];
				av[i] = tmp;
			}
		}
	}
	return (av[4]);
}

//t_color		get_av_color(unsigned char *img, int x, int y, int mode)
//{
//	t_color	*av;
//	t_color	c;
//	int		i;
//	int		j;
//	int		k;
//
//	av = (t_color *)malloc(sizeof(t_color) * 9);
//	j = y - 1;
//	k = 0;
//	while (j <= y + 1)
//	{
//		i = x - 1;
//		while (i <= x + 1)
//		{
//			if (i >= 0 && j >= 0 && i < WIDTH && j < HEIGHT)
//				av[k] = get_pixel_from_buffer(img, i, j);
//			k++;
//			i++;
//		}
//		j++;
//	}
//	if (mode == 1)
//	{
//		return (get_median_value(av, 9));
//	}
//	else
//	{
//		i = 0;
//		c.r = 0;
//		c.g = 0;
//		c.b = 0;
//		while (i < 9)
//		{
//			c.r += av[i].r;
//			c.g += av[i].g;
//			c.b += av[i].b;
//			i++;
//		}
//		c.r /= 9;
//		c.g /= 9;
//		c.b /= 9;
//		return (c);
//	}
//}
t_color		get_av_color(unsigned char *img, int x, int y, int mode)
{
	t_color	*av;
//	t_color	c;
	int		i;
	int		j;
	int		k;

	(void)mode;
	av = (t_color *)malloc(sizeof(t_color) * 9);
	j = y - 1;
	k = 0;
	while (j <= y + 1)
	{
		i = x - 1;
		while (i <= x + 1)
		{
			if (i >= 0 && j >= 0 && i < WIDTH && j < HEIGHT)
				av[k] = get_pixel_from_buffer(img, i, j);
			k++;
			i++;
		}
		j++;
	}
	return (get_median_value(av, 9));
}

void	*aa(void *img, int mode)
{
	unsigned char	*aa;
	int				i;
	int				j;
	t_color			c;

	if (!(aa = new_image_buffer(WIDTH, HEIGHT)))
		return (NULL);
	j = 0;
//	c = init_color(0, 0, 0);
//	(void)mode;
	while (j < HEIGHT)
	{
		i = 0;
		while (i < WIDTH)
		{
			c = get_av_color(img, i, j, mode);
			put_pixel_on_buffer(aa, i, j, c);
			i++;
		}
		j++;
	}
	return (aa);
}
