/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects_cmp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlepeche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/16 13:45:59 by tlepeche          #+#    #+#             */
/*   Updated: 2016/09/16 16:43:18 by tlepeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

int		find_type_cmp(void *n_data, void *o_data, int type)
{
	int	res;

	res = 0;
	if (type == SPHERE)
		res = sphere_cmp(((t_sphere *)(n_data)), ((t_sphere *)(o_data)));
	else if (type == CYLINDER)
		res = cylinder_cmp(((t_cylinder *)(n_data)), ((t_cylinder *)(o_data)));
	else if (type == CONE)
		res = cone_cmp(((t_cone *)(n_data)), ((t_cone *)(o_data)));
	else if (type == PLANE)
		res = plane_cmp(((t_plane *)(n_data)), ((t_plane *)(o_data)));
	else if (type == ELIPS)
		res = elips_cmp(((t_elips *)(n_data)), ((t_elips *)(o_data)));
	else if (type == TRIAN)
		res = triangle_cmp(((t_triangle *)(n_data)), ((t_triangle *)(o_data)));
	else if (type == PARA)
		res = para_cmp(((t_parallelo *)(n_data)), ((t_parallelo *)(o_data)));
	else if (type == TETRA)
		res = tetra_cmp(((t_tetra *)(n_data)), ((t_tetra *)(o_data)));
	return (res);
}

int		obj_list_cmp(t_node *new_obj, t_node *old_obj)
{
	t_node	*new;
	t_node	*old;
	int		res;

	new = new_obj;
	while (new != NULL)
	{
		old = old_obj;
		res = 0;
		while (old != NULL)
		{
			if (new->type == old->type)
				res = find_type_cmp(new->data, old->data, new->type);
			if (res == 1)
				break ;
			old = old->next;
		}
		if (res == 0)
			return (0);
		new = new->next;
	}
	return (1);
}

int		objects_cmp(t_node *new_obj, t_node *old_obj)
{
	t_node	*n_tmp;
	t_node	*o_tmp;
	int		i;
	int		j;

	n_tmp = new_obj;
	o_tmp = old_obj;
	i = 0;
	j = 0;
	while (n_tmp != NULL)
	{
		i++;
		n_tmp = n_tmp->next;
	}
	while (o_tmp != NULL)
	{
		j++;
		o_tmp = o_tmp->next;
	}
	if (i != j)
		return (0);
	return (obj_list_cmp(new_obj, old_obj));
}
