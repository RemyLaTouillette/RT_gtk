/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tetra.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhenne <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/08 02:14:57 by bhenne            #+#    #+#             */
/*   Updated: 2016/09/14 16:13:07 by tlepeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _tetra_H
# define _tetra_H

# include <ray.h>
# include <objects.h>

typedef struct	s_tetra
{
	t_vec		v0;
	t_vec		v1;
	t_vec		v2;
	t_vec		v3;
	t_color		color;
	int			specular;
	double		reflection;
	double		opacity;
	double		ref_index;
	int			is_negativ;
	int			texture;
}				t_tetra;

t_hit			is_tetra_hit(t_ray *ray, t_tetra*tetra);
void			complete_tetra_hit(t_tetra *tetra, t_hit *hit);
void			complete_triangle(t_triangle *tri, t_tetra *tetra);
void			get_face_hit(t_hit face, t_hit *hit);

#endif
