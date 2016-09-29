/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_get.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/10 14:37:17 by nbelouni          #+#    #+#             */
/*   Updated: 2016/09/28 18:36:14 by tlepeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

int		free_and_return(void *ptr, int i)
{
	free(ptr);
	return (i);
}

int		get_unsigned_double(t_elem *elem, double *radius)
{
	if (*radius != 0)
	{
		print_error(join("'", elem->name, "' redefined\n"), 1);
		return (0);
	}
	*radius = get_num(elem->values);
	if (radius < 0)
	{
		print_error(join("'", elem->name, "' < 0\n"), 1);
		return (0);
	}
	return (1);
}

int		get_secur_is(t_elem *elem, int *is)
{
	if (*is != NONE)
	{
		print_error(join("'", elem->name, "' redefined\n"), 1);
		return (0);
	}
	if ((*is = get_bool(elem->values)) == -1)
	{
		print_error(join("value of '", elem->name, "' != 'y' and 'n'\n"), 1);
		return (0);
	}
	return (1);
}

int		get_secur_num(t_elem *elem, double *n, double min, double max)
{
	char	*tmp;
	char	*new;
	char	*c_n;

	*n = get_num(elem->values);
	if (min != max && (*n < min || *n > max))
	{
		c_n = ft_itoa(min);
		new = join("'", elem->name, "' : < ");
		tmp = join(new, c_n, " or > ");
		free(new);
		free(c_n);
		c_n = ft_itoa(max);
		print_error(join(tmp, c_n, "\n"), 1);
		free(c_n);
		free(tmp);
		return (0);
	}
	return (1);
}

int		get_secur_enum(t_elem *elem, int *e)
{
	char *tmp;

	if (*e != NONE)
	{
		print_error(join("'", elem->name, "' redefined\n"), 1);
		return (0);
	}
	*e = get_enum(elem->values);
	if (*e == -1)
	{
		tmp = join("'", elem->name, "' : '");
		print_error(join(tmp, elem->values[0], "' does not exist\n"), 1);
		free(tmp);
		return (0);
	}
	return (1);
}
