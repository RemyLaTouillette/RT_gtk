/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sduprey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/09 23:50:11 by sduprey           #+#    #+#             */
/*   Updated: 2016/10/03 19:01:17 by tlepeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

t_node		*init_node(int type, void *data, char *name)
{
	t_node	*node;

	if (!(node = (t_node *)malloc(sizeof(t_node))))
		return (NULL);
	node->type = type;
	node->data = data;
	node->name = name;
	node->next = NULL;
	return (node);
}

void		node_add(t_node **node, t_node *new)
{
	new->next = *(node);
	*node = new;
}

void		free_node_list(t_node **node_list)
{
	t_node	*tmp;
	t_node	*tmp2;

	tmp = *node_list;
	while (tmp)
	{
		if (tmp->data)
		{
			free(tmp->data);
			tmp->data = NULL;
		}
		tmp2 = tmp->next;
		free(tmp);
		tmp = tmp2;
	}
	*node_list = NULL;
}
