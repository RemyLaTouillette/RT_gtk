/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_objects.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/09 02:29:09 by nbelouni          #+#    #+#             */
/*   Updated: 2016/09/22 15:06:40 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

int			get_data1(t_part *tmp, void **data)
{
	if (tmp->type == SPHERE)
	{
		if (!(*data = get_sphere(tmp)))
			return (-1);
	}
	else if (tmp->type == CYLINDER)
	{
		if (!(*data = get_cylinder(tmp)))
			return (-1);
	}
	else if (tmp->type == PLANE)
	{
		if (!(*data = get_plane(tmp)))
			return (-1);
	}
	else if (tmp->type == CONE)
	{
		if (!(*data = get_cone(tmp)))
			return (-1);
	}
	else
		return (0);
	return (1);
}

int			get_data2(t_part *tmp, void **data)
{
	if (tmp->type == ELIPS)
	{
		if (!(*data = get_elips(tmp)))
			return (0);
	}
	else if (tmp->type == TRIAN)
	{
		if (!(*data = get_triangle(tmp)))
			return (0);
	}
	else if (tmp->type == PARA)
	{
		if (!(*data = get_para(tmp)))
			return (0);
	}
	else if (tmp->type == TETRA)
	{
		if (!(*data = get_tetra(tmp)))
			return (0);
	}
	else
		return (0);
	return (1);
}

int			get_data(void **data, t_part *tmp)
{
	int		ref;

	if ((ref = get_data1(tmp, data)) == -1)
		return (0);
	if (ref == 0 && !get_data2(tmp, data))
		return (0);
	return (1);
}

t_scene		*get_objects(t_scene *scene, t_part *part)
{
	t_node	*node;
	t_part	*tmp;
	void	*data;

	if (!(tmp = part->sub_parts))
	{
		print_error("Empty Object\n", 1);
		return (NULL);
	}
	while (tmp)
	{
		data = NULL;
		if (!get_data(&data, tmp))
			return (NULL);
		if (!(node = init_node(tmp->type, data, "obj")))
			return (NULL);
		node_add(&(scene->objects), node);
		tmp = tmp->next;
	}
	return (scene);
}
