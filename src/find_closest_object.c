/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_closest_object.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/13 02:55:00 by nbelouni          #+#    #+#             */
/*   Updated: 2016/09/14 17:57:49 by tlepeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

t_hit		get_hit_next(t_ray *ray, t_node *node, int is_neg, t_hit tmp)
{
	t_hit	tmp_content;

	tmp_content = tmp;
	if (node->type == ELIPS &&
		((t_elips *)(node->data))->is_negativ == is_neg)
		tmp_content = is_elips_hit(ray, (t_elips *)node->data);
	else if (node->type == TRIAN &&
			((t_triangle *)(node->data))->is_negativ == is_neg)
		tmp_content = is_trian_hit(ray, (t_triangle *)node->data);
	else if (node->type == PARA &&
			((t_parallelo *)(node->data))->is_negativ == is_neg)
		tmp_content = is_parallelo_hit(ray, (t_parallelo *)node->data);
	else if (node->type == TETRA &&
			((t_tetra *)(node->data))->is_negativ == is_neg)
		tmp_content = is_tetra_hit(ray, (t_tetra *)node->data);
	return (tmp_content);
}

t_hit		get_hit(t_ray *ray, t_node *node, int is_neg)
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
	return (get_hit_next(ray, node, is_neg, tmp_content));
}

t_hit		find_hit(t_node *nodes, t_ray *ray, int *is_neg)
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
			{
				c_hit = tmp;
			}
		}
		nodes = nodes->next;
	}
	return (c_hit);
}

void		choose_c_hit(t_node *nodes, t_ray *ray, t_hit n_hit, t_hit *c_hit)
{
	t_vec	tmp_pos;

	if ((n_hit.t < c_hit->t && n_hit.t_max < c_hit->t_max &&
		c_hit->t < n_hit.t_max))
	{
		if (n_hit.type == PLANE)
			c_hit->nml = scalar_product(n_hit.nml, -1);
		else
		{
			c_hit->t = n_hit.t_max;
			c_hit->nml = scalar_product(n_hit.nml_max, -1);
		}
	}
	else if (n_hit.t > c_hit->t && n_hit.t_max > c_hit->t_max &&
			c_hit->t_max > n_hit.t)
	{
		c_hit->t_max = n_hit.t;
		c_hit->nml_max = scalar_product(n_hit.nml, -1);
	}
	else if (n_hit.t <= c_hit->t && n_hit.t_max >= c_hit->t_max)
	{
		tmp_pos = scalar_product(ray->dir, c_hit->t_max);
		ray->pos = vec_add(ray->pos, tmp_pos);
		*c_hit = find_closest_object(nodes, ray);
	}
}

t_hit		find_closest_object(t_node *nodes, t_ray *ray)
{
	t_hit		n_hit;
	t_hit		c_hit;
	int			is_neg;

	is_neg = 0;
	c_hit = find_hit(nodes, ray, &is_neg);
	n_hit = find_neg_hit(nodes, ray, &c_hit, is_neg);
	if (n_hit.bool == 1)
		choose_c_hit(nodes, ray, n_hit, &c_hit);
	return (c_hit);
}
