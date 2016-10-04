/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_jpeg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sduprey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/21 19:03:02 by sduprey           #+#    #+#             */
/*   Updated: 2016/10/04 12:39:29 by tlepeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>
#include <sys/stat.h>

int				file_exist(char *filename)
{
	struct stat	buffer;

	return (stat(filename, &buffer) == 0);
}

char			*filename_for_saving(void)
{
	char		*fname;
	int			i;
	int			check;

	if (!(fname = (char *)malloc(sizeof(char) * 24)))
		return (NULL);
	fname = ft_strcpy(fname, "save_img.jpeg");
	i = 1;
	check = file_exist(fname);
	while (check == 1 && i < 100)
	{
		fname = ft_strcpy(fname, "save_img(");
		fname = ft_strcat(fname, ft_itoa(i));
		fname = ft_strcat(fname, ").jpeg");
		check = file_exist(fname);
		i++;
	}
	return (fname);
}

void			save_jpeg(unsigned char *data)
{
	GdkPixbuf	*pixbuf;
	GError		*error;
	char		*fname;
	int			check;

	error = NULL;
	fname = filename_for_saving();
	pixbuf = gtk_new_image(data);
	if (fname != NULL)
	{
		check = gdk_pixbuf_save(pixbuf, fname, "jpeg", &error,
				"quality", "100", NULL);
		free(fname);
	}
}
