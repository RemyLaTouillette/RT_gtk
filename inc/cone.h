/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sduprey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/14 01:25:00 by sduprey           #+#    #+#             */
/*   Updated: 2016/09/09 15:21:48 by tlepeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _CONE_H
# define _CONE_H

# include <rtv1.h>
# include <objects.h>

typedef struct	s_cone
{
	t_vec		pos;
	t_vec		dir;
	double		len;
	double		r;
	t_color		color;
	int			specular;
	double		reflection;
	double		opacity;
	double		ref_index;
	int			is_negativ;
	int			texture;
	int			is_closed;
	t_intern	*intern;
}				t_cone;

t_hit			is_cone_hit(t_ray *ray, t_cone *cone);
void			create_cone_intern_struct(t_ray *r, t_cone *c, t_intern *inter);
void			complete_cone_hit(t_hit *hit, t_cone *cone);
double			find_cone_limit(t_ray *r, t_cone *c, t_intern inte, t_hit *hit);
t_hit			cone_first_try(t_cone *c, t_hit hit_size, t_hit hit, double *t);
t_hit			cone_second_try(t_cone *c, t_hit hit_siz, t_hit hit, double *t);
t_hit			cone_third_try(t_cone *c, t_hit hit_size, t_hit hit);

#endif
