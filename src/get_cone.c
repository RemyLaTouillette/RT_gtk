/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cone.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/11 14:47:07 by nbelouni          #+#    #+#             */
/*   Updated: 2016/09/11 17:00:38 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

int		get_cone_att2(t_elem *tmp2, t_cone *cone)
{
	if (!ft_strcmp(tmp2->name, "radius"))
	{
		if (!get_unsigned_double(tmp2, &(cone->r)))
			return (-1);
	}
	else if (!ft_strcmp(tmp2->name, "length"))
	{
		if (!get_unsigned_double(tmp2, &(cone->len)))
			return (-1);
	}
	else if (!ft_strcmp(tmp2->name, "specular"))
	{
		if (!get_secur_num(tmp2, &(cone->specular), 0, 100))
			return (-1);
	}
	else if (!ft_strcmp(tmp2->name, "reflection"))
	{
		if (!get_secur_num(tmp2, &(cone->reflection), 0, 1))
			return (-1);
	}
	else
		return (0);
	return (1);
}

int		get_cone_att3(t_elem *tmp2, t_cone *cone)
{
	if (!ft_strcmp(tmp2->name, "opacity"))
	{
		if (!get_secur_num(tmp2, &(cone->opacity), 0, 1))
			return (-1);
	}
	else if (!ft_strcmp(tmp2->name, "ref_index"))
	{
		if (!get_secur_num(tmp2, &(cone->ref_index), 1, 10))
			return (-1);
	}
	else if (!ft_strcmp(tmp2->name, "is_negativ"))
	{
		if (!get_secur_is(tmp2, &(cone->is_negativ)))
			return (-1);
	}
	else if (!ft_strcmp(tmp2->name, "is_closed"))
	{
		if (!get_secur_is(tmp2, &(cone->is_closed)))
			return (-1);
	}
	else
		return (0);
	return (1);
}

int		get_cone_all(t_elem *tmp2, t_cone *cone, t_vec **v, t_color **c)
{
	int			ref;

	if ((ref = get_c_att1(tmp2, &v[0], &v[1], c)) == -1)
		return (0);
	if (ref == 0 && (ref = get_cone_att2(tmp2, cone)) == -1)
		return (0);
	if (ref == 0 && (ref = get_cone_att3(tmp2, cone)) == -1)
		return (0);
	if (ref == 0)
	{
		if (!ft_strcmp(tmp2->name, "texture"))
		{
			if (!get_secur_enum(tmp2, &(cone->texture)))
				return (0);
		}
		else
			return (return_invalid_arg(tmp2->name));
	}
	return (1);
}

t_cone	*get_cone(t_part *part)
{
	t_elem		*tmp2;
	t_vec		*v[2];
	t_color		*color;
	t_cone		*cone;

	v[0] = NULL;
	v[1] = NULL;
	color = NULL;
	if (!(cone = init_cone()))
		return (NULL);
	tmp2 = part->elems;
	while (tmp2)
	{
		if (!get_cone_all(tmp2, cone, v, &color))
			return (NULL);
		tmp2 = tmp2->next;
	}
	if (cone_invalid(cone, v, color))
		return (NULL);
	return (cone);
}
