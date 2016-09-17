/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sepia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sduprey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/05 00:20:42 by sduprey           #+#    #+#             */
/*   Updated: 2016/09/16 16:09:27 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>
#include <stdio.h>

t_color		set_black_white_color(t_color c)
{
	t_color	s;
	int		m;

	m = (c.r + c.g + c.b) / 3;
	s = init_color(m, m, m);
	check_color(&s);
	return (s);
}

t_color		set_sepia_color(t_color c)
{
	t_color	s;
	t_color	sepia;

	sepia = init_color(94, 38, 18);
	s.r = (c.r * .393) + (c.g * .769) + (c.b * .189);
	s.g = (c.r * .349) + (c.g * .686) + (c.b * .168);
	s.b = (s.r * .272) + (s.g * .534) + (s.b * .131);
	s.r = (s.r + sepia.r) / 2;
	s.g = (s.g + sepia.g) / 2;
	s.b = (s.b + sepia.b) / 2;
	check_color(&s);
	return (s);
}

void		*sepia_filter(void *img, int filter)
{
	unsigned char	*new;
	int				i;
	int				j;
	t_color			c;

	if (filter != SEPIA && filter != NOIR_BLANC)
		return (img);
	if (!(new = new_image_buffer(WIDTH, HEIGHT)))
		return (NULL);
	j = -1;
	while (++j < HEIGHT)
	{
		i = -1;
		while (++i < WIDTH)
		{
			c = get_pixel_from_buffer(img, i, j);
			if (filter == SEPIA)
				c = set_sepia_color(c);
			else if (filter == NOIR_BLANC)
				c = set_black_white_color(c);
			put_pixel_on_buffer(new, i, j, c);
		}
	}
	return (new);
}
