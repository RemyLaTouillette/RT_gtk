/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_mapping.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhenne <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/25 16:38:39 by bhenne            #+#    #+#             */
/*   Updated: 2016/09/30 15:09:02 by tlepeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _TEXTURE_MAPPING_H
# define _TEXTURE_MAPPING_H

# include <objects.h>

t_color		colortexture(t_color c, t_vec hit, t_texture texture, double r);

#endif
