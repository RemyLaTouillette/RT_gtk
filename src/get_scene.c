/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_scene.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/09 16:27:40 by nbelouni          #+#    #+#             */
/*   Updated: 2016/09/15 15:49:29 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

int			get_scene_att1(t_scene *scene, t_elem *tmp)
{
	if (!ft_strcmp(tmp->name, "cartoon"))
	{
		if (!get_secur_is(tmp, &(scene->is_real)))
			return (-1);
		scene->is_real = (scene->is_real == 0) ? REALISTIC : CARTOON;
	}
	else if (!ft_strcmp(tmp->name, "depth"))
	{
		if (!(get_secur_is(tmp, &(scene->is_dof))))
			return (-1);
	}
	else if (!ft_strcmp(tmp->name, "focus"))
	{
		if (!get_secur_num(tmp, &(scene->dof), 0, 0))
			return (-1);
	}
	else if (!ft_strcmp(tmp->name, "blur"))
	{
		if (!get_secur_num(tmp, &(scene->blur), 0, 100))
			return (-1);
	}
	else
		return (0);
	return (1);
}

int			get_scene_att2(t_scene *scene, t_elem *tmp, t_color **color)
{
	if (!ft_strcmp(tmp->name, "filter"))
	{
		if (!get_secur_enum(tmp, &(scene->filter)))
			return (0);
	}
	else if (!ft_strcmp(tmp->name, "reflection"))
	{
		if (!get_secur_num(tmp, &(scene->reflection), 1, 5))
			return (0);
	}
	else if (!ft_strcmp(tmp->name, "ambient"))
	{
		if (!get_secur_num(tmp, &(scene->ambient_index), 0, 10))
			return (0);
	}
	else if (!ft_strcmp(tmp->name, "color"))
	{
		if (!(get_new_color(tmp, color, LIGHT)))
			return (0);
	}
	else
		return (return_invalid_arg(tmp->name));
	return (1);
}

t_scene		*get_scene(t_scene *scene, t_part *part)
{
	t_elem	*tmp;
	t_color	*color;
	int		ref;

	tmp = part->elems;
	color = NULL;
	while (tmp)
	{
		if ((ref = get_scene_att1(scene, tmp)) == -1)
			return (NULL);
		if (ref == 0)
		{
			if (!get_scene_att2(scene, tmp, &color))
				return (NULL);
		}
		tmp = tmp->next;
	}
	if (color)
	{
		scene->ambient_color = *color;
		free(color);
	}
	return (scene);
}
