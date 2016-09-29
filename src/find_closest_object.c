/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_closest_object.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/13 02:55:00 by nbelouni          #+#    #+#             */
/*   Updated: 2016/09/28 18:13:49 by tlepeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

static inline void		get_hit_next(t_ray *r, t_node *n, int is_neg, t_hit *t)
{
	if (n->type == ELIPS &&
			((t_elips *)(n->data))->is_negativ == is_neg)
		is_elips_hit(r, (t_elips *)n->data, t);
	else if (n->type == TRIAN &&
			((t_triangle *)(n->data))->is_negativ == is_neg)
		is_trian_hit(r, (t_triangle *)n->data, t);
	else if (n->type == PARA &&
			((t_parallelo *)(n->data))->is_negativ == is_neg)
		is_parallelo_hit(r, (t_parallelo *)n->data, t);
	else if (n->type == TETRA &&
			((t_tetra *)(n->data))->is_negativ == is_neg)
		is_tetra_hit(r, (t_tetra *)n->data, t);
}

void					get_hit(t_ray *ray, t_node *node, int is_neg, t_hit *t)
{
	init_hit(t);
	if (node->type == SPHERE &&
			((t_sphere *)(node->data))->is_negativ == is_neg)
		is_sphere_hit(ray, (t_sphere *)node->data, t);
	else if (node->type == CYLINDER &&
			((t_cylinder *)(node->data))->is_negativ == is_neg)
		is_cylinder_hit(ray, (t_cylinder *)node->data, t);
	else if (node->type == PLANE &&
			((t_plane *)(node->data))->is_negativ == is_neg)
		is_plane_hit(ray, (t_plane *)node->data, t);
	else if (node->type == CONE &&
			((t_cone *)(node->data))->is_negativ == is_neg)
		is_cone_hit(ray, (t_cone *)node->data, t);
	get_hit_next(ray, node, is_neg, t);
}

static inline void		find_hit(t_node *nodes, t_ray *r, int *is_neg, t_hit *h)
{
	t_hit	tmp;

	init_hit(h);
	while (nodes)
	{
		if (*is_neg == 0)
			*is_neg = neg_exists(nodes);
		get_hit(r, nodes, 0, &tmp);
		if (tmp.bool == 1)
		{
			if ((h->bool == 0 || tmp.t <= h->t) && tmp.t > 0)
				*h = tmp;
		}
		nodes = nodes->next;
	}
}

static inline void		choose(t_node *n, t_ray *r, t_hit *n_hit, t_hit *c_hit)
{
	t_vec	tmp_pos;

	if ((n_hit->t < c_hit->t && n_hit->t_max < c_hit->t_max))
	{
		if (n_hit->type == PLANE)
			c_hit->nml = scalar_product(n_hit->nml, -1);
		else
		{
			c_hit->t = n_hit->t_max;
			c_hit->nml = scalar_product(n_hit->nml_max, -1);
		}
	}
	else if (n_hit->t > c_hit->t && n_hit->t_max > c_hit->t_max &&
			c_hit->t_max > n_hit->t)
	{
		c_hit->t_max = n_hit->t;
		c_hit->nml_max = scalar_product(n_hit->nml, -1);
	}
	else if (n_hit->t < c_hit->t && n_hit->t_max > c_hit->t_max)
	{
		tmp_pos = scalar_product(r->dir, c_hit->t_max);
		r->pos = vec_add(r->pos, tmp_pos);
		find_closest_object(n, r, c_hit);
	}
}

void					find_closest_object(t_node *nodes, t_ray *ray, t_hit *h)
{
	t_hit		n_hit;
	int			is_neg;

	is_neg = 0;
	find_hit(nodes, ray, &is_neg, h);
	n_hit = find_neg_hit(nodes, ray, h, is_neg);
	if (n_hit.bool == 1)
		choose(nodes, ray, &n_hit, h);
}
