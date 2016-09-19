/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aa.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/15 17:36:50 by nbelouni          #+#    #+#             */
/*   Updated: 2016/09/19 21:23:34 by tlepeche         ###   ########.fr       */
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

t_color		get_av_color(unsigned char *img, int x, int y, t_color *av)
{
	int		i;
	int		j;
	int		k;
	t_color	c;

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
	c = get_median_value(av, 9);
	return (c);
}

void		*aa(void *img)
{
	unsigned char	*aa;
	t_color			av[9];
	int				i;
	int				j;
	t_color			c;

	if (!(aa = new_image_buffer()))
		return (NULL);
	j = 0;
	while (j < HEIGHT)
	{
		i = 0;
		while (i < WIDTH)
		{
			c = get_av_color(img, i, j, av);
			put_pixel_on_buffer(aa, i, j, c);
			i++;
		}
		j++;
	}
	return (aa);
}
