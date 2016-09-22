/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_get2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/10 14:40:42 by nbelouni          #+#    #+#             */
/*   Updated: 2016/09/22 16:19:58 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

int		get_new_vec(t_elem *elem, t_vec **pos)
{
	if (*pos)
	{
		print_error(join("'", elem->name, "' redefined\n"), 1);
		return (0);
	}
	if (!(*pos = get_vec(elem->values, elem->name)))
		return (0);
	return (1);
}

int		get_new_quad(t_elem *elem, t_quad **quad)
{
	if (*quad)
	{
		print_error(join("'", elem->name, "' redefined\n"), 1);
		return (0);
	}
	if (!(*quad = get_quad(elem->values)))
		return (0);
	if ((*quad)->a <= 0 || (*quad)->b <= 0 || (*quad)->c <= 0)
	{
		print_error("'quad' value <= 0\n", 1);
		return (0);
	}
	return (1);
}

int		get_new_color(t_elem *elem, t_color **color, int type)
{
	if (*color)
	{
		print_error("'color' redefined\n", 1);
		return (0);
	}
	if (!(*color = get_color(elem->values, type)))
		return (0);
	return (1);
}

int		return_invalid_arg(char *name)
{
	print_error(join("'", name, "' invalid\n"), 1);
	return (0);
}
