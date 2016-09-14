/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_get2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/10 14:40:42 by nbelouni          #+#    #+#             */
/*   Updated: 2016/09/10 17:49:41 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

int		get_new_vec(t_elem *elem, t_vec **pos)
{
	if (*pos)
	{
		write(1, "'", 1);
		ft_putstr(elem->name);
		ft_putendl("' redefined\n");
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
		write(1, "'", 1);
		ft_putstr(elem->name);
		ft_putendl("' redefined\n");
		return (0);
	}
	if (!(*quad = get_quad(elem->values)))
		return (0);
	if ((*quad)->a <= 0 || (*quad)->b <= 0 || (*quad)->c <= 0)
	{
		ft_putendl("'quad' value <= 0\n");
		return (0);
	}
	return (1);
}

int		get_new_color(t_elem *elem, t_color **color, int type)
{
	if (*color)
	{
		ft_putendl("'color' redefined\n");
		return (0);
	}
	if (!(*color = get_color(elem->values, type)))
		return (0);
	return (1);
}

int		return_invalid_arg(char *name)
{
	ft_putstr("'");
	ft_putstr(name);
	ft_putendl("' invalid\n");
	return (0);
}
