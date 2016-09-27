/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cam.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/10 17:32:27 by nbelouni          #+#    #+#             */
/*   Updated: 2016/09/26 20:03:42 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

int			get_cam_att(t_elem *tmp, t_vec **lk, t_vec **pos)
{
	if (!ft_strcmp(tmp->name, "pos"))
	{
		if (!get_new_vec(tmp, pos))
			return (0);
	}
	else if (!ft_strcmp(tmp->name, "look_at"))
	{
		if (!get_new_vec(tmp, lk))
			return (0);
		(*lk)->x = deg_to_rad((*lk)->x);
		(*lk)->y = deg_to_rad((*lk)->y);
		(*lk)->z = deg_to_rad((*lk)->z);
	}
	else
	{
		return_invalid_arg(tmp->name);
		return (0);
	}
	return (1);
}

int			return_invalid_vec(t_vec *pos, t_vec *lk)
{
	if (!pos || !lk)
	{
		if (!pos)
			print_error("'pos' missing", 1);
		else
			free(pos);
		if (!lk)
			print_error("'lk' missing", 1);
		else
			free(lk);
		return (1);
	}
	return (0);
}

t_cam		*get_cam(t_scene *scene, t_part *part)
{
	t_elem	*tmp;
	t_vec	*pos;
	t_vec	*lk;

	pos = NULL;
	lk = NULL;
	tmp = part->elems;
	while (tmp)
	{
		if (!get_cam_att(tmp, &lk, &pos))
			return (NULL);
		tmp = tmp->next;
	}
	if (return_invalid_vec(pos, lk))
		return (NULL);
	scene->cam = init_camera(*pos, *lk);
	free(pos);
	free(lk);
	return (&(scene->cam));
}
