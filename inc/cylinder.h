/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlepeche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/10 03:30:13 by tlepeche          #+#    #+#             */
/*   Updated: 2016/09/10 17:28:22 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _CYLINDER_H
# define _CYLINDER_H

# include <rtv1.h>
# include <objects.h>

typedef struct	s_cylinder
{
	double		radius;
	t_vec		pos;
	t_vec		dir;
	double		length;
	double		h;
	t_color		color;
	double		specular;
	double		reflection;
	double		opacity;
	double		ref_index;
	int			is_negativ;
	int			texture;
	int			is_closed;
}				t_cylinder;

t_hit			is_cylinder_hit(t_ray *ray, t_cylinder *cylinder);
void			create_cyl_intern_struct(t_ray *r, t_cylinder *c, t_intern *i);
void			complete_cyl_hit(t_hit *hit, t_cylinder *cylinder);
double			find_cyl_limit(t_ray *r, t_cylinder *cyl, t_intern i, t_hit *h);
t_hit			cyl_first_try(t_cylinder *c, t_hit hit_s, t_hit hit, double *t);
t_hit			cyl_second_try(t_cylinder *c, t_hit hit_s, t_hit h, double *t);
t_hit			cyl_third_try(t_cylinder *c, t_hit hit_size, t_hit hit);

#endif
