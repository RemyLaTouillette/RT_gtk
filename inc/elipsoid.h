/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elipsoid.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlepeche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/06 03:53:08 by tlepeche          #+#    #+#             */
/*   Updated: 2016/08/25 16:38:03 by tlepeche         ###   ########.fr       */
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
	int			specular;
	double		reflection;
	double		opacity;
	double		ref_index;
	int			is_negativ;
	int			texture;
}				t_elips;

double			find_elips_det(t_ray *ray, t_elips *eli, double *a, double *b);
void			find_elips_closest_hit(double a, double b, double d, t_hit *h);
t_hit			is_elips_hit(t_ray *ray, t_elips *elips);

#endif
