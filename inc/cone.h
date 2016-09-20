/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sduprey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/14 01:25:00 by sduprey           #+#    #+#             */
/*   Updated: 2016/09/20 17:51:49 by tlepeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _CONE_H
# define _CONE_H

# include <rtv1.h>
# include <objects.h>

typedef struct	s_cone
{
	double		r;
	t_vec		pos;
	t_vec		dir;
	double		len;
	t_color		color;
	double		specular;
	double		reflection;
	double		opacity;
	double		ref_index;
	int			is_negativ;
	int			texture;
	int			is_closed;
}				t_cone;

void			is_cone_hit(t_ray *ray, t_cone *cone, t_hit *hit);
void			create_cone_intern_struct(t_ray *r, t_cone *c, t_intern *inter);
void			complete_cone_hit(t_hit *hit, t_cone *cone);
double			find_cone_limit(t_ray *r, t_cone *c, t_intern inte, t_hit *hit);
t_hit			cone_first_try(t_cone *c, t_hit *hs, t_hit *hit, double *t);
t_hit			cone_second_try(t_cone *c, t_hit *hs, t_hit *hit, double *t);
t_hit			cone_third_try(t_cone *c, t_hit *hit_size, t_hit *hit);

#endif
