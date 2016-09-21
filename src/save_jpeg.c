/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_jpeg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sduprey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/21 19:03:02 by sduprey           #+#    #+#             */
/*   Updated: 2016/09/21 19:04:42 by sduprey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

void	save_jpeg(unsigned char *data)
{
	GdkPixbuf	*pixbuf;

	pixbuf = gtk_new_image(data);
	gdk_pixbuf_save(pixbuf, "test_img", "jpeg", NULL, "quality", "100", NULL);
}
