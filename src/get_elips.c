/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_elips.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/11 15:41:11 by nbelouni          #+#    #+#             */
/*   Updated: 2016/09/11 16:08:28 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

int		get_e_att1(t_elem *tmp2, t_e_tool *tool, t_elips *elips)
{
	if (!ft_strcmp(tmp2->name, "radius"))
	{
		if (!get_unsigned_double(tmp2, &(elips->radius)))
			return (-1);
	}
	else if (!ft_strcmp(tmp2->name, "pos"))
	{
		if (!get_new_vec(tmp2, &(tool->vec)))
			return (-1);
	}
	else if (!ft_strcmp(tmp2->name, "quad"))
	{
		if (!get_new_quad(tmp2, &(tool->quad)))
			return (-1);
	}
	else if (!ft_strcmp(tmp2->name, "color"))
	{
		if (!get_new_color(tmp2, &(tool->color), OBJECT))
			return (-1);
	}
	else
		return (0);
	return (1);
}

int		get_e_att2(t_elem *tmp2, t_elips *elips)
{
	if (!ft_strcmp(tmp2->name, "specular"))
	{
		if (!get_secur_num(tmp2, &(elips->specular), 0, 100))
			return (-1);
	}
	else if (!ft_strcmp(tmp2->name, "reflection"))
	{
		if (!get_secur_num(tmp2, &(elips->reflection), 0, 1))
			return (-1);
	}
	else if (!ft_strcmp(tmp2->name, "opacity"))
	{
		if (!get_secur_num(tmp2, &(elips->opacity), 0, 1))
			return (-1);
	}
	else if (!ft_strcmp(tmp2->name, "ref_index"))
	{
		if (!get_secur_num(tmp2, &(elips->ref_index), 1, 10))
			return (-1);
	}
	else
		return (0);
	return (1);
}

int		get_e_att3(t_elem *tmp2, t_elips *elips)
{
	if (!ft_strcmp(tmp2->name, "is_negativ"))
	{
		if (!get_secur_is(tmp2, &(elips->is_negativ)))
			return (0);
	}
	else if (!ft_strcmp(tmp2->name, "texture"))
	{
		if (!get_secur_enum(tmp2, &(elips->texture)))
			return (0);
	}
	else
		return (return_invalid_arg(tmp2->name));
	return (1);
}

int		get_e_all(t_elem *tmp2, t_elips *elips, t_e_tool *tool)
{
	int		ref;

	if ((ref = get_e_att1(tmp2, tool, elips)) == -1)
		return (0);
	if (ref == 0 && (ref = get_e_att2(tmp2, elips)) == -1)
		return (0);
	if (ref == 0 && !get_e_att3(tmp2, elips))
		return (0);
	return (1);
}

t_elips	*get_elips(t_part *part)
{
	t_elem		*tmp2;
	t_e_tool	tool;
	t_elips		*elips;

	tool.vec = NULL;
	tool.quad = NULL;
	tool.color = NULL;
	if (!(elips = init_elips()))
		return (NULL);
	tmp2 = part->elems;
	while (tmp2)
	{
		if (!get_e_all(tmp2, elips, &tool))
			return (NULL);
		tmp2 = tmp2->next;
	}
	if (elips_invalid(elips, &tool))
		return (NULL);
	return (elips);
}
