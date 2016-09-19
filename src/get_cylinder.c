/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cylinder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/10 19:50:27 by nbelouni          #+#    #+#             */
/*   Updated: 2016/09/19 20:48:51 by tlepeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

int			get_c_att1(t_elem *tmp2, t_vec **pos, t_vec **dir, t_color **c)
{
	if (!ft_strcmp(tmp2->name, "pos"))
	{
		if (!get_new_vec(tmp2, pos))
			return (-1);
	}
	else if (!ft_strcmp(tmp2->name, "dir"))
	{
		if (!get_new_vec(tmp2, dir))
			return (-1);
		**dir = normalize(**dir);
	}
	else if (!ft_strcmp(tmp2->name, "color"))
	{
		if (!get_new_color(tmp2, c, OBJECT))
			return (-1);
	}
	else
		return (0);
	return (1);
}

int			get_cyl_att2(t_elem *tmp2, t_cylinder *cylinder)
{
	if (!ft_strcmp(tmp2->name, "radius"))
	{
		if (!get_unsigned_double(tmp2, &(cylinder->radius)))
			return (-1);
	}
	else if (!ft_strcmp(tmp2->name, "length"))
	{
		if (!get_unsigned_double(tmp2, &(cylinder->length)))
			return (-1);
	}
	else if (!ft_strcmp(tmp2->name, "specular"))
	{
		if (!get_secur_num(tmp2, &(cylinder->specular), 0, 100))
			return (-1);
	}
	else if (!ft_strcmp(tmp2->name, "reflection"))
	{
		if (!get_secur_num(tmp2, &(cylinder->reflection), 0, 1))
			return (-1);
	}
	else
		return (0);
	return (1);
}

int			get_cyl_att3(t_elem *tmp2, t_cylinder *cylinder)
{
	if (!ft_strcmp(tmp2->name, "opacity"))
	{
		if (!get_secur_num(tmp2, &(cylinder->opacity), 0, 1))
			return (-1);
	}
	else if (!ft_strcmp(tmp2->name, "ref_index"))
	{
		if (!get_secur_num(tmp2, &(cylinder->ref_index), 1, 10))
			return (-1);
	}
	else if (!ft_strcmp(tmp2->name, "is_negativ"))
	{
		if (!get_secur_is(tmp2, &(cylinder->is_negativ)))
			return (-1);
	}
	else if (!ft_strcmp(tmp2->name, "is_closed"))
	{
		if (!get_secur_is(tmp2, &(cylinder->is_closed)))
			return (-1);
	}
	else
		return (0);
	return (1);
}

int			get_cyl_all(t_elem *tmp2, t_cylinder *cyl, t_vec **v, t_color **c)
{
	int			ref;

	if ((ref = get_c_att1(tmp2, &v[0], &v[1], c)) == -1)
		return (0);
	if (ref == 0 && (ref = get_cyl_att2(tmp2, cyl)) == -1)
		return (0);
	if (ref == 0 && (ref = get_cyl_att3(tmp2, cyl)) == -1)
		return (0);
	if (ref == 0)
	{
		if (!ft_strcmp(tmp2->name, "texture"))
		{
			if (!get_secur_enum(tmp2, &(cyl->texture)))
				return (0);
		}
		else
			return (return_invalid_arg(tmp2->name));
	}
	return (1);
}

t_cylinder	*get_cylinder(t_part *part)
{
	t_elem		*tmp2;
	t_vec		*v[2];
	t_color		*color;
	t_cylinder	*cylinder;

	v[0] = NULL;
	v[1] = NULL;
	color = NULL;
	if (!(cylinder = init_cylinder()))
		return (NULL);
	tmp2 = part->elems;
	while (tmp2)
	{
		if (!get_cyl_all(tmp2, cylinder, v, &color))
			return (NULL);
		tmp2 = tmp2->next;
	}
	if (cyl_invalid(cylinder, v, color))
		return (NULL);
	return (cylinder);
}
