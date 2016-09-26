/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sduprey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/10 01:41:15 by sduprey           #+#    #+#             */
/*   Updated: 2016/09/26 17:00:26 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

void		complete_scene(t_scene *s, t_blur *tmp)
{
	s->w = WIDTH;
	s->h = HEIGHT;
	s->objects = NULL;
	s->lights = NULL;
	s->is_dof = 0;
	s->dof = 0;
	s->reflection = 1;
	s->blur_array = tmp;
	s->is_real = 0;
	s->blur = 0;
	s->filter = NONE;
	s->ambient_index = 0.0;
	init_color(&(s->ambient_color), 255, 255, 255);
}

t_scene		*init_scene(void)
{
	t_scene	*s;
	t_blur	*tmp;
	int		i;

	i = -1;
	if (!(tmp = (t_blur *)malloc(sizeof(t_blur) * HEIGHT * WIDTH)))
		return (NULL);
	while (++i < HEIGHT * WIDTH)
	{
		tmp[i].t = 0;
		tmp[i].p_obj = 0;
	}
	if (!(s = (t_scene *)malloc(sizeof(t_scene))))
		return (NULL);
	complete_scene(s, tmp);
	return (s);
}

void		free_scene(t_scene **scene)
{
	free((*scene)->blur_array);
	if (!(*scene)->objects)
		free_node_list(&((*scene)->objects));
	if (!(*scene)->lights)
		free_node_list(&((*scene)->lights));
	free(*scene);
	*scene = NULL;
}
