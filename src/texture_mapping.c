/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_mapping.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhenne <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/24 17:31:33 by bhenne            #+#    #+#             */
/*   Updated: 2016/10/04 17:05:46 by tlepeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

void		gtk_get_pixel(GdkPixbuf *pix, double x, double y, t_color *color)
{
	int				width;
	int				height;
	unsigned char	*buffer;
	size_t			p;

	width = gdk_pixbuf_get_width(pix);
	height = gdk_pixbuf_get_height(pix);
	buffer = gdk_pixbuf_get_pixels(pix);
	p = ((((int)(x * width) % width) + width *
				((int)(y * height) % height)) * 3);
	if (p <= (size_t)(width * height * 3))
	{
		color->r = buffer[p];
		color->g = buffer[p + 1];
		color->b = buffer[p + 2];
	}
}

t_texture	coord_sphere_to_text(t_texture texture, t_vec coord_hit, double dfc)
{
	texture.x = -atan2(coord_hit.x, coord_hit.z) / (2.0 * M_PI);
	texture.y = ((asin(dfc) + (M_PI / 2)) / M_PI);
	return (texture);
}

t_color		colortexture(t_color c, t_vec coord_hit, t_texture t, double dfc)
{
	t_color dst_color;

	init_color(&dst_color, 0, 0, 0);
	t = coord_sphere_to_text(t, coord_hit, dfc);
	gtk_get_pixel(t.picture, t.x, t.y, &dst_color);
	c.r = dst_color.r;
	c.g = dst_color.g;
	c.b = dst_color.b;
	return (c);
}
