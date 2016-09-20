/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/13 03:17:42 by nbelouni          #+#    #+#             */
/*   Updated: 2016/09/20 17:29:36 by tlepeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLANE_H
# define PLANE_H

typedef struct		s_plane
{
	t_vec			pos;
	t_vec			normal;
	t_color			color;
	double			specular;
	double			reflection;
	double			opacity;
	double			ref_index;
	int				is_negativ;
	int				texture;
}					t_plane;

void				is_plane_hit(t_ray *ray, t_plane *plan, t_hit *hit);
double				find_plane_hit(t_ray *ray, t_plane *plan);

#endif
