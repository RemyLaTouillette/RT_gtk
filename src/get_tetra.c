/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tetra.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/14 19:24:02 by nbelouni          #+#    #+#             */
/*   Updated: 2016/09/15 13:55:44 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

int		get_tetra1(t_elem *tmp2, t_vec **v)
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
	else if (!ft_strcmp(tmp2->name, "v3"))
	{
		if (!get_new_vec(tmp2, &v[3]))
			return (-1);
	}
	else
		return (0);
	return (1);
}

int		get_tetra2(t_elem *tmp2, t_tetra *tetra, t_color **color)
{
	if (!ft_strcmp(tmp2->name, "color"))
	{
		if (!get_new_color(tmp2, color, OBJECT))
			return (-1);
	}
	else if (!ft_strcmp(tmp2->name, "specular"))
	{
		if (!get_secur_num(tmp2, &(tetra->specular), 0, 100))
			return (-1);
	}
	else if (!ft_strcmp(tmp2->name, "reflection"))
	{
		if (!get_secur_num(tmp2, &(tetra->reflection), 0, 1))
			return (-1);
	}
	else if (!ft_strcmp(tmp2->name, "opacity"))
	{
		if (!get_secur_num(tmp2, &(tetra->opacity), 0, 1))
			return (-1);
	}
	else
		return (0);
	return (1);
}

int		get_tetra3(t_elem *tmp2, t_tetra *tetra)
{
	if (!ft_strcmp(tmp2->name, "is_negativ"))
	{
		if (!get_secur_is(tmp2, &(tetra->is_negativ)))
			return (0);
	}
	else if (!ft_strcmp(tmp2->name, "ref_index"))
	{
		if (!get_secur_num(tmp2, &(tetra->ref_index), 1, 10))
			return (0);
	}
	else if (!ft_strcmp(tmp2->name, "texture"))
	{
		if (!get_secur_enum(tmp2, &(tetra->texture)))
			return (0);
	}
	else
		return (return_invalid_arg(tmp2->name));
	return (1);
}

int		get_tetra_all(t_elem *tmp2, t_tetra *tetra, t_vec **v, t_color **color)
{
	int		ref;

	if ((ref = get_tetra1(tmp2, v)) == -1)
		return (0);
	if (ref == 0 && (ref = get_tetra2(tmp2, tetra, color)) == -1)
		return (0);
	if (ref == 0)
		if (!get_tetra3(tmp2, tetra))
			return (0);
	return (1);
}

t_tetra	*get_tetra(t_part *part)
{
	t_elem		*tmp2;
	t_vec		*v[4];
	t_color		*color;
	t_tetra		*tetra;

	v[0] = NULL;
	v[1] = NULL;
	v[2] = NULL;
	v[3] = NULL;
	color = NULL;
	if (!(tetra = init_tetra()))
		return (NULL);
	tmp2 = part->elems;
	while (tmp2)
	{
		if (!get_tetra_all(tmp2, tetra, v, &color))
			return (NULL);
		tmp2 = tmp2->next;
	}
	if (tetra_invalid(tetra, v, color))
		return (NULL);
	return (tetra);
}
