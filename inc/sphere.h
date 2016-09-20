/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/14 01:13:12 by nbelouni          #+#    #+#             */
/*   Updated: 2016/09/20 17:30:28 by tlepeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _SPHERE_H
# define _SPHERE_H

# include <ray.h>
# include <objects.h>

typedef struct	s_sphere
{
	double		radius;
	t_vec		center;
	t_color		color;
	double		specular;
	double		reflection;
	double		opacity;
	double		ref_index;
	int			is_negativ;
	int			texture;
}				t_sphere;

void			is_sphere_hit(t_ray *ray, t_sphere *sphere, t_hit *hit);

#endif
