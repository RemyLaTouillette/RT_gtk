/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aa.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/15 17:36:50 by nbelouni          #+#    #+#             */
/*   Updated: 2016/09/29 19:17:00 by sduprey          ###   ########.fr       */
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
	return (av[12]);
}

t_color		get_av_color(unsigned char *img, int x, int y, t_color *av)
{
	t_iter	iter;
	int		i;
	int		j;
	int		k;
	t_color	c;

	j = y - 2;
	k = 0;
	while (j <= y + 2)
	{
		i = x - 2;
		while (i <= x + 2)
		{
			if (i < 0)
				iter.i = 0;
			else if (i > WIDTH - 1)
				iter.i = WIDTH - 1;
			else
				iter.i = i;
			if (j < 0)
				iter.j = 0;
			else if (j > HEIGHT - 1)
				iter.j = HEIGHT - 1;
			else
				iter.j = j;
			av[k] = get_pixel_from_buffer(img, iter.i, iter.j);
			k++;
			i++;
		}
		j++;
	}
	c = get_median_value(av, 25);
	return (c);
}

void		aa(void *b, void *n, int u, int d)
{
	t_color			av[25];
	int				i;
	int				j;
	t_color			c;

	j = -1;
	while (++j < HEIGHT)
	{
		i = u - 1;
		while (++i < d)
		{
			c = get_av_color(b, i, j, av);
			put_pixel_on_buffer(n, i, j, c);
		}
	}
}
