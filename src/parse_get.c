/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_get.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/10 14:37:17 by nbelouni          #+#    #+#             */
/*   Updated: 2016/09/19 21:01:50 by tlepeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

int		get_unsigned_double(t_elem *elem, double *radius)
{
	if (*radius != 0)
	{
		write(1, "'", 1);
		ft_putstr(elem->name);
		ft_putendl("' redefined\n");
		return (0);
	}
	*radius = get_num(elem->values);
	if (radius < 0)
	{
		write(1, "'", 1);
		ft_putstr(elem->name);
		ft_putendl("' < 0\n");
		return (0);
	}
	return (1);
}

int		get_secur_is(t_elem *elem, int *is)
{
	if (*is != NONE)
	{
		write(1, "'", 1);
		ft_putstr(elem->name);
		ft_putendl("' redefined");
		return (0);
	}
	if ((*is = get_bool(elem->values)) == -1)
	{
		ft_putstr("value of '");
		ft_putstr(elem->name);
		ft_putendl("' != 'y' and 'n'\n");
		return (0);
	}
	return (1);
}

int		get_secur_num(t_elem *elem, double *n, double min, double max)
{
	*n = get_num(elem->values);
	if (min != max && (*n < min || *n > max))
	{
		write(1, "'", 1);
		ft_putstr(elem->name);
		ft_putstr("' : < ");
		ft_putnbr(min);
		ft_putstr(" or > ");
		ft_putnbr(max);
		write(1, "\n", 1);
		return (0);
	}
	return (1);
}

int		get_secur_enum(t_elem *elem, int *e)
{
	if (*e != NONE)
	{
		write(1, "'", 1);
		ft_putstr(elem->name);
		ft_putendl("' redefined\n");
		return (0);
	}
	*e = get_enum(elem->values);
	if (*e == -1)
	{
		write(1, "'", 1);
		ft_putstr(elem->name);
		ft_putstr("' : '");
		ft_putstr(elem->values[0]);
		ft_putendl("' does not exist\n");
		return (0);
	}
	return (1);
}
