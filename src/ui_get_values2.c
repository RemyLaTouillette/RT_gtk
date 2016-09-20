/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_get_values2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sduprey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/20 19:25:04 by sduprey           #+#    #+#             */
/*   Updated: 2016/09/20 20:10:05 by sduprey          ###   ########.fr       */
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

	rgba = (GdkRGBA *)malloc(sizeof(GdkRGBA));
	if (rgba == NULL)
		return (init_color(0, 0, 0));
	o = gtk_builder_get_object(e->builder, "btn_color");
	gtk_color_chooser_get_rgba(GTK_COLOR_CHOOSER(o), rgba);
	return (init_color(rgba->red * 255, rgba->green * 255, rgba->blue * 255));
}
