/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_cmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlepeche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/16 15:05:47 by tlepeche          #+#    #+#             */
/*   Updated: 2016/09/16 15:23:46 by tlepeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

int		vec_cmp(t_vec v1, t_vec v2)
{
	if (v1.x == v2.x && v1.y == v2.y && v1.z == v2.z)
		return (1);
	return (0);
}

int		ray_cmp(t_ray r1, t_ray r2)
{
	t_vec tmp_dir1;
	t_vec tmp_dir2;

	tmp_dir1 = normalize(r1.dir);
	tmp_dir2 = normalize(r2.dir);
	if (vec_cmp(r1.pos, r2.pos) == 1 && vec_cmp(tmp_dir1, tmp_dir2) == 1)
		return (1);
	return (0);
}

int		color_cmp(t_color c1, t_color c2)
{
	if (c1.r == c2.r && c1.g == c2.g && c1.b == c2.b)
		return (1);
	return (0);
}

int		quad_cmp(t_quad q1, t_quad q2)
{
	if (q1.a == q2.a && q1.b == q2.b && q1.c == q1.c)
		return (1);
	return (0);
}
