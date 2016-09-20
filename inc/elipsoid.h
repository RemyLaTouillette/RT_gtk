/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elipsoid.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlepeche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/06 03:53:08 by tlepeche          #+#    #+#             */
/*   Updated: 2016/09/20 17:30:37 by tlepeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _ELIPSOID_H
# define _ELIPSOID_H

# include <ray.h>
# include <objects.h>
# include <quad.h>

typedef struct	s_elips
{
	double		radius;
	t_vec		center;
	t_quad		quad;
	t_color		color;
	double		specular;
	double		reflection;
	double		opacity;
	double		ref_index;
	int			is_negativ;
	int			texture;
}				t_elips;

void			is_elips_hit(t_ray *ray, t_elips *elips, t_hit *hit);

#endif
