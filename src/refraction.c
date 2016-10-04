/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refraction.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/22 04:58:48 by nbelouni          #+#    #+#             */
/*   Updated: 2016/10/04 17:04:59 by tlepeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

static inline t_ray	find_refract(t_ray *s, t_hit pxl, double c_r, int test)
{
	double	ref_refract;
	double	new_ref_index;
	t_ray	res;
	t_vec	new_norm;
	t_vec	inv_dir;

	res.pos = vec_add(s->pos, scalar_product(s->dir, pxl.t));
	inv_dir = scalar_product(s->dir, -1);
	pxl.nml = scalar_product(pxl.nml, test);
	ref_refract = dot_product(pxl.nml, inv_dir);
	ref_refract /= (get_length(pxl.nml) * get_length(inv_dir));
	new_ref_index = 1 - c_r * c_r * (1 - ref_refract * ref_refract);
	if (new_ref_index > 0)
	{
		new_ref_index = sqrt(new_ref_index);
		new_ref_index = c_r * ref_refract - new_ref_index;
		new_norm = scalar_product(pxl.nml, new_ref_index);
		res.dir = scalar_product(inv_dir, c_r);
		res.dir = vec_sub(res.dir, new_norm);
	}
	else
		res.dir = init_vector(0, 0, 0);
	res.dir = normalize(res.dir);
	return (res);
}

static inline void	init(t_hit *p, double *refract_indice, int *test)
{
	if (p->t_max == p->t)
	{
		*refract_indice = p->ref_index;
		*test = -1;
	}
	else
	{
		*test = 1;
		*refract_indice = 1.0 / p->ref_index;
	}
}

t_color				apply_refraction(t_ray *st, t_scene *s, t_hit *p, t_text *t)
{
	double	refract_indice;
	int		test;
	t_color	tmp;

	init(p, &refract_indice, &test);
	tmp = p->color;
	*st = find_refract(st, *p, refract_indice, test);
	if (get_length(st->dir) != 0)
	{
		if (s->is_real == CARTOON && is_black_edge(p))
		{
			init_color(&tmp, 0, 0, 0);
			return (tmp);
		}
		else
		{
			tmp = color_render(s, st, t, NULL);
			add_color(&tmp, &p->color);
		}
	}
	check_color(&tmp);
	return (tmp);
}
