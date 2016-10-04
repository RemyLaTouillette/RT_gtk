/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aa.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/15 17:36:50 by nbelouni          #+#    #+#             */
/*   Updated: 2016/10/04 16:32:33 by tlepeche         ###   ########.fr       */
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
	return (av[max / 2]);
}

t_color		get_av_color(unsigned char *img, t_iter map, t_color *av, int lvl)
{
	t_iter	iter;
	int		i;
	int		j;
	int		k;
	t_color	c;

	j = map.j - (lvl / 2);
	k = 0;
	while (j <= map.j + (lvl / 2))
	{
		i = map.i - (lvl / 2);
		while (i <= map.i + (lvl / 2))
		{
			iter.i = i < 0 ? 0 : i;
			iter.i = i > WIDTH - 1 ? WIDTH - 1 : iter.i;
			iter.j = j < 0 ? 0 : j;
			iter.j = j > HEIGHT - 1 ? HEIGHT - 1 : iter.j;
			av[k] = get_pixel_from_buffer(img, iter.i, iter.j);
			k++;
			i++;
		}
		j++;
	}
	c = get_median_value(av, (int)pow(lvl, 2));
	return (c);
}

void		aa(void *b, void *n, t_iter *it)
{
	t_color			av[9];
	t_color			c;
	t_iter			map;

	map.j = -1;
	while (++map.j < HEIGHT)
	{
		map.i = it->i - 1;
		while (++map.i < it->j)
		{
			c = get_av_color(b, map, av, 3);
			put_pixel_on_buffer(n, map.i, map.j, c);
		}
	}
}
