/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_mapping.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhenne <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/24 17:31:33 by bhenne            #+#    #+#             */
/*   Updated: 2016/09/22 15:10:26 by bhenne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>
#include <gdk-pixbuf/gdk-pixbuf.h>
#include <stdio.h>

t_color		gtk_get_pixel(GdkPixbuf *pixbuf, double x, double y)
{
	int				width;
	int				height;
	unsigned char	*buffer;
	int				p;
	t_color			dst_color;

	width = gdk_pixbuf_get_width(pixbuf);
	height = gdk_pixbuf_get_height(pixbuf);
	buffer = gdk_pixbuf_get_pixels(pixbuf);
	p = ((((int)(x * width) % width) + width *
				((int)(y * height) % height)) * 3);
	dst_color.r = buffer[p];
	dst_color.g = buffer[p + 1];
	dst_color.b = buffer[p + 2];
	return (dst_color);
}

t_color		colortexture(t_color src_color, t_vec coord_hit, t_texture texture)
{
	t_color dst_color;

	texture = coord_sphere_to_text(texture, coord_hit);
	dst_color = gtk_get_pixel(texture.picture, texture.x, texture.y);
	src_color.r = dst_color.r;
	src_color.g = dst_color.g;
	src_color.b = dst_color.b;
	return (src_color);
}

t_texture	coord_sphere_to_text(t_texture texture, t_vec coord_hit)
{
	texture.x = (atan(-(coord_hit.x) / coord_hit.z) + M_PI) / (2.0 * M_PI);
	texture.y = ((asin(coord_hit.y) + (M_PI / 2)) / M_PI) * 2;
	return (texture);
}
