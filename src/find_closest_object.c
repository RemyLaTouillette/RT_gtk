/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_closest_object.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/13 02:55:00 by nbelouni          #+#    #+#             */
/*   Updated: 2016/09/20 14:30:28 by tlepeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

static inline t_hit		get_hit_next(t_ray *r, t_node *n, int is_neg, t_hit *t)
{
	t_hit	tmp_content;

	tmp_content = *t;
	if (n->type == ELIPS &&
		((t_elips *)(n->data))->is_negativ == is_neg)
		tmp_content = is_elips_hit(r, (t_elips *)n->data);
	else if (n->type == TRIAN &&
			((t_triangle *)(n->data))->is_negativ == is_neg)
		tmp_content = is_trian_hit(r, (t_triangle *)n->data);
	else if (n->type == PARA &&
			((t_parallelo *)(n->data))->is_negativ == is_neg)
		tmp_content = is_parallelo_hit(r, (t_parallelo *)n->data);
	else if (n->type == TETRA &&
			((t_tetra *)(n->data))->is_negativ == is_neg)
		tmp_content = is_tetra_hit(r, (t_tetra *)n->data);
	return (tmp_content);
}

t_hit					get_hit(t_ray *ray, t_node *node, int is_neg)
{
	t_hit		tmp_content;

	tmp_content = init_hit();
	if (node->type == SPHERE &&
			((t_sphere *)(node->data))->is_negativ == is_neg)
		tmp_content = is_sphere_hit(ray, (t_sphere *)node->data);
	else if (node->type == CYLINDER &&
			((t_cylinder *)(node->data))->is_negativ == is_neg)
		tmp_content = is_cylinder_hit(ray, (t_cylinder *)node->data);
	else if (node->type == PLANE &&
			((t_plane *)(node->data))->is_negativ == is_neg)
		tmp_content = is_plane_hit(ray, (t_plane *)node->data);
	else if (node->type == CONE &&
		((t_cone *)(node->data))->is_negativ == is_neg)
		tmp_content = is_cone_hit(ray, (t_cone *)node->data);
	return (get_hit_next(ray, node, is_neg, &tmp_content));
}

static inline t_hit		find_hit(t_node *nodes, t_ray *ray, int *is_neg)
{
	t_hit	c_hit;
	t_hit	tmp;

	c_hit = init_hit();
	while (nodes)
	{
		if (*is_neg == 0)
			*is_neg = neg_exists(nodes);
		tmp = get_hit(ray, nodes, 0);
		if (tmp.bool == 1)
		{
			if ((c_hit.bool == 0 || tmp.t <= c_hit.t) && tmp.t > 0)
				c_hit = tmp;
		}
		nodes = nodes->next;
	}
	return (c_hit);
}

static inline void		choose(t_node *n, t_ray *r, t_hit *n_hit, t_hit *c_hit)
{
	t_vec	tmp_pos;

	if ((n_hit->t < c_hit->t && n_hit->t_max < c_hit->t_max &&
		c_hit->t < n_hit->t_max))
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
	else if (n_hit->t <= c_hit->t && n_hit->t_max >= c_hit->t_max)
	{
		tmp_pos = scalar_product(r->dir, c_hit->t_max);
		r->pos = vec_add(r->pos, tmp_pos);
		*c_hit = find_closest_object(n, r);
	}
}

t_hit					find_closest_object(t_node *nodes, t_ray *ray)
{
	t_hit		n_hit;
	t_hit		c_hit;
	int			is_neg;

	is_neg = 0;
	c_hit = find_hit(nodes, ray, &is_neg);
	n_hit = find_neg_hit(nodes, ray, &c_hit, is_neg);
	if (n_hit.bool == 1)
		choose(nodes, ray, &n_hit, &c_hit);
	return (c_hit);
}
