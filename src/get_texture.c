/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_texture.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlepeche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/22 14:30:16 by tlepeche          #+#    #+#             */
/*   Updated: 2016/09/22 18:08:43 by tlepeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

GdkPixbuf	*get_texture(void)
{
	FILE			*file;
	size_t			length;
	guint8			buffer[100000];
	GdkPixbufLoader	*loader;

	if (!(file = fopen("ressources/worldmap512.jpg", "r")))
	{
		printf("file not found\n");
		return (NULL);
	}
	length = fread(buffer, 1, sizeof(buffer), file);
	fclose(file);
	if (length == 100000)
	{
		printf("file too large\n");
		return (NULL);
	}
	loader = gdk_pixbuf_loader_new();
	gdk_pixbuf_loader_write(loader, buffer, length, NULL);
	return (gdk_pixbuf_loader_get_pixbuf(loader));
}
