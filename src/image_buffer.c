/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_buffer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sduprey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/17 01:51:06 by sduprey           #+#    #+#             */
/*   Updated: 2016/09/16 15:00:36 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

unsigned char		*new_image_buffer(int width, int height)
{
	unsigned char	*buf;
	int				size;
	int				i;

	size = width * height * 3;
	buf = (unsigned char *)malloc(sizeof(unsigned char) * size);
	if (!buf)
		return (NULL);
	i = 0;
	while (i < size)
	{
		buf[i] = 0;
		i++;
	}
	return (buf);
}

void			put_pixel_on_buffer(unsigned char *buf, int x, int y, t_color c)
{
	int			i;

	i = y * WIDTH * 3 + x * 3;
	buf[i + 0] = c.r;
	buf[i + 1] = c.g;
	buf[i + 2] = c.b;
}

t_color			get_pixel_from_buffer(unsigned char *buf, int x, int y)
{
	t_color		c;
	int			i;

	i = y * WIDTH * 3 + x * 3;
	c.r = buf[i];
	c.g = buf[i + 1];
	c.b = buf[i + 2];
	return (c);
}
