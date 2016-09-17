/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_closest_neg_object.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlepeche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/06 17:49:23 by tlepeche          #+#    #+#             */
/*   Updated: 2016/09/14 17:57:42 by tlepeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

t_hit		init_hit(void)
{
	t_hit		hit;

	hit.t = 1000000;
	hit.t_max = 1000000;
	hit.color.r = 0;
	hit.color.g = 0;
	hit.color.b = 0;
	hit.bool = 0;
	hit.dist_from_center = -1.0;
	hit.length = -1.0;
	hit.opacity = 1;
	hit.is_negativ = 0;
	return (hit);
}

int			neg_exists(t_node *node)
{
	if ((node->type == SPHERE &&
		((t_sphere *)(node->data))->is_negativ == 1) ||
		(node->type == CYLINDER &&
		((t_cylinder *)(node->data))->is_negativ == 1) ||
		(node->type == PLANE &&
		((t_plane *)(node->data))->is_negativ == 1) ||
		(node->type == CONE &&
		((t_cone *)(node->data))->is_negativ == 1) ||
		(node->type == ELIPS &&
		((t_elips *)(node->data))->is_negativ == 1) ||
		(node->type == TRIAN &&
		((t_triangle *)(node->data))->is_negativ == 1) ||
		(node->type == PARA &&
		((t_parallelo *)(node->data))->is_negativ == 1) ||
		(node->type == TETRA &&
		((t_tetra *)(node->data))->is_negativ == 1))
		return (1);
	return (0);
}

void		choose_neg_hit(t_hit *tmp, t_hit *n_hit)
{
	if (tmp->t < n_hit->t && tmp->t_max < n_hit->t_max)
	{
		if (tmp->t_max > n_hit->t)
		{
			n_hit->t = tmp->t;
			n_hit->point_norm = tmp->point_norm;
		}
		else
			n_hit = tmp;
	}
	else if (n_hit->t < tmp->t && n_hit->t_max < tmp->t_max &&
			n_hit->t_max >= tmp->t)
	{
		n_hit->t_max = tmp->t_max;
		n_hit->point_norm_max = tmp->point_norm_max;
	}
	else if (tmp->t < n_hit->t && tmp->t_max > n_hit->t_max)
		n_hit = tmp;
}

t_hit		find_neg_hit(t_node *nodes, t_ray *ray, t_hit *c_hit, int is_neg)
{
	t_hit	n_hit;
	t_hit	tmp;

	n_hit = init_hit();
	while (is_neg && nodes)
	{
		tmp = get_hit(ray, nodes, 1);
		if (tmp.bool == 1 && ((c_hit->t < tmp.t_max && c_hit->t > tmp.t) ||
			(c_hit->t_max > tmp.t && c_hit->t_max < tmp.t_max) ||
			(c_hit->t < tmp.t && c_hit->t_max > tmp.t_max)))
		{
			if (n_hit.bool == 0)
				n_hit = tmp;
			else
				choose_neg_hit(&tmp, &n_hit);
		}
		nodes = nodes->next;
	}
	return (n_hit);
}
