/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sduprey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/15 01:29:20 by sduprey           #+#    #+#             */
/*   Updated: 2016/08/15 01:46:06 by sduprey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _TRIANGLE_H
# define _TRIANGLE_H

typedef struct	s_triangle
{
	t_vec		pos;
	t_vec		dir;
	t_vec		dir2;
	t_vec		dir3;
	t_color		color;
	int			specular;
	double		reflection;
	double		opacity;
	double		ref_index;
	int			is_negativ;
	int			texture;

}				t_triangle;


t_hit			is_triangle_hit(t_ray *ray, t_triangle *tri);

#endif
