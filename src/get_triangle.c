/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_triangle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/11 16:42:46 by nbelouni          #+#    #+#             */
/*   Updated: 2016/09/22 15:08:47 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

int			get_t_att1(t_elem *tmp2, t_vec **v, t_color **color)
{
	if (!ft_strcmp(tmp2->name, "v0"))
	{
		if (!get_new_vec(tmp2, &v[0]))
			return (-1);
	}
	else if (!ft_strcmp(tmp2->name, "v1"))
	{
		if (!get_new_vec(tmp2, &v[1]))
			return (-1);
	}
	else if (!ft_strcmp(tmp2->name, "v2"))
	{
		if (!get_new_vec(tmp2, &v[2]))
			return (-1);
	}
	else if (!ft_strcmp(tmp2->name, "color"))
	{
		if (!get_new_color(tmp2, color, OBJECT))
			return (-1);
	}
	else
		return (0);
	return (1);
}

int			get_t_att2(t_elem *tmp2, t_triangle *triangle)
{
	if (!ft_strcmp(tmp2->name, "specular"))
	{
		if (!get_secur_num(tmp2, &(triangle->specular), 0, 100))
			return (-1);
	}
	else if (!ft_strcmp(tmp2->name, "reflection"))
	{
		if (!get_secur_num(tmp2, &(triangle->reflection), 0, 1))
			return (-1);
	}
	else if (!ft_strcmp(tmp2->name, "opacity"))
	{
		if (!get_secur_num(tmp2, &(triangle->opacity), 0, 1))
			return (-1);
	}
	else if (!ft_strcmp(tmp2->name, "ref_index"))
	{
		print_error("'triangle' : 'ref_index' always == 1\n\n", 2);
		return (-1);
	}
	else
		return (0);
	return (1);
}

int			get_t_att3(t_elem *tmp2, t_triangle *triangle)
{
	if (!ft_strcmp(tmp2->name, "is_negativ"))
	{
		if (!get_secur_is(tmp2, &(triangle->is_negativ)))
			return (0);
	}
	else if (!ft_strcmp(tmp2->name, "texture"))
	{
		if (!get_secur_enum(tmp2, &(triangle->texture)))
			return (0);
	}
	else
		return (return_invalid_arg(tmp2->name));
	return (1);
}

int			get_t_all(t_elem *tmp2, t_triangle *t, t_vec **v, t_color **color)
{
	int		ref;

	if ((ref = get_t_att1(tmp2, v, color)) == -1)
		return (0);
	if (ref == 0 && (ref = get_t_att2(tmp2, t)) == -1)
		return (0);
	if (ref == 0 && !get_t_att3(tmp2, t))
		return (0);
	return (1);
}

t_triangle	*get_triangle(t_part *part)
{
	t_elem		*tmp2;
	t_vec		*v[3];
	t_color		*color;
	t_triangle	*triangle;

	v[0] = NULL;
	v[1] = NULL;
	v[2] = NULL;
	color = NULL;
	if (!(triangle = init_triangle()))
		return (NULL);
	tmp2 = part->elems;
	while (tmp2)
	{
		if (!get_t_all(tmp2, triangle, v, &color))
			return (NULL);
		tmp2 = tmp2->next;
	}
	if (triangle_invalid(triangle, v, color))
		return (NULL);
	return (triangle);
}
