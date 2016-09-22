/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_plane.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/10 18:22:33 by nbelouni          #+#    #+#             */
/*   Updated: 2016/09/22 15:07:51 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

int		get_plane_att1(t_elem *tmp, t_vec **pos, t_vec **n, t_color **color)
{
	if (!ft_strcmp(tmp->name, "pos"))
	{
		if (!get_new_vec(tmp, pos))
			return (-1);
	}
	else if (!ft_strcmp(tmp->name, "normal"))
	{
		if (!get_new_vec(tmp, n))
			return (-1);
		**n = normalize(**n);
	}
	else if (!ft_strcmp(tmp->name, "color"))
	{
		if (!get_new_color(tmp, color, OBJECT))
			return (-1);
	}
	else
		return (0);
	return (1);
}

int		get_plane_att2(t_elem *tmp2, t_plane *plane)
{
	if (!ft_strcmp(tmp2->name, "specular"))
	{
		if (!get_secur_num(tmp2, &(plane->specular), 0, 100))
			return (-1);
	}
	else if (!ft_strcmp(tmp2->name, "reflection"))
	{
		if (!get_secur_num(tmp2, &(plane->reflection), 0, 1))
			return (-1);
	}
	else if (!ft_strcmp(tmp2->name, "opacity"))
	{
		if (!get_secur_num(tmp2, &(plane->opacity), 0, 1))
			return (-1);
	}
	else if (!ft_strcmp(tmp2->name, "ref_index"))
	{
		print_error("'plane' : 'ref_index' always == 1\n\n", 2);
		return (-1);
	}
	else
		return (0);
	return (1);
}

int		get_plane_all(t_elem *tmp2, t_plane *plane, int ref)
{
	if (ref == 0)
	{
		if ((ref = get_plane_att2(tmp2, plane)) == -1)
			return (0);
	}
	if (ref == 0)
	{
		if (!ft_strcmp(tmp2->name, "is_negativ"))
		{
			if (!get_secur_is(tmp2, &(plane->is_negativ)))
				return (0);
		}
		else if (!ft_strcmp(tmp2->name, "texture"))
		{
			if (!get_secur_enum(tmp2, &(plane->texture)))
				return (0);
		}
		else
			return (return_invalid_arg(tmp2->name));
	}
	return (1);
}

int		plane_invalid(t_plane *plane, t_vec *pos, t_color *color, t_vec *normal)
{
	if (!pos || !color || !normal)
	{
		if (!pos)
			print_error("'pos' missing\n", 1);
		if (!color)
			print_error("'color' missing\n", 1);
		if (!normal)
			print_error("'normal' missing\n", 1);
		return (1);
	}
	plane->pos = *pos;
	plane->normal = *normal;
	plane->color = *color;
	free(pos);
	free(normal);
	free(color);
	return (0);
}

t_plane	*get_plane(t_part *part)
{
	t_elem		*tmp2;
	t_vec		*v[2];
	t_color		*color;
	t_plane		*plane;
	int			ref;

	v[0] = NULL;
	v[1] = NULL;
	color = NULL;
	if (!(plane = init_plane()))
		return (NULL);
	tmp2 = part->elems;
	while (tmp2)
	{
		if ((ref = get_plane_att1(tmp2, &v[0], &v[1], &color)) == -1)
			return (NULL);
		if (!get_plane_all(tmp2, plane, ref))
			return (NULL);
		tmp2 = tmp2->next;
	}
	if (plane_invalid(plane, v[0], color, v[1]))
		return (NULL);
	return (plane);
}
