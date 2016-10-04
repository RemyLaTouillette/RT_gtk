/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sepia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sduprey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/05 00:20:42 by sduprey           #+#    #+#             */
/*   Updated: 2016/10/04 17:05:28 by tlepeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

static inline t_color		set_black_white_color(t_color c)
{
	t_color	s;
	int		m;

	m = (c.r + c.g + c.b) / 3;
	init_color(&s, m, m, m);
	check_color(&s);
	return (s);
}

static inline t_color		set_sepia_color(t_color c)
{
	t_color	s;
	t_color	sepia;

	init_color(&sepia, 94, 38, 18);
	s.r = (c.r * .393) + (c.g * .769) + (c.b * .189);
	s.g = (c.r * .349) + (c.g * .686) + (c.b * .168);
	s.b = (s.r * .272) + (s.g * .534) + (s.b * .131);
	s.r = (s.r + sepia.r) * 0.5;
	s.g = (s.g + sepia.g) * 0.5;
	s.b = (s.b + sepia.b) * 0.5;
	check_color(&s);
	return (s);
}

void						sepia_filter(void *b, void *n, int f, t_iter *iter)
{
	int				i;
	int				j;
	t_color			c;

	if (f != SEPIA && f != NOIR_BLANC)
		return ;
	j = -1;
	while (++j < HEIGHT)
	{
		i = iter->i - 1;
		while (++i < iter->j)
		{
			c = get_pixel_from_buffer(b, i, j);
			if (f == SEPIA)
				c = set_sepia_color(c);
			else if (f == NOIR_BLANC)
				c = set_black_white_color(c);
			put_pixel_on_buffer(n, i, j, c);
		}
	}
}
