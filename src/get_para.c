/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_para.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/14 19:59:56 by nbelouni          #+#    #+#             */
/*   Updated: 2016/09/22 15:07:18 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

int			get_para_att1(t_elem *tmp2, t_vec **v, t_color **color)
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

int			get_para_att2(t_elem *tmp2, t_parallelo *para)
{
	if (!ft_strcmp(tmp2->name, "specular"))
	{
		if (!get_secur_num(tmp2, &(para->specular), 0, 100))
			return (-1);
	}
	else if (!ft_strcmp(tmp2->name, "reflection"))
	{
		if (!get_secur_num(tmp2, &(para->reflection), 0, 1))
			return (-1);
	}
	else if (!ft_strcmp(tmp2->name, "opacity"))
	{
		if (!get_secur_num(tmp2, &(para->opacity), 0, 1))
			return (-1);
	}
	else if (!ft_strcmp(tmp2->name, "ref_index"))
	{
		print_error("'rectangle' : 'ref_index' always == 1\n\n", 2);
		return (-1);
	}
	else
		return (0);
	return (1);
}

int			get_para_all(t_elem *tmp2, t_parallelo *p, t_vec **v, t_color **c)
{
	int		ref;

	if ((ref = get_para_att1(tmp2, v, c)) == -1)
		return (-1);
	if (ref == 0 && (ref = get_para_att2(tmp2, p)) == -1)
		return (-1);
	if (ref == 0)
	{
		if (!ft_strcmp(tmp2->name, "is_negativ"))
		{
			if (!get_secur_is(tmp2, &(p->is_negativ)))
				return (0);
		}
		else if (!ft_strcmp(tmp2->name, "texture"))
		{
			if (!get_secur_enum(tmp2, &(p->texture)))
				return (0);
		}
		else
			return (return_invalid_arg(tmp2->name));
	}
	return (1);
}

int			para_invalid(t_parallelo *para, t_vec **v, t_color *color)
{
	if (!v[0] || !v[1] || !v[2] || !color)
	{
		if (!v[0])
			print_error("'v0' missing", 1);
		if (!v[1])
			print_error("'v1' missing", 1);
		if (!v[2])
			print_error("'v2' missing", 1);
		if (!color)
			print_error("'color' missing", 1);
		return (1);
	}
	para->v0 = *v[0];
	para->v1 = *v[1];
	para->v2 = *v[2];
	para->color = *color;
	free(v[0]);
	free(v[1]);
	free(v[2]);
	free(color);
	return (0);
}

t_parallelo	*get_para(t_part *part)
{
	t_elem		*tmp2;
	t_vec		*v[3];
	t_color		*color;
	t_parallelo	*para;

	v[0] = NULL;
	v[1] = NULL;
	v[2] = NULL;
	color = NULL;
	if (!(para = init_para()))
		return (NULL);
	tmp2 = part->elems;
	while (tmp2)
	{
		if (!get_para_all(tmp2, para, v, &color))
			return (NULL);
		tmp2 = tmp2->next;
	}
	if (para_invalid(para, v, color))
		return (NULL);
	return (para);
}
