/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_texture.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlepeche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/22 14:30:16 by tlepeche          #+#    #+#             */
/*   Updated: 2016/09/28 18:15:06 by tlepeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

static inline size_t		find_length(void)
{
	int		fd;
	size_t	length;
	int		tmp;
	char	str[10000];

	tmp = 0;
	length = 0;
	if ((fd = open("ressources/worldmap512.jpg", O_RDONLY)) == -1)
		return (0);
	while ((tmp = read(fd, str, 10000)) != 0)
		length += tmp;
	close(fd);
	return (length);
}

GdkPixbuf					*get_texture(void)
{
	FILE			*file;
	size_t			length;
	unsigned char	*buffer;
	GdkPixbufLoader	*loader;
	GdkPixbuf		*texture;

	if (!(file = fopen("ressources/worldmap512.jpg", "r")))
		return (NULL);
	length = find_length();
	buffer = (unsigned char *)malloc(sizeof(unsigned char) * length);
	if (!(fread(buffer, 1, length, file)))
		return (NULL);
	fclose(file);
	loader = gdk_pixbuf_loader_new();
	if (!(gdk_pixbuf_loader_write(loader, buffer, length, NULL)))
		return (NULL);
	texture = gdk_pixbuf_loader_get_pixbuf(loader);
	free(buffer);
	gdk_pixbuf_loader_close(loader, NULL);
	return (texture);
}
