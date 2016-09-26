/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_mapping.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhenne <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/25 16:38:39 by bhenne            #+#    #+#             */
/*   Updated: 2016/09/25 17:06:07 by tlepeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _TEXTURE_MAPPING_H
# define _TEXTURE_MAPPING_H

# include <objects.h>

t_color		colortexture(t_color src_color, t_vec coord_hit, t_texture texture, double radius);

#endif
