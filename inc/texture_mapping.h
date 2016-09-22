/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_mapping.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhenne <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/25 16:38:39 by bhenne            #+#    #+#             */
/*   Updated: 2016/09/22 15:27:26 by tlepeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _TEXTURE_MAPPING_H
# define _TEXTURE_MAPPING_H

# include <objects.h>

t_texture	coord_sphere_to_text(t_texture texture, t_vec coord_hit);
t_color		colortexture(t_color src_color, t_vec coord_hit, t_texture texture);
//t_color		gtk_get_pixel(GdkPixbuf *pixbuf, int x, int y);
t_color		gtk_get_pixel(GdkPixbuf *pixbuf, double x, double y);

#endif
