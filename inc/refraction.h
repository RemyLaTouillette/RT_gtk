/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refraction.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/22 04:59:45 by nbelouni          #+#    #+#             */
/*   Updated: 2016/09/20 13:53:09 by tlepeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REFRACTION_H
# define REFRACTION_H

t_color	apply_refraction(t_ray *start, t_scene *s, t_hit *drawn_p, double noise);

#endif
