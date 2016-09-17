/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lights_cmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlepeche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/16 15:28:52 by tlepeche          #+#    #+#             */
/*   Updated: 2016/09/16 16:55:25 by tlepeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

int		light_type_cmp(t_light *new_lights, t_light *old_lights)
{
	if (vec_cmp(new_lights->pos, old_lights->pos) == 0 ||
		color_cmp(new_lights->color, old_lights->color) == 0)
		return (0);
	if (new_lights->type == DIRECT && (new_lights->angle != old_lights->angle ||
		vec_cmp(new_lights->look_at, old_lights->look_at) == 0))
		return (0);
	return (1);
}

int		light_list_cmp(t_node *new_lights, t_node *old_lights)
{
	t_node	*n;
	t_node	*old;
	int		res;

	n = new_lights;
	while (n != NULL)
	{
		old = old_lights;
		res = 0;
		while (old != NULL)
		{
			if (((t_light *)(n->data))->type == ((t_light *)(old->data))->type)
				res = light_type_cmp(((t_light *)(n->data)),
						((t_light *)(old->data)));
			if (res == 1)
				break ;
			old = old->next;
		}
		if (res == 0)
			return (0);
		n = n->next;
	}
	return (1);
}

int		lights_cmp(t_node *new_lights, t_node *old_lights)
{
	t_node	*n_tmp;
	t_node	*o_tmp;
	int		i;
	int		j;

	n_tmp = new_lights;
	o_tmp = old_lights;
	i = 0;
	j = 0;
	while (n_tmp != NULL)
	{
		i++;
		n_tmp = n_tmp->next;
	}
	while (o_tmp != NULL)
	{
		j++;
		o_tmp = o_tmp->next;
	}
	if (i != j)
		return (0);
	return (light_list_cmp(new_lights, old_lights));
}
