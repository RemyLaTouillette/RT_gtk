/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_sphere.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/10 18:22:04 by nbelouni          #+#    #+#             */
/*   Updated: 2016/09/22 15:08:12 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

int			get_s_att1(t_elem *tmp2, t_sphere *s, t_vec **pos, t_color **color)
{
	if (!ft_strcmp(tmp2->name, "radius"))
	{
		if (!get_unsigned_double(tmp2, &(s->radius)))
			return (-1);
	}
	else if (!ft_strcmp(tmp2->name, "pos"))
	{
		if (!get_new_vec(tmp2, pos))
			return (-1);
	}
	else if (!ft_strcmp(tmp2->name, "color"))
	{
		if (!get_new_color(tmp2, color, OBJECT))
			return (-1);
	}
	else if (!ft_strcmp(tmp2->name, "specular"))
	{
		if (!get_secur_num(tmp2, &(s->specular), 0, 100))
			return (-1);
	}
	else
		return (0);
	return (1);
}

int			get_sphere_att2(t_elem *tmp2, t_sphere *sphere)
{
	if (!ft_strcmp(tmp2->name, "reflection"))
	{
		if (!get_secur_num(tmp2, &(sphere->reflection), 0, 1))
			return (-1);
	}
	else if (!ft_strcmp(tmp2->name, "opacity"))
	{
		if (!get_secur_num(tmp2, &(sphere->opacity), 0, 1))
			return (-1);
	}
	else if (!ft_strcmp(tmp2->name, "ref_index"))
	{
		if (!get_secur_num(tmp2, &(sphere->ref_index), 1, 10))
			return (-1);
	}
	else if (!ft_strcmp(tmp2->name, "is_negativ"))
	{
		if (!get_secur_is(tmp2, &(sphere->is_negativ)))
			return (-1);
	}
	else
		return (0);
	return (1);
}

int			get_s_all(t_elem *tmp2, t_sphere *s, t_vec **pos, t_color **color)
{
	int			ref;

	if ((ref = get_s_att1(tmp2, s, pos, color)) == -1)
		return (0);
	else if (ref == 0)
	{
		if ((ref = get_sphere_att2(tmp2, s)) == -1)
			return (0);
	}
	if (ref == 0)
	{
		if (!ft_strcmp(tmp2->name, "texture"))
		{
			if (!get_secur_enum(tmp2, &(s->texture)))
				return (0);
		}
		else
			return (return_invalid_arg(tmp2->name));
	}
	return (1);
}

int			sphere_invalid(t_vec *pos, t_color *color)
{
	if (!pos || !color)
	{
		if (!pos)
			print_error("'pos' missing\n", 1);
		if (!color)
			print_error("'color' missing\n", 1);
		return (1);
	}
	return (0);
}

t_sphere	*get_sphere(t_part *part)
{
	t_elem		*tmp2;
	t_vec		*pos;
	t_color		*color;
	t_sphere	*sphere;

	pos = NULL;
	color = NULL;
	if (!(sphere = init_sphere()))
		return (NULL);
	tmp2 = part->elems;
	while (tmp2)
	{
		if (!get_s_all(tmp2, sphere, &pos, &color))
			return (NULL);
		tmp2 = tmp2->next;
	}
	if (sphere_invalid(pos, color))
		return (NULL);
	sphere->center = *pos;
	sphere->color = *color;
	free(pos);
	free(color);
	return (sphere);
}
