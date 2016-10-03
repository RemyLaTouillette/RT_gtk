/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_get_values2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sduprey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/20 19:25:04 by sduprey           #+#    #+#             */
/*   Updated: 2016/10/03 17:34:12 by tlepeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

double		get_range_value(t_env *e, char *widget)
{
	GObject	*o;

	o = gtk_builder_get_object(e->builder, widget);
	return (gtk_range_get_value(GTK_RANGE(o)));
}

t_color		get_rgba(t_env *e)
{
	GObject	*o;
	GdkRGBA	*rgba;
	t_color	color;

	init_color(&color, 0, 0, 0);
	rgba = (GdkRGBA *)malloc(sizeof(GdkRGBA));
	if (rgba == NULL)
		return (color);
	o = gtk_builder_get_object(e->builder, "btn_color");
	gtk_color_chooser_get_rgba(GTK_COLOR_CHOOSER(o), rgba);
	init_color(&color, rgba->red * 255, rgba->green * 255, rgba->blue * 255);
	gdk_rgba_free(rgba);
	return (color);
}
